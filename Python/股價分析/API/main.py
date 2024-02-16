
# %%
import shioaji as sj
import touchprice as tp
from math import ceil
from datetime import date, datetime, timedelta
from apscheduler.schedulers.blocking import BlockingScheduler
import pandas as pd

sched = BlockingScheduler()

api = sj.Shioaji()
def login():
    print("Login")
    accounts = api.login("L124905566", "159753Lp",contracts_timeout=30000)
    api.activate_ca(
        ca_path="Sinopac.pfx",
        ca_passwd="L124905566",
        person_id="L124905566",
    )



def week_of_month(dt):
    """ Returns the week of the month for the specified date.
    """

    first_day = dt.replace(day=1)

    dom = dt.day
    adjusted_dom = dom + first_day.weekday()

    return int(ceil(adjusted_dom/7.0))

def roundTo50(x):
    return round(x / 50.0) * 50

def getCode():
    today = date.today()
    week = getWeek()  # 第幾週
    year = today.year
    month = "{0:02d}".format(today.month)
    index = api.snapshots([api.Contracts.Indexs["001"]])  # 當前指數
    index = pd.DataFrame(index)['close']
    price = int(roundTo50(index) + 50)  # 計算履約價 + 50
    code = f"TX{week}{year}{month}0{price}C"
    return code

def getWeek():
    today = date.today()
    week = week_of_month(today)#這個月的第幾週
    week += 1#要買新的一週
    if(week == 3):
        week = 'O'
    return week

def getWeekDay():
    return datetime.today().weekday()

def buyEveryWednesday():
    login()
    # 每禮拜三9點買入(Once a week)
    code = getCode()
    # print(api.snapshots(contracts = [api.Contracts.Options[code]]))
    week = getWeek()
    contract = api.Contracts.Options[f"TX{week}"][code]
    buyPrice = api.snapshots(contracts=[contract])  # 現價
    buyPrice = float(pd.DataFrame(buyPrice)['close'])# 現價

    hunredThousand = 2#多少個一萬

    quantity = int(10000 / (buyPrice*50)) * hunredThousand  # 要買的數量

    if(quantity == 0):
        print("The price is over 10000 now")
        return
    # 下單
    order = api.Order(action="Buy",
                      price=buyPrice,
                      quantity=quantity,
                      order_type="ROD",
                      price_type="LMT",
                      octype="Auto",
                      account=api.futopt_account)

    trade = api.place_order(contract, order)
    print(trade)
    print(f"Order {code} {quantity}口")
#%%
def touch_price_order(takeProfit: float):  # run every day to refresh token
    # touch price order(run once a day)
    if(getWeekDay() != 2):#Don't login again at wednesday
        login()
    print(f"Set touch price order:{takeProfit}")
    df = api.get_account_openposition(
        query_type='1', account=api.futopt_account)
    if(df == None):
        print("No Position Now")
        return
    df = pd.DataFrame(df.data())
    print(df)
    code = getCode()[0:3]
    for index, row in df.iterrows():
        if(code == row["Code"][0:3]):
            try:
                sellPrice = float(row['ContractAverPrice']) * takeProfit  # 停利

                position = int(float(row['Volume']))
                code = row['Code']
            except:
                print("No Position Now")
                return
            touch = tp.TouchOrderExecutor(api)
            touch_cmd = tp.TouchCmd(
                code=code,
                close=tp.Price(price=sellPrice, trend="Up")
            )

            order_cmd = tp.OrderCmd(
                code=code,
                order=sj.Order(
                    action="Sell",
                    price=sellPrice,
                    quantity=position//2,
                    order_type="ROD",
                    price_type="LMT",)
            )

            condition = tp.TouchOrderCond(
                touch_cmd=touch_cmd,
                order_cmd=order_cmd
            )
            touch.add_condition(condition)


# %%
sched.add_job(buyEveryWednesday, 'cron',
              day_of_week='wed', hour=9, minute=2)  # 0900

sched.add_job(touch_price_order, 'cron',args=[1.55],
              day_of_week='mon-fri', hour=9, minute=5)  # 0905
sched.add_job(touch_price_order, 'cron',args=[1.95],
              day_of_week='mon-fri', hour=9, minute=5)  # 0905
sched.start()


# %%
# login()
# print(getWeekDay())
# %%
