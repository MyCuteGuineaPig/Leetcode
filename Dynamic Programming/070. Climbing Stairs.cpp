
/*
70. Climbing Stairs
https://leetcode.com/problems/climbing-stairs/description/

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.


Example 1:

Input: 2
Output:  2
Explanation:  There are two ways to climb to the top.

1. 1 step + 1 step
2. 2 steps
Example 2:

Input: 3
Output:  3
Explanation:  There are three ways to climb to the top.

1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step


*/


class Solution {
public:
    int climbStairs(int n) {
		if(n == 0) return 0;
        int arr[] = {1,2,3};
		for(int i = 3; i<n ; i++){
			arr[i%3]= arr[(i-1)%3]+arr[(i-2)%3];
		}
		return arr[(n-1)%3];
    }
};



//another solution
int climbStairs(int n) {
    int a = 1, b = 1;
    while (n--)
        a = (b += a) - a; //需要有括号，否则 b += a -a 
    return a;
}

/*
n = 5
 i 1 a 1 b 2
 i 2 a 2 b 3
 i 3 a 3 b 5
 i 4 a 5 b 8
 i 5 a 8 b 13

 */

class Solution {
public:
    int climbStairs(int n) {
        long a = 1, b = 1;
        for(int i = 1; i<=n; ++i){
            b += a;
            a = b - a; //需要有括号，否则 b += a -a 
            //cout<<" i "<<i <<" a "<<a <<" b "<<b<<endl;
        }
        return a;
    }
};