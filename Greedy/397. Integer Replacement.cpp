/*
Hint: 
 tricky,如果是奇数, 看第二个bit决定+1, -1
 */

/*


in binary form 我们需要remove 尽可能多的1， 

111011 -> 111010 -> 11101 -> 11100 -> 1110 -> 111 -> 1000 -> 100 -> 10 -> 1
And yet, this is not the best way because

111011 -> 111100 -> 11110 -> 1111 -> 10000 -> 1000 -> 100 -> 10 -> 1


See? Both 111011 -> 111010 and 111011 -> 111100 remove the same number of 1's, but the second way is better.

尽可能的把1 往左侧堆积，比如111100， 除以4后，+1，可以消除很多1

So, we just need to remove as many 1's as possible, 
doing +1 in case of a tie? Not quite. 3是个例外
The infamous test with n=3 fails for that strategy because 11 -> 10 -> 1 is better than 11 -> 100 -> 10 -> 1.
Fortunately, that's the only exception (or at least I can't think of any other, and there are none in the tests).

So the logic is:

If n is even, halve it.
If n=3 or n-1 has less 1's than n+1, decrement n.
Otherwise, increment n.

另一外一种思路， 当N时奇数时，只有第2个bit matter
如果第二个bit是 '1', N+1 will remove at least one '1' in N. 1011 + 1 = 1100, 1111 + 1 = 10000. 
However, N - 1 will remove only one '1'. 1011 - 1 = 1010 or 1111 - 1 = 1110. So we favor N + 1 here.

如果第二个bit是 '0', N+1 will remove zero '1'. 1001 + 1 = 1010. N -1 will remove one '1'. 1001 - 1 = 1000.

而operation是当是奇数，只能加减一，不能消除位数，而是偶数时候，可以消除位数，比如1011只能变成1010 or 1100, 而1100 可以变成110, 
所以目标是尽可能消除更多的1，让后面operation减小 从而更快减小位数

*/
class Solution {
public:
    int integerReplacement(long n) { //需要把int 改成long，否则会overflow
        int step = 0;
        while(n>1){
            if(!(n & 1)){
                n = n>>1;
            }
            else{
                if( n == 3 || ((n-1) & 2) == 0) // check if n-1 % 4 == 0
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


/*
除了3以外，看奇数 是+1 除以2的次数更多点，看是-1 除以2的次数更多点
*/
class Solution {
public:
    int integerReplacement(long n) {
        int step = 0;
        while(n!=1){
            //cout<<n<<" step "<<step<<endl;
            if( n & 1){
                if(n==3) n--;
                else n = countdiv2(n+1) > countdiv2(n-1) ? n+1 : n-1;
            }
            else
                n /= 2;
            step++;
        }
        return step;
    }
    
    int countdiv2(long n){
        int count = 0;
        while(!(n & 2)){
            n /=2;
            count++;
        }
        return count;
    }
};


//recursion
class Solution {
public:
    int check(long long int n)
    {
        if(n == 1) return 0;
        if(n % 2) 
        {
            //if(n == 2147483647) return check(107374) + 2;
            return min(check(n-1), check(n+1)) + 1;
        }
        return check(n/2) + 1;
    }
    int integerReplacement(int n) {
        //cout << INT_MAX + 1 << endl;
        return check(n);
    }
};


//2020 
class Solution {
public:
    int integerReplacement(int n) {
        unordered_map<long,int>dp;
        return topDown(n, dp);
    }
    
    int topDown(long n, unordered_map<long,int>&dp){
        if(n == 1) return 0;
        if(dp.count(n)) return dp[n];
        if (n % 2 == 0)
            return dp[n] = topDown(n/2, dp) + 1;
        return dp[n] = min(topDown(n+1,dp), topDown(n-1, dp))+1;
    }
};