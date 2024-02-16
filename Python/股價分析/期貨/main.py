#%%
import pandas as pd
df = pd.read_csv('TXF.csv')
df.head()
# %%
principal = [80000]
print(type(principal))
part = None
buyMode = None
takeProfit = 45
stopLoss = 20
minProfit = 0
cost = 40000
for index in range(len(df)):
    if(df.iloc[index]['Time'] == "09:00:00"):
        part = df.iloc[index]['Open']#9點買入開盤價
        principal[-1] -= cost
        if((df.iloc[index-1]['Open'] + df.iloc[index-1]['Close'] )/2 >= df.iloc[index]['Open']):#決定買call還是put
            buyMode = "call"
        else:
            buyMode = "put"
    minProfit = principal[-1]
    if(index==1180):
        print(df.iloc[index]['Time'])
        print(part)
        print(principal[-1])
        
    if(part != None):#持有部位
        #停利
        if(df.iloc[index]['High'] - part >= takeProfit and buyMode == "call"):
            minProfit = principal[-1] + (df.iloc[index]['High'] - part)*50
            minProfit += cost
            part=None
            buyMode = None
        elif(part - df.iloc[index]['Low'] >= takeProfit and buyMode == "put"):
            minProfit = principal[-1] + (part - df.iloc[index]['Low'])*50
            minProfit += cost
            part=None
            buyMode = None
        #停損
        elif(part - df.iloc[index]['Low'] >= stopLoss and buyMode == "call"):
            minProfit = principal[-1] + (df.iloc[index]['Low'] - part)*50
            minProfit += cost
            part=None
            buyMode = None
        elif(df.iloc[index]['High'] - part >= stopLoss and buyMode == "put"):
            minProfit = principal[-1] + (part - df.iloc[index]['High'])*50
            minProfit += cost
            part=None
            buyMode = None
        elif(df.iloc[index]['Date'] != df.iloc[index+1]['Date']):#該日最後一分鐘
            if(buyMode == 'call'):
                minProfit = principal[-1] + (df.iloc[index]['High'] - part) * 50
                minProfit += cost
            else:
                minProfit = principal[-1] + (part - df.iloc[index]['Low']) * 50
                minProfit += cost
    
    principal.append(minProfit)#The legnth of principal must be same with the len of csv
df['money'] = principal[0:len(principal)-1]
df.to_csv('output.csv')
# %%
print(len(df))
print(len(principal[0:len(principal)-1]))
# %%
#4188