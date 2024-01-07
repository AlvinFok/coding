package main

// import "fmt"
func twoSum(nums []int, target int) []int {
    data := make(map[int]int)
	for index,i := range nums {
		tmp := target - i
		v, ok := data[tmp]
		if(ok){
			//fmt.Print(v,index)
			return []int{v, index}
		}
		data[i] = index
	}
	return []int{}
}

func main(){
	twoSum([]int{3,2,4}, 6)
}