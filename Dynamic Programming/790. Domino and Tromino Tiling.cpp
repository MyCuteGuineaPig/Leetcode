/*
题目重述:

n = 1 ,  tot = 1
    case 1:    |
               |

n = 2,   tot = 2
    case 1:    |  |    case 2:  ————
               |  |             ————

n = 3,   tot = 5
    case 1:    |  |  |   case 2:  ———— |     case 3:  |  ————
               |  |  |            ———— |              |  ————
                ___                  ___
    case 4:    |     |   case 5:  |     |
               |  ___|            |___  |
    
n = 4,   tot = 11
    case 1:        |  |  |  |   case 2:      ———— | |   case 3:      | ———— |
    (from n =3)    |  |  |  |   (from n =3)  ———— | | (from n =3)    | ———— |
                    ___                        ___
    case 4:        |     |  |   case 5:     |     | |   
    (from n =3)    |  ___|  |  (from n =3)  |___  | |

    case 6:        |  |  ————      case 7:    ———— ————
    (from n=2)     |  |  ————     (from n=2)  ———— ————
                       ___                        ___
    case 8:        |  |     |    case 9      | |     |
    (from n=1)     |  |  ___|    (from n=1)  | |___  |
                    ___                                  ___
    case 10:       |    ———— |   case 11:        | ————     |
    (from n=0)     | ———— ___|   (from n = 0)    |___ ————— |

*/


/*
dp[n]=2*dp[n-1]+dp[n-3],

看上面的例子

dp[3] = dp[2] + dp[1] + 2 x dp[0]  ()

dp[4] = dp[3] + dp[2] + 2 x dp[1] + 2 x dp[0]

dp[5] = dp[4] + dp[3] + 2 x dp[2] + 2 x dp[1] + 2 x dp[0]

dp[6] = dp[5] + dp[4] + 2 x dp[3] + 2 x dp[2] + 2 x dp[1] + 2 x dp[0]


2 x dp[n-3]:
               ___            ___
    是 加上    |    |   和   |    |
              | ___|        |___ |

2 x dp[n-4]
               ___ ___           
    是 加上    |       |   和   |  x  x | 
              |  x x  |        |___ ___|

2 x dp[n-5]
 
              ___                       ___
    是 加上    |   x x  |   和   |  x  x    |
              | x x ___|        |___  x  x |


dp[n-1] = dp[n-2] + dp[n-3] + 2 x dp[n-4] + ... + 2 x dp[0]
dp[n] = dp[n-1] + dp[n-2] + 2 x dp[n-3] + ... + 2 x dp[0]

dp[n] = dp[n-1] + (dp[n-2] + dp[n-3] + 2 x dp[n-4] + ... + 2 x dp[0]) + dp[n-3]
      = 2 x dp[n-1] + dp[n-3]


*/

class Solution {
public:
    const long M = 1e9 + 7;
    int numTilings(int N) {
        long dp[1001] = {0};
        dp[0] = 1;dp[1] = 1;dp[2] = 2;
        for(int i = 3; i<=N; i++)
            dp[i] = ((dp[i-1]*2)%M + dp[i-3])%M;
        return dp[N];
    }
};



/*
Three rule: 
T(N) = T(N-1) + T(N-2) + T_up(N-1) + T_down(N-1)

T_up(N) = T_down(N-1) + T(N-2)

T_down(N) = T_up(N-1) + T(N-2)

which can be written 
T(N) = T(N-1) + T(N-2) + T_down(N-2) + T(N-3) + T_up(N-2) + T(N-3)

which can be regrouped as:

T(N) = T(N-1) + T(N-3) + [T(N-2) + T(N-3) + T_up(N-2) + T_down(N-2)]

Now if you recognize the part in square brakets which is simply T(N-1), we arrive at:

T(N) = 2 * T(N-1) + T(N-3).
*/

class Solution {
public:
    const long M = 1e9 + 7;
    int numTilings(int N) {
        long T_N = 1, T_N_1 = 1, T_N_2 =1, T_UP = 0, T_DOWN = 0, T_UP_1=0, T_DOWN_1 = 0;
        for(int i = 2; i<=N; i++){
            T_N = (T_N_1+T_N_2 +T_UP_1+T_DOWN_1)%M;
            T_UP = (T_DOWN_1+T_N_2)%M;
            T_DOWN = (T_UP_1+T_N_2)%M;
            
            T_N_2 = T_N_1; T_N_1 = T_N;
            T_UP_1 = T_UP; 
            T_DOWN_1 = T_DOWN;
            //cout<<T_N<<endl;
        }
        return T_N;
    }
};



//2020 Top-Down
class Solution {
public:
    int numTilings(int N) {
        if(N==1) return 1;
        if(N==2) return 2;
        int mod = pow(10,9)+7;
        vector<long>dp(N+1, 0);
        
        return topDown(dp, N);
    }
    
    long topDown(vector<long>&dp, int N){
        if(N==1 || N == 0) return 1;
        if(N==2) return 2;
        if(dp[N]) 
            return dp[N];
        int mod = pow(10,9)+7;
        return dp[N] = (2 * topDown(dp, N-1) + topDown(dp, N-3))%mod;
    }
};

class Solution {
public:
    int numTilings(int N) {
        int a = 0, b = 1, c = 1, c2, mod = 1e9 + 7;
        while (--N) {
            c2 = (c * 2 % mod + a) % mod;
            a = b;
            b = c;
            c = c2;
        }
        return c;
    }
};



//O(logN) Solution
// Matrix Exponentiation

/*
https://leetcode.com/problems/domino-and-tromino-tiling/discuss/156332/O(log-N)-C%2B%2B-concise-and-clean-and-easy-DP-solution_(%3Az)_
 
 */

/*
图:
https://leetcode.com/problems/domino-and-tromino-tiling/discuss/116612/Easy-to-understand-O(n)-solution-with-Drawing-Picture-Explanation!
/ 1 1 2 \  /f(i-1)\     / f(i) \
| 1 0 0 |  |f(i-2)|  =  |f(i-1)|
\ 0 1 1 /  \g(i-1)/     \ g(i) /
*/
#define M 1000000007
#define ll long long
class Solution {
public:
    int numTilings(int N) {
        if (N <= 2) return N;
        vector<vector<ll>> r;
        r.push_back({1, 1, 2}); //2g(i-1),  因为多出来的一部分, T_up(N) = T_down(N)
        r.push_back({1, 0, 0});
        r.push_back({0, 1, 1});
        r = power(r, N - 2); //N 是从3开始
        return (r[0][0] * 2 + r[0][1] + r[0][2]) % M;  //f(2) = 2, f(1) = 1, g(i) = 1
    }
    
    vector<vector<ll>> power(vector<vector<ll>>& x, int n) {
        if (n == 1) return x;
        int m = n >> 1;
        auto r = power(x, m);
        r = multiply(r, r);
        if (n & 1) {
            r = multiply(r, x);
        }
        return r;
    }
    
private:
    vector<vector<ll>> multiply(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
        vector<vector<ll>> r(3, vector<ll>(3, 0));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    r[i][j] += a[i][k] * b[k][j];
                }
                r[i][j] %= M;
            }
        }
        return r;
    }
};