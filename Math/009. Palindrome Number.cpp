/*
9. Palindrome Number

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?

*/


class Solution {
public:
    bool isPalindrome(int x) {
        if (x<0) return false;
        int cur = 0, n = x;
        while(n){
            cur = cur*10 + n%10;
            n /= 10;
        }
        return x == cur;
    }
};



// Time:  O(logx) = O(1)
// Space: O(1)
class Solution2 {
public:
    bool isPalindrome(int x) {
        if (x<0 || (x!=0 && x%10==0)) return false;
        int rev = 0;
        while (x>rev){
            rev = rev*10 + x%10;
            x = x/10;
        }
        return (x==rev || x==rev/10);
    }
};


// Time:  O(logx) = O(1)
// Space: O(1)
class Solution2 {
public:
    bool isPalindrome(int x) {
        if(x < 0) {
            return false;
        }

        int divisor = 1;
        while (x / divisor >= 10) {
            divisor *= 10;
        }

        for (; x > 0; x = (x % divisor) / 10, divisor /= 100) {
            int left = x / divisor;
            int right = x % 10;
            if (left != right) {
                return false;
            }
        }

        return true;
    }
};