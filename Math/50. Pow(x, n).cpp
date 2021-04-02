class Solution {
public:
    double myPow(double x, int n) {
        long  N = n;
        if(N < 0){
            x = 1/x;
            N = -N;
        }
        return fastPow(x, N);
    }
    
    double fastPow(double x, long n){
        if(n == 0)
            return 1;
        double half = fastPow(x, n/2);
        if(n % 2 == 0)
            return half*half;
        else
            return half*half*x;
    }
};


/*
比如 x = 10, n = 10

cur = 10

cur = 10^2, ans = 1,      i = 10
cur = 10^4, ans = 10^2,   i =5
cur = 10^8, ans = 10^2,   i = 2
cur = 10^16,ans = 10^10,  i = 1



比如 x = 10, n = 15

cur = 10                                        

cur = 10^2,   ans = 10,      i = 15  15 -> 7 少算了一份, 加10
cur = 10^4,   ans = 10^3,    i = 7   7->3, 少算了一份, 加10^2
cur = 10^8,   ans = 10^7,    i = 3   3 -> 1. 少算了一份，加10^4
cur = 10^16,  ans = 10^15,   i = 1   


*/

class Solution {
public:
    double myPow(double x, int n) {
        long  N = n;
        if(N < 0){
            x = 1/x;
            N = -N;
        }
        double ans = 1;
        double cur = x;
        for(long  i = N; i; i/=2){
            if(i % 2 == 1)
                ans = ans* cur;
            cur = cur*cur;
        }
        
        return ans;
    }
};