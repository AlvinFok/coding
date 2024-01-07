package main

import (
	"fmt"
	"math"
)

func reverse(x int) int {
    ans := 0
	for x != 0{
		var pop int = x % 10
		x /= 10
		if(ans > math.MaxInt32/10 ||(ans == math.MaxInt32/10 && pop > 7)){
			return 0
		}

		if(ans < math.MinInt32/10 ||(ans == math.MinInt32/10 && pop < -8)){
			return 0
		}
		ans = ans * 10 + pop
	}
	// fmt.Println(ans)
	return ans
}

func main() {
	reverse(123)
	reverse(-123)
	reverse(120)
	reverse(0)
	reverse(1534236469)
}