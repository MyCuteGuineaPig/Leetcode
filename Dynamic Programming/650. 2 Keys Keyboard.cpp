/*

  To get the DP solution, analyse the pattern first by generating first few solutions
1: 0
2: 2
3: 3
4: 4
5: 5
6: 5
7: 7
8: 6
9: 6
10: 7
11: 11
12: 7
13: 13
14: 9
15: 8

Now, check the solution.
Eg: n=6
To get 6, we need to copy 3 'A’s two time. (2)
To get 3 'A’s, copy the 1 ‘A’ three times. (3)
So the answer for 6 is 5

Now, take n=9.
We need the lowest number just before 9 such that (9% number =0). So the lowest number is 3.
So 9%3=0. We need to copy 3 'A’s three times to get 9. (3)
For getting 3 'A’s, we need to copy 1 ‘A’ three times. (3)
So the answer is 6

Finally to analyse the below code, take n=81.
To get 81 we check
if (81 % 2 ==0) No
if (81 % 3 ==0) Yes
So we need to copy 81/3 = 27 'A’s three times (3)
Now to get 27 'A’s, we need to copy 27/3= 9 'A’s three times (3)
To get 9 'A’s, we need to copy 9/3=3 'A’s three times (3)
And to get 3 'A’s, we need to copy 3/3=1 'A’s three times (3)
Final answer is 3+3+3+3 = 12

Last Example, n=18
18/2 = 9 Copy 9 'A’s 2 times (2)
9/3=3 Copy 3 'A’s 3 times (3)
3/3=1 Copy 1’A’s 3 times (3)
Answer: 2+3+3= 8

*/


public int minSteps(int n) {
    int[] dp = new int[n+1];

    for (int i = 2; i <= n; i++) {
        dp[i] = i;
        for (int j = i-1; j > 1; j--) {
            if (i % j == 0) {
                dp[i] = dp[j] + (i/j);
                break;
            }
            
        }
    }
    return dp[n];
}

//2020
class Solution {
public:
    int minSteps(int n) {
        vector<int>dp(n+1, n+1);
        dp[1] = 0;
        for(int i = 1; i<=n; ++i){
            for(int j = i*2, time = dp[i]+2; j<=n; j=j+i, time++){ //dp[i]+2 加2 因为一次copy, 一次paste
                dp[j] = min(dp[j], time);
            }
        }
        return dp[n];
    }
};


class Solution {
public:
    int minSteps(int n) {
        int res = 0;
        for(int i = 2; i<=n; i++){
            while(n%i == 0){  //比如 6 - > 18, copy 6, paste => 12, paste =》 18， 一次copy, 两次paste = 3
                res += i;
                n /= i;
            }
        }
        return res;
    }
};


/*
log(n)
*/

class Solution {
public:
    int minSteps(int n) {
        int res = 0;
        for(int i = 2; i<=sqrt(n); i++){
            while(n%i == 0){
                res += i;
                n /= i;
            }
        }
        if(n>1) return res+n;
        return res;
    }
};

/*
We want to find the greatest divisor for our number, 
so we can minimize the number of steps by getting it 
in a buffer and pasting multiple times. 
The quickest way to find the greatest divisor is to start with the smallest prime and work our way up. 
Note that we only need primes up to 31 as n is limited to 1,000 (32 * 32 > 1,000).



 */
class Solution {
public:
    int minSteps(int n) {
       static const int primes[11] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };
        if (n <= 5) return n == 1 ? 0 : n;
        for (auto i : primes)
            if (n % i == 0) return i + minSteps(n / i);
        return n; // prime number.
    }
};



class Solution {
public:
    int minSteps(int n) {
        if(n == 1) return 0;
        int count = 0;
        bool *isPrime = new bool[n + 1];
        for(int i = 2; i < n + 1; i++) isPrime[i] = true;
        for(int i = 2; i < n + 1; i++)
        {
            if(isPrime[i] == true)
            {
                while(n % i == 0)
                {
                    count += i;
                    n /= i;
                }
                for(int j = i * i; j < n + 1; j += i) 
                {
                    if(isPrime[j]) isPrime[j] = false;
                }
            }
        }
        return count;
    }
};