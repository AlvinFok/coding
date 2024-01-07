#%%
def twoSum(nums: list[int], target: int) -> list[int]:
    data ={}
    for index, i in enumerate(nums):
        tmp = target - i
        if(tmp in data.keys()):
            print(data[tmp], index)
            return [data[tmp], index]
        data[i] = index

twoSum([3,3],6)
# %%
