package main
import "fmt"
func pivotIndex(nums []int) int {
    leftSum, rightSum, sum, ans := 0, 0, 0, -1
	for _, v := range nums {
		sum += v
	}
	if(sum - nums[0] == 0){
		return 0;
	}

	for i := 1;i<len(nums);i++ {
		leftSum += nums[i-1]
		rightSum = sum - leftSum - nums[i];
		if(leftSum == rightSum){
			ans = i;
			break
		}
	}
	fmt.Println(ans)
	return ans;
}

func main() {
	pivotIndex([]int{1,7,3,6,5,6})
	pivotIndex([]int{1,2,3})
	pivotIndex([]int{2,1,-1})
}