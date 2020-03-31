/*
552. Student Attendance Record II

Given a positive integer n, return the number of all possible attendance records with length n, which will be regarded as rewardable. The answer may be very large, return it after mod 109 + 7.

A student attendance record is a string that only contains the following three characters:

'A' : Absent.
'L' : Late.
'P' : Present.
A record is regarded as rewardable if it doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

Example 1:
Input: n = 2
Output: 8 
Explanation:
There are 8 records with length 2 will be regarded as rewardable:
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" won't be regarded as rewardable owing to more than one absent times. 
Note: The value of n won't exceed 100,000.



*/

/*

P(n) = A(n-1) + P(n-1) + L(n-1)
L(n) = P(n-1) + P(n-2) + A(n-1) + A(n-2) （比如 PL, PLL, AL, ALL)
A(n) = noA_P(n-1) + noA_L(n-1)
noA_P(n) = noA_P(n-1) + noA_L(n-1) = A(n)   (比如 前面没有A, PP, LP)  
noA_L(n) = noA_P(n-1) + noA_P(n-2) = A(n-1) + A(n-2) (比如 前面没有A, PL, PLL)

P(n) = A(n-1) + P(n-1) + L(n-1)
L(n) = P(n-1) + P(n-2) + A(n-1) + A(n-2) （比如 PL, PLL, AL, ALL)
A(n) = A(n-1) + A(n-2) + A(n-3) 
A(n-1) + A(n-2) + A(n-3)  相当于把最后一位的A换成P

A(1) = 1    A
A(2) = 2    PA, LA
A(3) = 4    PPA, LPA, PLA, LLA
A(4) = 1+2+4 = 7   把A(3)最后一位变成P， PPPA, LPPA, PLPA, LLPA, 把A(2) 最后一位变成P再加一个L，PPLA, LPLA, 把A(1)最后一位变成p，加两个L，PLLA

*/


class Solution {
public:
    int checkRecord(int n) {
        int m = 1000000007;
        if(n==0) return 3;
        long long *P = new long long[n];
        long long *A = new long long[n];
        long long *L = new long long[n];
        P[0] = A[0] = L[0] = 1;
        P[1] = L[1] = 3; A[1] = 2;
        A[2] = 4;
        for(long long i = 2; i<n; i++){
            P[i] = (A[i-1] + L[i-1] + P[i-1])%m;
            L[i] = (A[i-2] +P[i-2] + A[i-1] + P[i-1])%m;
            if(i>2)
                A[i] = (A[i-1] + A[i-2] + A[i-3])%m;
        }
        return (A[n-1] + P[n-1] + L[n-1])%m;
    }
};

class Solution {
public:
    int checkRecord(int n) {
        static long long m = 1000000007;
        if(n==1) return 3;
        if(n==2) return 8;
        vector<long long>P(3,0);vector<long long>A(3,0);vector<long long>L(3,0);
        P[0] = 1, P[1] = 3, P[2] = 8,  A[0] = 1, A[1] = 2, A[2] = 4, L[0] = 1, L[1] = 3, L[2] = 7;
        for(int i = 3; i<=n; i++){
            P[i%3] = (P[(i-1)%3] + A[(i-1)%3] + L[(i-1)%3]) % m;
            A[i%3] += (A[(i-1)%3] + A[(i-2)%3])%m;
            L[i%3] =(P[(i-1)%3] + P[(i-2)%3] + A[(i-1)%3] + A[(i-2)%3]) % m;
        }
        return P[n%3];
    }
};


class Solution {
public:
    int checkRecord(int n) {
        static const long long M = 1000000007;
        long long a0l0 = 1, a0l1 = 0, a0l2 = 0, a1l0 = 0, a1l1 = 0, a1l2 = 0;
        for (int i = 0; i <= n; ++i) {
            auto new_a0l0 = (a0l0 + a0l1 + a0l2) % M;
            a0l2 = a0l1;
            a0l1 = a0l0;
            a0l0 = new_a0l0;
            auto new_a1l0 = (a0l0 + a1l0 + a1l1 + a1l2) % M;
            a1l2 = a1l1;
            a1l1 = a1l0;
            a1l0 = new_a1l0;
            //cout<<i<<" a0l0 "<<a0l0<<" a0l1 "<<a0l1<<" a0l2 "<<a0l2<<" a1l0 "<<a1l0<<" a1l1 "<<a1l1<<" a1l2 "<<a1l2<<endl;
        }
        return static_cast<int>(a1l0);
    }
};