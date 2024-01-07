#%%
def reverse( x: int) -> int:
    INT_MAX = 2147483647
    INT_MIN = 2147483648
    ans = 0
    isNegative = False
    if(x < 0):
        isNegative = True
        x = abs(x)
    while(x != 0):
        pop = int(x % 10)
        x //= 10
        if(ans > INT_MAX//10 or (ans == INT_MAX//10 and pop > 7)):
            return 0
        if(ans > INT_MIN//10 or (ans == INT_MIN//10 and pop > 8 and isNegative)):
            return 0
        
        ans = ans * 10 + pop
    if(isNegative):
        ans *= -1
    print(ans)
    return ans

reverse(123)
reverse(-123)
reverse(120)
reverse(0)
reverse(1534236469)
# %%
