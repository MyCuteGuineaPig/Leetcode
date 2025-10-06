/*

P(n), 在第n位是P的个数
L(n), 在第n位是L的个数
A(n), 在第n位是A的个数

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
A(4) = 1+2+4 = 7   把A(3)最后一位变成P， PPPA, LPPA, PLPA, LLPA, 
                   把A(2) 最后一位变成P再加一个L，PPLA, LPLA, 
                   把A(1)最后一位变成p，加两个L，PLLA

*/


class Solution {
public:
    int checkRecord(int n) {
        int m = 1000000007;
        if(n==1) return 3;
        if(n==2) return 8;
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
        }
        return static_cast<int>(a1l0);
    }
};

//2020
class Solution {
public:
    int checkRecord(int n) {
        long long p = 1, a = 1, l = 1, ll = 0, al = 0, all = 0, ap = 0;
        long long mod = pow(10,9)+7;
        for(int i = 1; i<n; i++){
            long long nxt_p = (p + l + ll) % mod; 
            long long nxt_a = (p + l + ll)  % mod; 
            long long nxt_l = p; 
            long long nxt_ll = l;
            
            long long nxt_al = ( a + ap) % mod;
            long long nxt_all = al;
            long long nxt_ap =( a + al + all + ap ) % mod;
            
            p = nxt_p;
            a = nxt_a;
            l = nxt_l;
            ll = nxt_ll;
            al = nxt_al;
            all = nxt_all;
            ap = nxt_ap;
        }
        return (p+a+l+ll+al+all+ap)%mod;
    }
};