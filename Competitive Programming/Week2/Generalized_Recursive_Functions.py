N =int(input())
while N != 0:
    N -= 1
    ab = list(map(int, input().split()))
    dp = []
    zeroes = [0]*100
    for _ in range(100):
        dp.append(zeroes.copy())
    c = int(ab[-2])
    d = int(ab[-1])
    def f(x,y):
        if x > 0 and y > 0:
            return dp[x][y]
        else:
            return d
    for i in range(100):
        for j in range(100):
            ans = c
            for k in range(len(ab)//2-1):
                ans += f(i-ab[2*k], j-ab[2*k+1])
            dp[i][j] = ans
            
    xy = list(map(int, input().split()))
    for i in range(len(xy)//2):
        print(f(xy[2*i], xy[2*i+1]))
    print()