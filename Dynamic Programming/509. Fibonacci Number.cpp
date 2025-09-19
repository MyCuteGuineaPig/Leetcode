class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        int a0 = 0;
        int a1 = 1;
        for(int i = 2; i<=n; ++i){
            a0 = (a1 += a0) - a0;
        }
        return a1;
    }
};