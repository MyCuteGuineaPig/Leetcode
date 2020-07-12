
/*

0 00000
1 00001
2 00010
3 00011 X
4 00100
5 00101
6 00110 X
7 00111 X
8 01000
9 01001
10 01010
11 01100 X
12 01100 X
13 01101 X
14 01110 X
15 01111 X

规律:
Bit 总共一位: 2 
    总共两位: 3
    总共三位: 5 
    总共四位: 8

如果最高位和最高位下一位都是1, 返回FB[n] (n = 5, FB[n] 包含了 11xxx 的情况的所有解, 且10xxx < 11xxx)
比如 12: 1100, 返回 FB[3] 

如果最高位是1， 最高位下一位不是1,  返回 FB[n-1] +  findIntegers(num& ~(1<<n));
FB[n-1] 组成的数, 如果n-1不是1，则带上n位的1，如果n-1位是1，则不带上n位的1， 比如100, 不能是1100, 再比如 1, 带上n位的1可以组成1001
比如 10: 1010, 返回 FB[2] = 5 表示的是: 1000, 1001, 1010, 100, 101, 再找 findIntegers(10)

*/

class Solution {
public:
    int findIntegers(int num) {
            static int fb[31] = { 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946,
        17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578 };
        if(num<3)
            return num+1;
        if(num == 3)
            return 3;
        for(int i = 29; i>=0; i--)
            if(num & (1<<i)){
                return num & (1<<(i-1)) ? fb[i] : fb[i-1] +  findIntegers(num& ~(1<<i));
            }
    }
};


class Solution {
public:
    int findIntegers(int num) {
        int calc[32] = {1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765
        ,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309};
        int sum = 0;
        bool is_last_one = false;
        for (int i = 31; i >= 0; i --)
            if (( num & 1 << i) > 0)
            {
                sum += calc[i];
                if ((num & 1 << i+1) > 0)
                    return sum;
            }
        return sum + 1;
    }
};


//Iterative: 
//先算共同可能性的，再减去不符合条件的
/*

比如 num = 25  11001
Bit : 1 0 0 1 1 
dp:   1 1 2 3 5 8
res = dp [5] + dp[4] = 13 
遇到 bit[3] == bit[4] == 1 : break


 */
class Solution {
public:
    int findIntegers(int num) {
        vector<int> bits;
        for (; num > 0; num >>= 1)
            bits.push_back(num & 1);
        int n = bits.size();
        
        vector<int> dp(n+1, 0);
        dp[0] = 1; dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        
        int res = dp[n] + dp[n - 1];
        for (int i = n - 2; i >= 0; i--)
            if (bits[i] == 0 && bits[i + 1] == 0)
                res -= dp[i];
            else if (bits[i] == 1 && bits[i + 1] == 1)
                break;
        return res;
    }
};

class Solution {
public:
    int findIntegers(int num) {
        static int fb[32] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946,
        17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578 };
        int res = 0, prev_bit = 0, k = 30;
        while(k>=0){
            if(num & (1<<k)){
                res += fb[k];
                if(prev_bit)
                    return res;
                prev_bit = 1;
            }
            else 
                prev_bit = 0;
            k--;
        }
        return res+1; //加的1: the number n itself. 比如4 return 4, 1000, = 3 + 1, 
        //比如 20 (10100) = 8(4位的bit) + 3 (两位的bit) + 1 ( 10100)
    }
};


/**
0 00000
1 00001
2 00010
3 00011 X
4 00100
5 00101
6 00110 X
7 00111 X
8 01000
9 01001
10 01010
11 01100 X
12 01100 X
13 01101 X
14 01110 X
15 01111 X
16 10000
17 10001
18 10010
19 10011 X
20 10100
21 10101
22 10110 X
23 10111 X
24 11000 X
25 11001 X
26 11010 X
27 11011 X
28 11100 X
29 11101 X
30 11110 X
31 11111 X

one[i]:  be the number of non-consecutive-1 solutions with the i-th significant bit being 1; 
one[4]: 表示1xxxx 含有的解 (第五位必须是1)
zero[i]:  be the number of non-consecutive-1 solutions with the i-th significant bit being 0;
one[4]: 表示0xxxx 含有的解

比如 num = 25  11001
Bit : 1 0 0 1 1 
one:   1 1 2 3 5
zero:    1 2 3 5 8
res = zero[4] + one[4] = 13

比如 num = 18,  10010
zeros:  1 1 2 3 5 
ones:   1 2 3 5 8 

res = 5 + 8 = 13  - 2 (0xx) 多算了,   
其中5 是 10000, 10001, 10010, 100, 101
其中8 是 0, 1, 10, 100, 101, 1000, 1001, 1010 
100, 101 被重复算了

 */



class Solution {
public:
    int findIntegers(int num) {
        vector<int> bits;
        for (; num > 0; num >>= 1)
            bits.push_back(num & 1);
        int n = bits.size();
        
        vector<int> one(n, 0), zero(n, 0);
        one[0] = zero[0] = 1;
        for (int i = 1; i < n; i++) {
            one[i] = zero[i - 1];
            zero[i] = zero[i - 1] + one[i - 1];
        }
        
        int res = zero[n - 1] + one[n - 1];
        for (int i = n - 2; i >= 0; i--)
            if (bits[i] == 0 && bits[i + 1] == 0)
                res -= one[i];
            else if (bits[i] == 1 && bits[i + 1] == 1)
                break;
        return res;
    }
};