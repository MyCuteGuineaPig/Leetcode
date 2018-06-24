/*
202. Happy Number


Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, 
replace the number by the sum of the squares of its digits, 
and repeat the process until the number equals 1 (where it will stay), 
or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 

Input: 19
Output: true
Explanation: 
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

*/


class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int>set;
        while(n!=1){
            int x = 0;
            while(n){
                int cur = n%10;
                x += cur*cur;
                n = n/10;
            }
            if(set.count(x)) return false;
            set.insert(x);
            n = x;
        }
        return true;
    }
};


//Two pointer
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int>set;
        int slow = n, fast = digitsquare(digitsquare(n));
        while(slow!=fast && fast!= 1){
            slow = digitsquare(slow);
            fast = digitsquare(digitsquare(fast));
        }
        return fast == 1;
    }
    
    int digitsquare(int n){
        int x = 0;
        while(n){
            int cur = n%10;
            x += cur*cur;
            n = n/10;
        }
        return x;
    }
};



//If a number is NOT happy, there is always a 4 in the cycle.
bool isHappy(int n) {
    if (n <= 0) return false;
    
    int magic = 4;
    while (1) {
        if (n == 1) return true;
        if (n == magic) return false;
        int t = 0;
        while (n) {
            t += (n % 10) * (n % 10);
            n /= 10;
        }
        n = t;
    }
}