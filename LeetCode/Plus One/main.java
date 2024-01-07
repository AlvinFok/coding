import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

class Solution {
    public static int[] plusOne(int[] digits) {
        boolean addTen = false;
        int n = digits.length - 1;
        digits[n] += 1;
        if(digits[n] >= 10) {
            if(n == 0){
                return new int[] {1,0};
            }
            else{
                digits[n] -= 10;
                addTen = true;
            }
        }

        for(int i = n-1;i>=0;i--){
            if(addTen) {
                digits[i] += 1;
                addTen = false;
                if(digits[i] >= 10) {
                    digits[i] -= 10;
                    addTen = true;
                }
            }
            else{
                break;
            }
        }
        if(addTen) {
            int[] ans = new int[n+2];
            ans[0] = 1;
            for(int i = 1;i<n+1;i++){
                ans[i] = digits[i-1];
            }
            return ans;
        }
        return digits;
    }

    public static void print(int[] array){
        for(int i=0;i<array.length;i++){
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }
    public static void main(String[] args) {
        
        print(plusOne(new int[]{1,2,3}));
        
        print(plusOne(new int[]{4,3,2,1}));
        
        print(plusOne(new int[]{0}));
        
        print(plusOne(new int[]{9}));
        
        print(plusOne(new int[]{9,9}));
    }
}