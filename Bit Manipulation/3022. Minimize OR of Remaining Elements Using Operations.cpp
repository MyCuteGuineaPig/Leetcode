/*
每次看 j + 1位 bit 能不能被消除
比如现在j = 1, 检查 第3 位bit 1的1 能不能被消掉

第三位能被消掉condition是  第三位的 1 的个数 小于等于k, 
如果1不能被消除，在结果中要保留1。 


比如 nums = [3,5,3,2,7], k = 2
binary  3   011
        5   101
        3   011
        2   010
        7   111 

j = 2, 检查最左侧可不可位为1， cur = 111, target = 011

cur & x  表示直到有x的 j+1 bit 为0， 那么 cur & x | targe == target

如果 (cur | target) == target 表示第三位bit 不为1, 因为cur 起始值是111, target 起始值是1， 
如果(cur | target) == target  =》 新的数 第三位是0  让 cur 111 -> 0xx
检测只有两个数（5和7） 不满足condition， 两个数 2 <= k (2), 所以第三位可以不是1 

j = 1, 检查中间位bit 可不可为1， cur = 111, target = 001, 查出了3,3,2,7 中间bit 都是1， 而4个数 > k， 所以第二位必须是1
j = 0, cur = 1, target = 10 (由j = 2 update,)



比如 nums = [6,4,2,5,1], k = 2
binary  6   1 1 0
        4   1 0 0
        2   0 1 0
        5   1 0 1
        1   0 0 1

target 的作用保持前面数该有的bit， 

当 j = 1, cur = 111, target = 101
    x=6    cur = 110 (111 & 110)  cur | target  = 111 (010 | 101) != 101 
    x=4    cur = 100 (110 & 100)   cur | target = 101  ( 0 | 101 ) == 101  (第二位是0)
           cur = 111, target = 101  cnt++
    x=2    cur = 010 (111 & 010) cur | target = 111 ( 010 | 101) != 101 
    x=5    cur = 0   (010 & 101) cur | target = 101 == 101 (第二位是0)
           cur = 111, target = 101  cnt++
    x=1    cur = 1   (111 & 001) cur | target = 101 == 101 (第二位是0)
            cnt++

当 j = 0, cur = 111, target = 100， 要第二位，第三位 连续merge 是 0
    x=6    cur = 010 (111 & 110)  cur | target  = 110 (010 | 100) != 100 （中间位不是0!!!!!!）
    x=4    cur = 0 (010 & 100)   cur | target = 100  ( 0 | 100 ) == 100  (第二位是0, 第一位是0)
           cur = 111, target = 100  cnt++
    x=2    cur = 010 (111 & 010) cur | target = 110 ( 010 | 100) != 100 （中间位不是0!!!!!!）
    x=5    cur = 0   (010 & 101) cur | target = 101 == 100 (第一位不是0)
           cur = 111, target = 100  cnt++
    x=1    cur = 1   (111 & 001) cur | target = 101 != 100 (第一位不是0)



*/


class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int  n= nums.size(); 
        int ans = 0;
        int cur = 0;
        for (int i = 30; i>=0; --i){
            cur = ((1<<30)-1);
            int target = ans | ((1<<i)-1);
            int cnt = 0;
            for(auto x: nums){
                cur = cur & x;
                if ((cur | target) == target){
                    ++cnt;
                    cur = ((1<<30)-1);
                }
            }
            if ( n - cnt > k){
                ans |= (1<<i);
            }
        }
        return ans; 
    }
};

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int  n= nums.size(); 
        int ans = 0;
        int cur = 0;
        for (int i = 29; i>=0; --i){
            cur = -1; //111111 in binary representation
            int target = ans | ((1<<i)-1);
            int cnt = 0;
            for(auto x: nums){
                cur = cur & x;
                if ((cur | target) == target){
                    ++cnt;
                    cur = -1;
                }
            }
            if ( n - cnt > k){
                ans |= (1<<i);
            }
        }
        return ans; 
    }
};

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int  n= nums.size(); 
        int ans = 0;
        int cur = 0;
        for (int i = 30; i>=0; --i){
            cur = cur | (1<<i) ; //111111 in binary representation
            int cnt = 0;
            int temp = cur;
            for(auto x: nums){
                temp = temp & x;
                if ((temp | ans) == ans){
                    ++cnt;
                    temp = cur;
                }
            }
            if ( n - cnt > k){
                ans |= (1<<i);
            }
        }
        return ans; 
    }
};