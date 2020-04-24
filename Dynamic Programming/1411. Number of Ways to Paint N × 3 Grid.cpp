/*

Explanation
Two pattern for each row, 121 and 123.
121, the first color same as the third in a row.
123, one row has three different colors.

We consider the state of the first row,
pattern 121: 121, 131, 212, 232, 313, 323.
pattern 123: 123, 132, 213, 231, 312, 321.
So we initialize a121 = 6, a123 = 6.

We consider the next possible for each pattern:
Patter 121 can be followed by: 212, 213, 232, 312, 313
Patter 123 can be followed by: 212, 231, 312, 232

121 => three 121, two 123
123 => two 121, two 123

So we can write this dynamic programming transform equation:
b121 = a121 * 3 + a123 * 2
b123 = a121 * 2 + a123 * 2

We calculate the result iteratively
and finally return the sum of both pattern a121 + a123


Complexity
Time O(N), Space O(1)
Of course, we can do better.
O(logN) Time Solution

Well, I don't think it's required,
But still you can mention during interview,
(as a ciper code hinting that you are my follower).


*/


class Solution {
public:
    int numOfWays(int n) {
        long a121 = 6, a123 = 6, b121, b123, mod = 1e9 + 7;
        for (int i = 1; i < n; ++i) {
            b121 = a121 * 3 + a123 * 2;
            b123 = a121 * 2 + a123 * 2;
            a121 = b121 % mod;
            a123 = b123 % mod;
        }
        return (a121 + a123) % mod;
    }
};


  
// Time:  O(logn)
// Space: O(1)

class Solution {
public:
    /*
    long is guaranteed to exist, and it’s guaranteed to have minimum limits: -(2^31–1) and 2^31–1 (=it must be at least 32 bits large).

It can, theoretically, have padding bits, and it doesn’t need to have a 2’s complement representation.

int64_t is optional, but must exist if the platform provides a type with exactly 64 bits, (no padding bits) and a 2’s complement representation, which then must be typedef’d to int64_t.

On common 64-bit platforms (LP64, ILP64), long will be int64_t; that is, it will be exactly 64bits large and have limits -2^64 and +2^64–1.
    */
    const int MOD = 1e9 + 7;
    
    vector<vector<int>>matrixMult(const vector<vector<int>>&A, const vector<vector<int>>&B){
        vector<vector<int>>result(A.size(), vector<int>(B[0].size()));
        for(int i = 0; i<A.size(); ++i){
            for(int j = 0; j <B[0].size(); ++j){
                int64_t entry = 0; // long = int64_t;
                for(int k = 0; k < B.size(); ++k){
                    entry = (entry + static_cast<int64_t>(A[i][k])*B[k][j] % MOD )% MOD;
                }
                result[i][j] = static_cast<int>(entry);
            }
        }
        return result;
    }
    
    vector<vector<int>>matrixExpo(const vector<vector<int>>&A, int pow){
        vector<vector<int>>result(A.size(), vector<int>(A.size()));
        vector<vector<int>>A_exp(A);
        for(int i = 0; i<A.size(); ++i)
            result[i][i] = 1;
        while(pow){
            if(pow % 2 == 1)
                result = matrixMult(result, A_exp);
            A_exp = matrixMult(A_exp, A_exp);
            pow /= 2;
        }
        return result;
    }
    
    
    
    
    int numOfWays(int n) {
        static const vector<vector<int>> T = {{3, 2},
                                              {2, 2}};
        const auto result = matrixMult({{6, 6}}, matrixExpo(T, n - 1))[0];  // [a1, a0] * T^(n-1)
        return (result[0] + result[1]) % MOD;
    }
};




//Recurssion
class Solution {
public:

    const int MOD = 1e9 + 7;
    
    vector<vector<int>>matrixMult(const vector<vector<int>>&A, const vector<vector<int>>&B){
        vector<vector<int>>result(A.size(), vector<int>(B[0].size()));
        for(int i = 0; i<A.size(); ++i){
            for(int j = 0; j <B[0].size(); ++j){
                int64_t entry = 0; // long = int64_t;
                for(int k = 0; k < B.size(); ++k){
                    entry = (entry + static_cast<int64_t>(A[i][k])*B[k][j] % MOD )% MOD;
                }
                result[i][j] = static_cast<int>(entry);
            }
        }
        return result;
    }
    
    vector<vector<int>>matrixPower(const vector<vector<int>>&A, int pow){
        //pow need to > 1
        
        if(pow == 1) return A;
        vector<vector<int>>A_exp(A);
        A_exp = matrixMult(A, A);
        A_exp = matrixPower(A_exp, pow/2);
        if(pow % 2)
            A_exp = matrixMult(A_exp, A);
        
        return A_exp;
    }
    
    
    
    
    int numOfWays(int n) {
        if(n == 1) return 12;
        const vector<vector<int>> T = {{3, 2},
                                              {2, 2}};
        const auto result = matrixMult({{6, 6}}, matrixPower(T, n - 1))[0];  // [a1, a0] * T^(n-1)
        return (result[0] + result[1]) % MOD;
    }
};