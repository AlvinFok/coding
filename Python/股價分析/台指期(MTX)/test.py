import yfinance as yf
import pandas as pd
import multiprocessing as mp

# def get_historical_data(ticker):
#   d = yf.Ticker(ticker)
#   df = d.history(period="max")
#   df.columns = df.columns.str.lower()
#   df.columns = pd.Series(df.columns).str.capitalize().values
#   return df.dropna()

# df = get_historical_data('TX')
# df.head()

import talib

# # compute simple moving average using talib
# sma1 = talib.SMA(df.Close, timeperiod=20)
# sma2 = talib.SMA(df.Close, timeperiod=60)

# # compute buy and sell signals (golden cross and death cross)
# signal_long = (sma1 > sma2) & (sma1.shift() < sma2.shift())
# signal_short = (sma1 < sma2) & (sma1.shift() > sma2.shift())

# # combine long and short signals
# signal = signal_long.copy()
# signal[signal_short] = -1

# # plot
# df.Close['2020'].plot()
# sma1['2020'].plot()
# sma2['2020'].plot()
# signal['2020'].astype(int).plot(secondary_y=True)

from backtesting import Backtest, Strategy
from backtesting.lib import crossover
import numpy as np


class Strategy(Strategy):
    # RSI setting
    rsiTimePeriod = 18
    low = 20
    high = 75

    # MACD setting
    fast = 3
    slow = 8
    signalperiod = 5

    def init(self):
        super().init()

        # Precompute the two moving averages
        close = pd.Series(self.data.Close)

        self.rsi = self.I(talib.RSI, self.data.Close, self.rsiTimePeriod)
        self.macd = self.I(talib.MACD, self.data.Close,
                           self.fast, self.slow, self.signalperiod)
        

        # Precompute signal
        # signal_long = (sma1 > sma2) & (sma1.shift() < sma2.shift())
        # signal_short = (sma1 < sma2) & (sma1.shift() > sma2.shift())

        # combine signal
        # signal = signal_long
        # signal[signal_short] = -1

        # plot sma
        # self.I(lambda x: self.rsi, 'RSI')
        # self.I(lambda x: sma2, 'sma2')

        sellSignal = (self.rsi > self.low) & (self.macd[0] < 0)
        buySignal = (self.rsi > self.high) & (self.macd[0] > 0)
        buySignal[sellSignal] = -1

        # set signal to trade
        self.signal = self.I(lambda x: buySignal, 'signal')
        # self.signal = self.I(lambda x: signal, 'signal')

    def next(self):
        super().next()

        if self.rsi[-1] > self.high and self.macd[0][-1] > 0:
            # print(f'macd = {self.macd[0][-1]}')
            # print(self.rsi[-1])
            self.buy()
        elif self.rsi[-1] < self.low and self.macd[0][-1] < 0:
            self.position.close()


df = pd.read_excel('TX.xlsx')
df.index = pd.to_datetime(df.index)
df = df.astype(np.float64)
# print(df['Open'].head())
bt = Backtest(df, Strategy)
result1 = bt.run()
print(result1)
bt.plot()


# if mp.get_start_method(allow_none=True) != 'fork':
#     mp.set_start_method('fork', force=True)

# result2 = bt.optimize(rsiTimePeriod=range(3, 20, 5),low=range(20, 40, 5), high=range(60, 80, 5), fast=range(3, 20, 5), slow=range(3, 20, 5), signalperiod=range(3, 20, 5), constraint=lambda p: p.low < p.high and p.fast < p.slow,
#             maximize='mark')

# print(result2._strategy)
# result1._trade_data.Equity.plot()
