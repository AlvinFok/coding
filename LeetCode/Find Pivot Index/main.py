#%%
def pivotIndex(nums: list[int]) -> int:
    leftSum, rightSum, Sum = 0, 0, 0
    ans = -1
    Sum = sum(nums)
    if(Sum - nums[0] == 0):
        return 0
    
    for i in range(1, len(nums)):
        leftSum += nums[i-1]
        rightSum = Sum - leftSum - nums[i]
        if(leftSum == rightSum):
            ans = i
            break
    print(ans)
    return ans

pivotIndex([1,7,3,6,5,6])
pivotIndex([1,2,3])
pivotIndex([2,1,-1])
# %%
