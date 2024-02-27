#%%


class PotterKata:
    
    def __init__(self):
        self.discount = [1, 0.95, 0.9, 0.8, 0.75]#If only buy same books then no discount
    
    def getPrice(self, books:list):
        key = range(len(books))
        books = dict(zip(key, books))#cost list to dict
        
        price = 0
        tenPercentDiscount = False
        twentyFivePercentDiscount = False
        
        
        while self.__getNumbersOfBooks(books) > 0:
            numberOfDistinctBooks = self.__getNumberOfDistinctBooks(books)
            if numberOfDistinctBooks == 5:
                twentyFivePercentDiscount = True
            elif numberOfDistinctBooks == 3:
                tenPercentDiscount = True
                
            discount = self.__getDiscount(numberOfDistinctBooks-1)
            price += numberOfDistinctBooks * 8 * discount
            
            if twentyFivePercentDiscount and tenPercentDiscount:#25% and 10% can replace by two 20%
                price -= 5 * 8 * 0.75
                price -= 3 * 8 * 0.9
                price += (4 * 8 * 0.8) * 2
                
            
            books = self.__removeOneOfEachBooks(books, numberOfDistinctBooks)#update books state
                    
        
        return price

    def __removeOneOfEachBooks(self, books, numberOfDistinctBooks):
        for key in books:
            if numberOfDistinctBooks == 0:
                break
            if books[key] > 0:
                books[key] -= 1
                numberOfDistinctBooks -=1
    
        return books
    
    def __getDiscount(self, index):
        return self.discount[index]
    
    def __getNumbersOfBooks(self, books:dict):
        return sum(list(books.values()))
    
    def __getNumberOfDistinctBooks(self, books:dict):
        return sum(i > 0 for i in books.values())
    


potterKata = PotterKata()
books = [1,0,0,0,0]
print(potterKata.getPrice(books))
# %%
