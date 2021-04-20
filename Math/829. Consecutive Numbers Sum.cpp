/*

Math: 

N = x + (x + 1 ) + (x + 2 ) + ... + (x + k)
  = kx + k(k+1)/2

x = N/k - (k + 1)/2

Then: 

N/k >= (k + 1 )/2

2N >= k^2 + k 
2N + 1/4 >= (k + 1/2)^2
k<= (2N + 1/4 )**0.5 - 1/2

for each k, must have 
N/k - (k + 1)/2 is integer

*/
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int count = 0;
        int limit = sqrt(static_cast<double>(2*N) + 0.25)  - 0.5;
        for(int k = 1; k<= limit; ++k){
            double x = static_cast<double>(N) / k - static_cast<double>(k+ 1)/2 ;
            if(x == (int)x)
                ++count;
        }
        return count;
    }
};

class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int count = 0;
        // x > 0 --> N/k - (k + 1)/2 > 0
        int upper_limit = (int)(sqrt(2 * N + 0.25) - 0.5);
        for (int k = 1; k <= upper_limit; ++k) {
            // x should be an integer
            if ((N - k * (k + 1) / 2) % k == 0)
                count++;
        }
        return count;
    }
};

/*

The idea is to use the same iteration limits for k, and to decrease N by k at each step.

N = 15 N = x+1 + ... + x + k

1. k = 1, check the situtation 15 = x + 1 
   N = N - 1 -> 14
   14 % 1 = 0 ; found solution 15 = 14 + 1 

2. k = 2, check the situtation 15 = (x + 1)  + (x + 2)
   N = N - 2 -> 12
   12 % 2 = 0 ; found solution 15 = (6 + 1) + (6 + 2)

3. k = 3, check the situtation 15 = (x + 1)  + (x + 2)  + (x + 3)
   N = N - 3 -> 9
   9 % 3 = 0 ; found solution 15 = (3 + 1) + (3 + 2) + (3 + 3)

4. k = 4, check the situtation 15 = (x + 1)  + (x + 2)  + (x + 3) + (x + 4)
   N = N - 4 -> 5
   5 % 4 != 0 ; no solution for k = 4

5. k = 3, check the situtation 15 = (x + 1)  + (x + 2)  + (x + 3) + (x + 4) + (x + 5)
   N = N - 5 -> 0
   0 % 5 = 0 ; found solution 15 = (0 + 1) + (0 + 2) + (0 + 3) + (0 + 4) + (0 + 5)


*/


class Solution {
public:
    int consecutiveNumbersSum(int N) {
        vector<int>dp(10, 0);
        int count = 0;
        int limit = sqrt(static_cast<double>(2*N) + 0.25)  - 0.5;
        for(int k = 1; k<= limit; ++k){
            N -= k;
            if(N % k == 0)
                ++count;
        }
        return count;
    }
};


/*
x + (x+1) + (x+2)+...+ k terms = N
kx + k*(k-1)/2 = N implies
kx = N - k*(k-1)/2

so N - k*(k-1)/2 must module k


N - k*(k-1)/2 > 0 which implies
k*(k-1) < 2N which can be approximated to
k*k < 2N ==> k < sqrt(2N)
*/


class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int count = 1;
        for( int k = 2; k < sqrt( 2 * N ); k++ ) {
            if ( ( N - ( k * ( k - 1 )/2) ) % k == 0) count++;
        }
        return count;
    }
};
/*

N = (x+1) + (x+2) + ... + (x+k)
N = kx + k(k+1)/2
N * 2 = k(2x + k + 1),where x >= 0, k >= 1

Either k or 2x + k + 1 is odd.

It means that, for each odd factor of N,

*/