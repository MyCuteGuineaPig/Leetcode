/*
396. Rotate Function

Given an array of integers A and let n to be its length.

Assume Bk to be an array obtained by rotating the array A k positions clock-wise, we define a "rotation function" F on A as follow:

F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].

Calculate the maximum value of F(0), F(1), ..., F(n-1).

Note:
n is guaranteed to be less than 105.

Example:

A = [4, 3, 2, 6]

F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26

So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.

*/


/*

F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1]
F(k-1) = 0 * Bk-1[0] + 1 * Bk-1[1] + ... + (n-1) * Bk-1[n-1]
       = 0 * Bk[1] + 1 * Bk[2] + ... + (n-2) * Bk[n-1] + (n-1) * Bk[0]
Then,

F(k) - F(k-1) = Bk[1] + Bk[2] + ... + Bk[n-1] + (1-n)Bk[0]
              = (Bk[0] + ... + Bk[n-1]) - nBk[0]
              = sum - nBk[0]
Thus,

F(k) = F(k-1) + sum - nBk[0]
What is Bk[0]?

k = 0; B[0] = A[0];
k = 1; B[0] = A[len-1];
k = 2; B[0] = A[len-2];
...


比如：  
A = [4, 3, 2, 6]

F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
            \         \          \
              \         \          \ 
                \          \          \
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
           \         \          \
              \         \          \ 
                \          \          \
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26

So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.

sum(A) = 7 + 8 = 15
我们知道F[0] = 25, 
F[1] = 25 + 15 - 4*6 = 40 - 24 = 16

F[2] = 16 + 15 - 4*2  = 31 - 8  = 23

F[3] = 23 + 15 - 4*3 = 38 - 12 = 26


*/




/*
F(0) = 0 * Bk[0] + 1 * Bk[1] + ... + (n - 1) * Bk[n - 1]
and the case when k > 0 and k < n

F(k) = 0 * Bk[n - k] + 1 * Bk[n - k + 1] + ... + (n - 1) * Bk[n - (k + 1)]
For those who got confused why we will start from i = len - 1:

F(1) = F(0) + sum - n * A[n - 1], here n = len so that A[n - 1] == A[i]
F(2) = F(1) + sum - n * A[n - 2]
...
F(k) = F(k - 1) + sum - n * A[n - k]
  */


 class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int sum = accumulate(A.begin(),A.end(),0);
        int f = 0;
        for(int i = 0; i<A.size(); i++)
            f += A[i]*i;
        
        int res = f, n = A.size();
        for(int i = n -1; i>0; i--)
        {
            f += sum - n*A[i];
            res = max(res, f);
        }
        return res;
    }
};




class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int sum = accumulate(A.begin(), A.end(), 0);
        int fi = 0;
        for (int i = 0; i < A.size(); ++i) {
            fi += i * A[i];
        }

        int result = fi;
        for (int i = 1; i <= A.size(); ++i) {
            fi += sum - A.size() * A[A.size() - i];
            result = max(result, fi);
        }
        return result;
    }
};


//逆序的 从B[0]->B[n-1]->B[n-2]
class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int n = A.size();
        int sum = 0;
        int candidate = 0;

        for (int i = 0; i < n; i++) {
            sum += A[i];
            candidate += A[i] * i;
        }
        int best = candidate;

        for (int i = 1; i < n; i++) {
            candidate = candidate - sum + A[i - 1] * n;
            best = max(best, candidate);
        }
        return best;
    }
};