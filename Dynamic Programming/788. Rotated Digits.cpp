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


//O(NlogN)
class Solution {
public:
    int rotatedDigits(int N) {
        int f[] = {1,1,2,0,0,2,2,0,1,2};
        int res = 0;
        for(int i = 1; i <= N; i++){
            int p = i;
            int s = 1;
            while(p){
                s *= f[p%10];
                p /= 10;
            }
            if(s >=2) res+=1;
        }
        return res;
    }
};



class Solution {
public:
    int rotatedDigits(int N) {
        int count = 0;
        for (int i = 1; i <= N; i ++) {
            if (isValid(i)) count ++;
            i += incrementIfNeeded(i);
        }
        return count;
    }
    
    int incrementIfNeeded(int i) { //比如number 是 30, 因为3不是significant, 4也不是, 
                                // 30 + (2*10-1) = 49, 跳到79
                                //比如现在是170,  因为7不是 跳到179
        int inc = 1;
        while (i >= 10) {
            int modCheck = i % 10;
            if (modCheck == 3) return (2*inc) - 1;
            if (modCheck == 7) return inc - 1;
            inc *= 10;
            i /= 10;
        }
        if (i == 3) return (2*inc) - 1;
        else if (i == 7) return inc - 1;
        else return 0;
    }
    
    bool isValid(int N) {
        /*
         Valid if N contains ATLEAST ONE 2, 5, 6, 9
         AND NO 3, 4 or 7s
         */
        bool validFound = false;
        while (N > 0) {
            if (N % 10 == 2) validFound = true;
            if (N % 10 == 5) validFound = true;
            if (N % 10 == 6) validFound = true;
            if (N % 10 == 9) validFound = true;
            if (N % 10 == 3) return false;
            if (N % 10 == 4) return false;
            if (N % 10 == 7) return false;
            N = N / 10;
        }
        return validFound;
    }
};

/*

O(Logn): math 


+= 7 ** means you could pick digits from this set [0, 1, 8, 2, 5, 6, 9], 

7**len, permutation: 比如有两位数， [0, 1, 8, 2, 5, 6, 9] 可以组合成49个
3**len, permutation, 比如有两位数， [0,1,8] 9 个rotate 后自己, rotate是自己: 0(00), 1(01), 8(08), 10, 11, 18, 80,81,88

 */


class Solution {
public:
    int rotatedDigits(int N) {
        //                    0  1  2  3   4   5  6  7   8  9
        vector<int> rotate = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
        vector<int> ds;
        while (N > 0) {
            ds.push_back(N % 10);
            N /= 10;
        }
        
        int count = 0;
        bool diff = false;
        for (int i = ds.size() - 1; i >= 0; --i) {
            int good = 0, soso = 0, d = ds[i];
            for (int j = 0; j < d; ++j) {
                if (rotate[j] == 1) ++good;
                else if (rotate[j] == 0) ++soso;
            }
            count += (good + soso) * pow(7, i);
            if (!diff) count -= soso * pow(3, i);
            if (rotate[d] == -1) return count;
            if (rotate[d] == 1) diff = true;
        }
        return diff ? count + 1 : count; //count+1, 是算上N, 比如188 不加1, 155 加1
    }
};





/*
O(logn), 
算的是所有比当前digit减1是good number的所有的数，下一位时候就包括这个数
比如24
i = 0, 算的是0-19是good number的，算所有valid的，减去自己rotate还是自己的
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
        int exclude = true, res = 0; //exclude 取决于前一位，比如260, 在 i = 1, 时候因为i = 0, rotate 不是自己， 可以exclude = false
        for(int i = 0; i<len; i++, base7/=7, base3 /= 3){
            int index = s[i] - '0';
            if(index == 0 && i!=len-1) continue;
            if(i<len-1) index--;
            int v = validCount[index]*base7;
            int e = exclude ?excludeCount[index]*base3:  0 ;
            
            res += v-e;
            if(breakDigit[s[i] - '0']) break; //比如249, i=0 算0-199 满足的， i=1 算200-239满足的，因为4不是good number, 剔除, break, 所有240 到249不可能是good number
            exclude = exclude & excludeDigit[s[i] - '0'];
            //比如329, i=0 算0-299 满足的， i=1 算300-319满足的，2是valid的不是self rotated，所以算320-329 不用考虑是不是valid的
            //3299, 也是这个道理
        }
        return res;
    }
};