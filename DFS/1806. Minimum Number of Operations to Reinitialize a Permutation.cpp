/*

E.g. n = 10

init        0  1  2  3  4  5  6  7  8  9 
First Swap  0  5  1  6  2  7  3  8  4  9

*/


class Solution {
public:
    int reinitializePermutation(int n) {
        int res = 0, i = 1;
        while (res == 0 || i > 1) {
            if (i < n / 2)
                i *= 2;
            else
                i = (i - n / 2) * 2 + 1;
            res++;
        }
        return res;
    }
};