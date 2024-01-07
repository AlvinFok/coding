# %%
import xlsxwriter
import pandas as pd
import os
import numpy as np
import re




def getFilePath():
    dataPath = []
    filePath = "Data/週選"
    # get all data file path
    for yearData in os.listdir(filePath):
        for monthData in os.listdir(filePath + "/" + yearData):
            for weekData in os.listdir(filePath + "/" + yearData + "/" + monthData):
                # print(weekData)
                if ('.xlsx' not in weekData):
                    continue
                dataPath.append(filePath + "/" + yearData +
                                "/" + monthData + "/" + weekData)
    dataPath.sort()
    return dataPath
    # print(dataPath[0].split("/")[-1].split('.')[0])
    # print(dataPath[0].split('週選/')[1].split('.xlsx')[0])


def createProfitFile(dataPath:list):
    resultIndex = []
    data = []
    profitList = np.arange(lowestProfit, highestProfit + profitInterval, profitInterval)

    # dataPath = ['week2.xlsx']# for testing one file
    for filePath in dataPath:
        # print(filePath)
        file = pd.ExcelFile(filePath)
        sheetLength = len(file.sheet_names)
        sheetList = file.sheet_names
        if (len(sheetList) <= 1):#只有一天的交易日
            continue
        # filePath = '週選/' + filePath# for testing one file
        for index, sheetName in enumerate(sheetList):
            # if('Fri' not in sheetName and 'Mon' not in sheetName and 'Tue' not in sheetName):  # 只要星期五、一、二
            #     #print(sheetName, "skipped")
            #     continue
            # print(re.split('(\d+){2}', sheetName))
            # x軸的名字 分割出檔案的名字
            resultIndex.append(filePath.split(
                '週選/')[1].split('.xlsx')[0] + '_' + re.split('(\d+){2}', sheetName)[2])

            rowData = []
            df = pd.read_excel(file, sheet_name=sheetName)
            # If buyMode = 開倉收盤,buyStrikePrice = 1, 開倉收盤履約價+50
            onePartPrice = df[buyMode + callOrPut][6 + buyStrikePrice]#選擇的履約價一口價錢
            strikePrice = df['履約價'][6 + buyStrikePrice]  #選擇的履約價
            cost = costPerTimes / 50  # 一點50NTD

            if (onePartPrice == 0):  # 買入價是0
                part = 0
            else:
                part = int(cost / onePartPrice)  # 買入的部位

            
            finalSheet = pd.read_excel(file, sheet_name=sheetList[sheetLength-1])
            finalPrice = finalSheet[finalSheet['履約價'] == strikePrice]['結算' + callOrPut]  # 買入的履約價的結算價
            if(len(finalPrice.values) == 0):#找不到買入的履約價的結算價
                finalPrice = 0
            else:
                finalPrice = finalSheet[finalSheet['履約價'] == strikePrice]['結算' + callOrPut].values[0]
                
            if (buyMode == '開倉收盤'):#收盤買入必定從下個交易日開始所以index + 1
                index += 1
            
            rowData.append('{:.2f}'.format(onePartPrice))  # 一口成本
            rowData.append('{:d}'.format(part))  # 買入的部位數量
            rowData.append('{:d}'.format(int(strikePrice)))  # 買入的履約價

            # print(sheetName, df['開倉收盤'][5], '元買入')
            for profit in profitList:  # 針對不同利潤做賣出的動作

                # part = int(10000/onePartPrice)#一萬元可買入的部位數量
                sellTimes = 2  # 一次賣出部位的數量
                # profit = 0.5#50%利潤
                
                rowData.append('{:.2f}'.format(onePartPrice * profit))#理論獲利點
                
                for i in range(index, sheetLength):  # 用買入的成本與之後的日子的開盤及收盤確認收益
                    if(sellTimes <= 0 or onePartPrice == 0):  # 沒有部位可以賣出或買入價是0
                        break

                    df = pd.read_excel(file, sheet_name=sheetList[i])
                    # 最高價賣出
                    maxPrice = df[df['履約價'] == strikePrice]['最高價' + callOrPut]  # 買入的履約價的最高價
                    if (len(maxPrice.values) == 0):
                        maxPrice = 0
                    else:
                        maxPrice = maxPrice.values[0]

                    # 一次賣出全部
                    if(sellTimes > 0 and (maxPrice-onePartPrice)/onePartPrice >= profit):  # 有可賣出的次數及利潤高於設定
                        sellTimes = 0
                        # print(sheetList[i], '開盤賣出{:.2f}%\n買入價{:.2f}\n開盤價{:.2f}\n獲利{:.2f}'.format(profit*100, onePartPrice, df['開倉開盤'][5], df['開倉開盤'][5]/onePartPrice*100))
                        # profit += 0.5#每次賣出後利潤提升50%才賣出下一次
                        # part = int(part / 2)
                        # rowData.append('{:.2f}%'.format(((maxPrice - onePartPrice) / onePartPrice)*100))#獲利率
                        rowData.append('{:.2f}'.format(maxPrice - onePartPrice))  # 真實獲利點
                        rowData.append('{:.2f}'.format(onePartPrice * profit * 50))  # 理論每口獲利
                        rowData.append('{:.2f}'.format((maxPrice - onePartPrice) * 50))  # 真實每口獲利
                        rowData.append('{:.2f}'.format(onePartPrice * profit * 50 * part))  # 理論每口獲利 * 買入的口數 = 理論總獲利
                        rowData.append('{:.2f}'.format((maxPrice - onePartPrice) * 50 * part))  # 真實每口獲利 * 買入的口數 = 真實總獲利


                if (sellTimes > 0):  # 部位沒有完全賣出被結算
                    # print(sheetName, sellTimes, '次沒有賣出')
                    # for i in range(sellTimes):
                    # print(type(finalPrice))
                    #虧了所有成本
                    rowData.append('{:.2f}'.format(finalPrice - onePartPrice))# 真實獲利點
                    rowData.append('{:.2f}'.format((finalPrice - onePartPrice) * 50))# 理論每口獲利
                    rowData.append('{:.2f}'.format((finalPrice - onePartPrice) * 50))# 真實每口獲利
                    rowData.append('{:.2f}'.format((finalPrice -onePartPrice)* 50 * part))  # 理論每口獲利 * 買入的口數 = 理論總獲利
                    rowData.append('{:.2f}'.format((finalPrice - onePartPrice) * 50 * part))  # 真實每口獲利 * 買入的口數 = 真實總獲利
                    
                    # rowData.append('{:.2f}%(結算)'.format(finalPrice/onePartPrice))
            data.append(rowData)
            # print(rowData)
        print(filePath, 'Finished')

    # print(len(data[0]))
    # 開盤及收盤賣出
    # df = pd.DataFrame(data, columns=['兩口成本', '50100_50獲利點', '50100_50獲利率','50100_100獲利點', '50100_100獲利率','100150_100獲利點', '100150_100獲利率', '100150_150獲利點', '100150_150獲利率', '150200_150獲利點', '150200_150獲利率', '150200_200獲利點', '150200_200獲利率'], index=resultIndex)
    # for i in data:
    #     if (len(i) > 10):
    #         print(i)
    columns = ['一口成本', '口數', '履約價{}'.format(buyStrikePrice*50)]
    for profit in profitList:#'50%', '50%獲利點', '50%每口獲利',, '50每口獲利真實價格', 'Profit50'
        columns.append('{:d}%理論獲利點'.format(int(profit * 100)))
        columns.append('{:d}%真實獲利點'.format(int(profit * 100)))
        columns.append('{:d}%理論每口獲利'.format(int(profit * 100)))
        columns.append('{:d}%真實每口獲利'.format(int(profit * 100)))
        columns.append('{:d}%理論總獲利'.format(int(profit * 100)))
        columns.append('{:d}%真實總獲利'.format(int(profit * 100)))

    df = pd.DataFrame(data, columns=columns, index=resultIndex)

    df.to_excel('{}_{}_履約價{}_獲利{}-{}_本金{}萬_每次{}萬_Tmp.xlsx'.format(buyType, buyMode, buyStrikePrice*50, int(lowestProfit*100), int(highestProfit*100), int(principal / 10000), int(costPerTimes / 10000)))


# %%
def daySplit(fileName):
    df = pd.read_excel(fileName)

    day3 = []
    day4 = []
    day5 = []
    day1 = []
    day2 = []
    day3_2 = []
    # print(df.iloc[0, :1].values[0])
    for i in range(len(df)):
        # print(df.iloc[i])
        if ('Wed_1' in df.iloc[i, :1].values[0]):
            day3_2.append(df.iloc[i])
        elif ('Wed' in df.iloc[i, :1].values[0]):
            day3.append(df.iloc[i])
        elif ('Thu' in df.iloc[i, :1].values[0]):
            day4.append(df.iloc[i])
        elif ('Fri' in df.iloc[i, :1].values[0]):
            day5.append(df.iloc[i])
        elif ('Mon' in df.iloc[i, :1].values[0]):
            day1.append(df.iloc[i])
        elif('Tue' in df.iloc[i, :1].values[0]):
            day2.append(df.iloc[i])

    # print(type(day5[0]))
    writer = pd.ExcelWriter('{}_{}_履約價{}_獲利{}-{}_本金{}萬_每次{}萬.xlsx'.format(buyType, buyMode, buyStrikePrice*50, int(lowestProfit*100), int(highestProfit*100), int(principal / 10000), int(costPerTimes / 10000)), engine='xlsxwriter')

    df1 = pd.concat(day3, axis=1).T
    df2 = pd.concat(day4, axis=1).T
    df3 = pd.concat(day5, axis=1).T
    df4 = pd.concat(day1, axis=1).T
    df5 = pd.concat(day2, axis=1).T
    df6 = pd.concat(day3_2, axis=1).T

    #計算每種獲利率的虧損
    dfList = [df1, df2, df3, df4, df5, df6]
    profitList = np.arange(lowestProfit, highestProfit + profitInterval, profitInterval)
    sheetNameLsit = ['Wed', 'Thu', 'Fri', 'Mon', 'Tue', 'Wed_1']

    for df, sheetName in zip(dfList, sheetNameLsit):
        columnsIndex = 4#四個不變的column [日期，一口成本，口數，履約價] 每一個sheet要reset
        for index, profit in enumerate(profitList):
            
            principalPerSheet = principal
            columnData = []
            #理論虧損
            for profitPerOnce in df['{}%理論總獲利'.format(int(profit * 100))]:
                if (profit == 0.35):
                    print(profitPerOnce)
                principalPerSheet += profitPerOnce#把獲利加入本金
                columnData.append(principalPerSheet)
            
            df.insert(columnsIndex + (index + 1) * 6, '{}%理論虧損'.format(int(profit * 100)), columnData)#加在真實總獲利後面
            columnsIndex += 1 #加了一個新的column
            #真實虧損
            principalPerSheet = principal
            columnData = []
            for profitPerOnce in df['{}%真實總獲利'.format(int(profit * 100))]:
                if (profit == 0.35):
                    print(profitPerOnce)
                principalPerSheet += profitPerOnce#把獲利加入本金
                columnData.append(principalPerSheet)
            
            df.insert(columnsIndex + (index + 1) * 6, '{}%真實虧損'.format(int(profit * 100)), columnData)#加在理論虧損後面
            columnsIndex += 1 #加了一個新的column
        df.to_excel(writer, sheet_name=sheetName)


    writer.save()
    print('All Finished')
#%%
def dayCombine(days:list, combineProfit:list, fileName):
    df = pd.read_excel(fileName)

    combineData = []
    dayList = ['Wed', 'Thu', 'Fri', 'Mon', 'Tue', 'Wed_1']
    sheetName = ','.join([dayList[i] for i in days])

    # print(df.iloc[0, :1].values[0])
    for i in range(len(df)):
        # print(df.iloc[i])
        #輸入的日子
        for day, profit in zip(days, combineProfit):
            #Web是 Web 和 Web_1 的substring所以要判斷接下來的row是否Wed_1
            #如果是的話要看使用有否選擇Wed_1，沒有則continue
            if('Wed_1' in df.iloc[i, :1].values[0] and day != 5):
                continue
            #想要的日子及獲利
            if (dayList[day] in df.iloc[i, :1].values[0]):
                combineData.append(pd.Series(df.iloc[i, 0:4]).append(pd.Series(df.iloc[i, 4+(profit//5 - 2)*6: 4+(profit//5 - 2)*6 + 6].values , index=['理論獲利點', '真實獲利點', '理論每口獲利', '真實每口獲利', '理論總獲利', '真實總獲利'])))
            

    # print(type(day5[0]))
    writer = pd.ExcelWriter('{}_{}_履約價{}_獲利{}-{}_本金{}萬_每次{}萬_混合獲利.xlsx'.format(buyType, buyMode, buyStrikePrice*50, int(lowestProfit*100), int(highestProfit*100), int(principal / 10000), int(costPerTimes / 10000)), engine='xlsxwriter')

    df = pd.concat(combineData, axis=1).T
    # print(df.head())
    df['理論虧損'] = df['理論總獲利'].cumsum() + principal
    df['真實虧損'] = df['真實總獲利'].cumsum() + principal
    

    #計算每種獲利率的虧損
    
    # profitList = np.arange(lowestProfit, highestProfit + profitInterval, profitInterval)
    
    
    # columnsIndex = 4#四個不變的column [日期，一口成本，口數，履約價] 每一個sheet要reset
    # for index, profit in enumerate(profitList):
        
    #     principalPerSheet = principal
    #     columnData = []
    #     #理論虧損
    #     for profitPerOnce in df['{}%理論總獲利'.format(int(profit * 100))]:
    #         principalPerSheet += profitPerOnce#把獲利加入本金
    #         columnData.append(principalPerSheet)
        
    #     df.insert(columnsIndex + (index + 1) * 6, '{}%理論虧損'.format(int(profit * 100)), columnData)#加在真實總獲利後面
    #     columnsIndex += 1 #加了一個新的column

    #     #真實虧損
    #     principalPerSheet = principal
    #     columnData = []
    #     for profitPerOnce in df['{}%真實總獲利'.format(int(profit * 100))]:
    #         principalPerSheet += profitPerOnce#把獲利加入本金
    #         columnData.append(principalPerSheet)
        
    #     df.insert(columnsIndex + (index + 1) * 6, '{}%真實虧損'.format(int(profit * 100)), columnData)#加在理論虧損後面
    #     columnsIndex += 1 #加了一個新的column

    df.to_excel(writer, sheet_name=sheetName)

    writer.save()
    print('All Finished')
#%%
buyType = int(input('買權\n1.Call\n2.Put\n'))#要買Call or Put
if(buyType == 1):
    buyType = 'Call'
    callOrPut = ''
elif(buyType == 2):
    buyType = 'Put'
    callOrPut = '.1'
else:
    print('輸入錯誤')
    quit()

buyMode = int(input('1.開倉開盤\n2.開倉收盤\n'))  # 開盤買入\收盤買入
# let buyMode become string increase readability
if (buyMode == 1):
    buyMode = '開倉開盤'
elif (buyMode == 2):
    buyMode = '開倉收盤'
else:
    print('輸入錯誤')
    quit()

buyStrikePrice = int(int(input('履約價-300-300\n')) / 50)  # 要買入的覆約價
lowestProfit = int(input('最低獲利率\n')) * 0.01 #最低獲利率
highestProfit = int(input('最高獲利率\n')) * 0.01  #最高獲利率
profitInterval = int(input('獲利間隔\n')) * 0.01  #獲利間隔
principal = int(input('本金(萬)\n')) * 10000  #本金
costPerTimes = int(input('每次入場的金額(萬)\n')) * 10000

fileName = '{}_{}_履約價{}_獲利{}-{}_本金{}萬_每次{}萬_Tmp.xlsx'.format(buyType, buyMode, buyStrikePrice*50, int(lowestProfit*100), int(highestProfit*100), int(principal / 10000), int(costPerTimes / 10000))

if(not os.path.isfile(fileName)):
    dataPath = getFilePath()
    #
    createProfitFile(dataPath)


dateMod = int(input('1.日期分開\n2.日期合並\n'))
if(dateMod == 1):
    daySplit(fileName)
elif(dateMod == 2):
    combineDay = list(map(int,input('合并的日子:\n0:Wed\n1:Thu\n2:Fri\n3:Mon\n4:Tue\n5:Wed_1\n').split()))
    combineProfit = list(map(int,input('合并的獲利(10-300):\n').split()))
    dayCombine(combineDay, combineProfit, fileName)

# %%
import time
def getDate():
    a = time.strptime("Wed 00 Nov 2020", "%a %W %b %Y")
    print(time.strftime("%Y",a), time.strftime("%m",a), time.strftime("%d",a))

# %%
