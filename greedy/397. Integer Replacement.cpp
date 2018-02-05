
/*
397. Integer Replacement
https://leetcode.com/problems/integer-replacement/description/

Given a positive integer n and you can do operations as follow:

If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?

Example 1:

Input:
8

Output:
3

Explanation:
8 -> 4 -> 2 -> 1
Example 2:

Input:
7

Output:
4

Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1

*/

class Solution {
public:
    int integerReplacement(long n) {
        int step = 0;
        while(n>1){
            if(!(n & 1)){
                n = n>>1;
            }
            else{
                if(n == 3) step += 1, n=1;
                else if(((n-1) & 2) == 0) // check if n-1 % 4 == 0
                    n--;
                else 
                    n++;
            }
            step++;
            //cout<<n<<" st "<<step<<endl;
        }
        return step;
    }
};