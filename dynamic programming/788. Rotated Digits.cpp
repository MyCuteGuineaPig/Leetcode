/*
788. Rotated Digits
X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X. 
 Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other;
 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation: 
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Note:

N  will be in range [1, 10000].

*/


/*

Using a int[] for dp.
dp[i] = 0, invalid number
dp[i] = 1, valid and same number
dp[i] = 2, valid and different number
*/

class Solution {
public:
    int rotatedDigits(int N) {
        int dp[N+1] = {0};
        int count = 0;
        for(int i = 0; i<=N;i++){
            if(i<=10){
                if(i==0|| i == 1 || i ==8 || i == 10) dp[i] = 1;
                else if (i == 2 || i == 5 || i == 6 || i == 9) dp[i] = 2, count ++;
            }else{
                int a = dp[i%10], b = dp[i/10];
                if(a==1 && b == 1) dp[i] = 1;
                else if(a >=1  && b>=1)
                    dp[i] = 2, count++;
            }
        }
        return count;
    }
};



/*
O(logn), 
算的是所有比当前digit减1是good number的所有的数，下一位时候就包括这个数
比如24
i = 1, 算的是0-19是good number的，算所有valid的，减去自己rotate还是自己的
2*7(所有valid) - 2*3(自己rotate还是自己的， 0, 1, 8, 10,11,18) = 11 
i=1 算个位所有是good number的
5 - 2 = 3



*/
class Solution {
public:                   //0 1 2 3 4 5 6 7 8 9
    int validCount[10] =   {1,2,3,3,3,4,5,5,6,7}; //0, 1, 2, 5, 6, 8, 9
    int excludeCount[10] = {1,2,2,2,2,2,2,2,3,3}; //0, 1, 8
    bool breakDigit[10] =  {0,0,0,1,1,0,0,1,0,0};
    bool excludeDigit[10]= {1,1,0,0,0,0,0,0,1,0};
    
    int rotatedDigits(int N) {
        string s = to_string(N);
        int len = s.size(), base7 = pow(7,len-1), base3 = pow(3,len-1);
        int exclude = true, res = 0;
        for(int i = 0; i<len; i++, base7/=7, base3 /= 3){
            int index = s[i] - '0';
            if(index == 0 && i!=len-1) continue;
            if(i<len-1) index--;
            int v = validCount[index]*base7;
            int e = exclude ?excludeCount[index]*base3:  0 ;
            //cout<<index<<"  v  "<<v<<"  e "<<e<<endl;
            res += v-e;
            if(breakDigit[s[i] - '0']) break; //比如249, i=0 算0-199 满足的， i=1 算200-239满足的，因为4不是good number, 剔除, break, 所有240 到249不可能是good number
            exclude = exclude & excludeDigit[s[i] - '0'];
            //比如329, i=0 算0-299 满足的， i=1 算300-319满足的，2是valid的不是self rotated，所以算320-329 不用考虑是不是valid的
            //3299, 也是这个道理
        }
        return res;
    }
};