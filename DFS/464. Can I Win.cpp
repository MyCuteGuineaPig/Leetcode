/*
464. Can I Win

In the "100 game," two players take turns adding, to a running total, any integer from 1..10. The player who first causes the running total to reach or exceed 100 wins.

What if we change the game so that players cannot re-use integers?

For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.

Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally.

You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.

Example

Input:
maxChoosableInteger = 10
desiredTotal = 11

Output:
false

Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.


*/

class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= 0) return true;
        if(maxChoosableInteger * (1+maxChoosableInteger)/2 < desiredTotal) return false;
        unordered_map<int,bool>mp;
        return helper(maxChoosableInteger,desiredTotal, 0, mp);
    }
    
private:
    bool helper(int mci, int dt, int cur, unordered_map<int, bool> &mp){
        if(mp.count(cur)) return mp[cur];

        for(int i = 0; i<mci; i++){
            if((cur & (1<<i)) == 0 && (dt<= i+1 || !helper(mci, dt-i-1, cur|(1<<i),mp))) ){
                return mp[cur] = true;
            }
        }
        return mp[cur] = false;
    }
};

//self
class Solution {
public:
    unordered_map<int,bool>mpA;
    unordered_map<int,bool>mpB;
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= 0) return true;
        if((maxChoosableInteger + 1)*maxChoosableInteger/2 < desiredTotal)
            return false;
        long long number = pow(2, maxChoosableInteger)-1;
        return helper(number, maxChoosableInteger,desiredTotal, 'A');
    }
    
    bool helper(long long & number, int maxChoosableInteger, int desiredTotal, char cur){
        if(cur == 'A' && mpA.find(number) != mpA.end())
            return mpA[number];
        if(cur == 'B' && mpB.find(number) != mpB.end())
            return mpB[number];
        if( desiredTotal <= maxChoosableInteger && (number >> (desiredTotal-1)) >= 1){//可以选的大于 desiredTotal,
            assign(number, true, cur);
            return true;
        }
        for(int i = 0; i<maxChoosableInteger; ++i){
            if((number & (1<<i)) && i+1 < desiredTotal){
                number = number ^ (1<<i);
                if(!helper(number, maxChoosableInteger, desiredTotal - i-1, cur == 'A' ? 'B': 'A')){              
                    number |= (1<<i); //一定把现在选择的放回去, 要不然影响前面的选择, 比如 A 选择了2 , 如果不reset bit, 前面 B 不能选择2了
                    assign(number, true, cur);
                    return true;
                }
                number |= (1<<i);
            }
        }
       assign(number, false, cur);
       return false;
    }
    
    void assign(const long long & number, bool val, const char& cur){
        if(cur == 'A')
            mpA[number] = val;
        else if(cur == 'B')
            mpB[number] = val;        
    }
};
