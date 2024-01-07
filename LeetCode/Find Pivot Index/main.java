import java.util.Arrays;

class Solution {
    public static int pivotIndex(int[] nums) {
        int leftSum = 0, rightSum = 0, sum = 0, ans = -1;
        sum = Arrays.stream(nums).sum();
        
        if(sum - nums[0] == 0)return 0;
        for(int i = 1; i < nums.length; i++){
            leftSum += nums[i-1];
            rightSum = sum - leftSum - nums[i];
            if(leftSum == rightSum){
                ans = i;
                break;
            }
        }
        System.out.println(ans);
        return ans;
    }
    public static void main(String[] args) {
        pivotIndex(new int[] {1,7,3,6,5,6});
        pivotIndex(new int[] {1,2,3});
        pivotIndex(new int[] {2,1,-1});
    }
}