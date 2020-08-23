/*
Hint:
当num <= miss 表示\[0,miss)已经满足, miss+=num; else, miss*=2, patch++ 


*/

/*
Miss the smallest number we missed in [0,n],代表着[0, miss) 所有的sum 我们已经建立, 
如果下一个数小于<=miss, 我们可以扩大sum的到 [0, num + miss), 如果现在的数大于miss，为了扩大区间，我们加miss，
可以扩大到num + miss, 因为[1, miss)之前已经覆盖了, 每个数都可以加上num，最大值就变成了num+miss

比如 nums[1,2,4,13,43], n = 100, 我们需要确认[1,100]每个数都可以被sum， 
1. miss = 1, num = 1, miss += 1 = 2, i++, 区间扩大到[1,2) 
2. miss = 2, num = 2, miss += 2  = 4, i++, 区间扩大到[1,4)
3. miss = 4, num = 4, miss += 4  = 8, i++, 区间扩大到[1,8）
4. miss = 8, num = 13, miss += miss = 16,  区间扩大到[1,16）
5. miss = 16, num = 13, miss += 13 = 29,  区间扩大到[1,29）
4. miss = 29, num = 43, miss += miss = 58,  区间扩大到[1,58)
4. miss = 58, num = 43, miss += 43 = 101,  区间扩大到[1,101)

*/


class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int patch = 0;
        for (uint64_t miss = 1, i = 0; miss <= n;) { //也可以用long
            if (i < nums.size()  && nums[i] <= miss) {
                miss += nums[i++];
            } else {
                miss += miss;  
                ++patch;
            }
        }
        return patch;
    }
};

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int count = 0, i = 0;
        for (long miss=1; miss <= n; count++)
            miss += (i < nums.size() && nums[i] <= miss) ? nums[i++] : miss;
        return count - i;
    }
};

/*
比如现在是[1,2,3,9], 
1,2,3 是可以实现的，可以到6，7是第一个到不了的，所以我们加上7, 6 + 7 = 13, 【1，13】都可以的
9 < 13, 每个[1,13]的数都可以加上9， 所以现在range是[1,22], 23是第一个到不了的，加上23, range变为[1,45]
*/
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        
        long long sum = 0; 
        //和上面解法区别是上面sum 起始是1，所以miss *= 2, 这起始0，sum是第一个到不了的点需要 sum += sum + 1
        //这的sum表示最后到达的点，上面的sum表示第一个到达不了的点
        int i=0, patch = 0;
        
        while(sum < n) {
            if(i>=(int)nums.size() || sum+1 < nums[i]) {
                patch += 1;
                sum = sum + (sum+1); //sum 是 2^n - 1, 1,3,7,15
            }
            else {
                sum = sum + nums[i];
                i++;
            }
        }
        
        return patch;
    }
};




class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long long prev = 0;
        int cnt = 0;
        for(int i : nums) {
            while(prev < i - 1 && prev < n) {
                prev = 2 * prev + 1;
                cnt++;
            }
            prev += i;
            if(prev >= n) break;
        }
        while(prev < n) {
            prev = 2 * prev + 1;
            cnt++;
        }
        return cnt;
    }
};


