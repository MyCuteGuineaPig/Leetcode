/*
793. Preimage Size of Factorial Zeroes Function

Let f(x) be the number of zeroes at the end of x!. (Recall that x! = 1 * 2 * 3 * ... * x, and by convention, 0! = 1.)

For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has 2 zeroes at the end. 
Given K, find how many non-negative integers x have the property that f(x) = K.

Example 1:
Input: K = 0
Output: 5
Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.

Example 2:
Input: K = 5
Output: 0
Explanation: There is no x such that x! ends in K = 5 zeroes.
Note:

K will be an integer in the range [0, 10^9].

*/





/*
when n>=5, the number of zeros in n! is the count of factors of 5. This function nzero has a complexity of O(log(n)).

therefore, (5K)! should have more than K zeros, if K >= 1.

use a binary search in [1, 5K] to find the smallest number n, so that nzero(n) >= K. This has a complexity of O(log(5K)).

if 'nzero(n) == K', the numbers in range [n, n + 5 - n % 5) are all valid candidates. As mentioned by @vikchernij, 
because the valid n should be always a multiple of 5, the result should be always 5 in this case.

otherwise, there is no valid numbers.

the total complexity is O(log(5K) * log(5K)), which is very small.

*/



// Time:  O((logn)^2)
// Space: O(1)

class Solution {
public:
    int preimageSizeFZF(int K) {
        long l = 0, r = static_cast<long>(K)*5;  //要用long，否则会有overflow
        while(l<r){
            long mid = (l+r)>>1;
            long zeros = countZero(mid);
            if(zeros>=K) r = mid;
            else l = mid+1;
        }
        return countZero(l) == K ? 5 : 0;
    }

    int countZero(long val){
        long cnt = 0;
        while(val>0){
            cnt += val/5;
            val /= 5;
        }
        return cnt;
    }
};



class Solution {
public:
    int preimageSizeFZF(int K) {
        
        long long lo = 0;
        long long hi = (long long )K * 5 ; 

        while( lo <= hi ){
            long long md = (lo + hi) / 2;
            long long save = md;
            long long tot = 0;
            while( md >= 5 ){
                tot += md/5; 
                md/=5;
            }
                 if(tot > K) hi = save - 1; 
            else if(tot < K) lo = save + 1; 
            else{
                return 5;
            }
        }
        return 0;
    }
};


class Solution {
public:
    int preimageSizeFZF(int K) {
        const int p = 5;
        int left = 0, right = p * K;
        while (left < right) {
            const int mid = left + (right - left) / 2;
            cout<<"mid "<<mid<<" left "<<left<<" right "<<right<<endl;
            if (countOfFactorialPrimes(mid, p) >= K) {
                right = mid;
            } else {
                left = mid + 1;
            }
            cout<<"aftermid "<<mid<<" left "<<left<<" right "<<right<<endl;
        }
        return countOfFactorialPrimes(left, p) == K ? p : 0;
    }

private:
    int countOfFactorialPrimes(int n, int p) {
        int cnt = 0;
        for (; n > 0; n /= p) {
            cnt += n / p;
            cout<<"cnt "<<cnt<<" n "<<n<<endl;
        }
        return cnt;
    }
};



/*

math solution O(logn)

Let g(x)=f(x)-f(x-1), so f(x)=sum{g(x)}.
We can find that
g(x)=0 if x%5!=0,
g(x)>=1 if x%5==0,
g(x)>=2 if x%25==0,
...
List g(x) as follows:
x: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 ...
g(x): 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 ...
x: 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120 125 ...
g(x): 1 1 1 1 2 1 1 1 1 2 1 1 1 1 2 1 1 1 1 2 1 1 1 1 3 ...
so g(x) will always repeat a sequnce for 5 times and +1 at the last number of the sequence.
Some K is/are skipped if g(x)>1.
For example, when x=25, g(x)=2, K=5 is skipped(there is no x that f(x)=5), and when x=125, g(x)=3, K=29, 30 are skipped.
We can find that 5(=1*5), 11(=6*1+5), 17(=6*2+5), 23(=6*3+5), 29(=6*4+5), 30(=6*5), 36(=31+5), 42(=31+6+5), 48(=31+6*2+5), ... are skipped.

比如48”

48 sum[i] 61035156
48 sum[i] 12207031
48 sum[i] 2441406
48 sum[i] 488281
48 sum[i] 97656
48 sum[i] 19531
48 sum[i] 3906
48 sum[i] 781
48 sum[i] 156
48 sum[i] 31
17 sum[i] 6
5 sum[i] 1 return 0

Let me know if there are ambiguities.


Same idea. Another explanation could be:

First the answer is either 0 or 5 without doubt.
Let x = a0 * 5^0 + a1 * 5^1 + a2 * 5^2 + ....... where a0, a1, a2 ..... are less than 5 and greater or equal to 0.

Then f(x) = x / 5 + x / 5^2 + x / 5^3 + ......
= a1 * 1 + a2 * (1 + 5) + a3 * (1 + 5 + 5^2) + ....
= a1 * sum[0] + a2 * sum[1] + a3 * sum[2] + .... as in the code above

So if any one of the a above is not [0, 4] for a given number K, it violate the constraints so we should return 0.
Otherwise return 5.

*/

class Solution {
public:
    int preimageSizeFZF(int K) {
        int sum[13]={1};
        for (int i=1; i<13; i++) sum[i]=sum[i-1]*5+1;
        //for(auto i:sum){
        //    cout<<i<<" ";
        //}
        for (int i=12; i>=0; i--) {
            if (K/sum[i]==5) return 0;
            K=K%sum[i];
        }
        return 5;
    }
};
