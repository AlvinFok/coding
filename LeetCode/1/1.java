import java.util.HashMap;
import java.util.Map;

class Solution {
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer>data = new HashMap<>();
        int[] ans = new int[2];
        for(int i = 0; i < nums.length; i++) {
            int tmp = target - nums[i];
            if(data.containsKey(tmp)){
                System.out.println(data.get(tmp) + " " + i);
                ans[0] = data.get(tmp);
                ans[1] = i;
            }
            data.put(nums[i],i);
        }
        return ans;
    }

    public static void main(String[] args) {
        int[] tmp;
        tmp = twoSum(new int[] {3,2,4}, 6);
    }
}