/*

首先，multiset 当新插入的数与multiset 中的数相等时，插入在相等数的后面
比如 0,1,2 再插入1 
会变成 0,1,1,2
          ^
          | 第二1 是新插入的 1, 所以把等于条件想成大于

mid 是开始操作前，处于upper median 位置的指针

 0   1    2    3
     ^    ^
     |    |
 lower    |
        upper median
 

************ 

if (nums[i] < *mid){
    mid--;   
}

为了保证在这步之后，mid在lower median 位置 
比如  k 是奇数， 当前set 1,2,3 新插入0 
     1, 2 ,3 
        ^
        | mid 
插入后  
        0, 1, 2, 3 
            ^
            | mid 保证 在lower median 

比如  k 是欧数， 当前set 1,2,3,4 新插入0 
     1, 2 , 3, 4
            ^
            | mid 
插入后  
      0, 1, 2, 3, 4
            ^
            | mid 保证 在lower median 

如果 新插入的数 等于当前数，已经满足 lower median 条件
     1, 2 ,3 
        ^
        | mid 
    新插入2 
     1, 2 ,  2， 3 
        ^    ^ 
        |    |
        mid   第2个2 是新插入的数

************ 


if (nums[i-k] <= *mid)
    mid++;   

*** 注： 当 nums[i-k] == mid, remove (nums[i-k]) 会导致 invalidate mid pointer

目的让lower median 变成upper medium, 

让 lower median 变成 upper median 的移动条件是 nums[i-k] <= *mid

如果 nums[i-k] > *mid, mid 不变 
比如 
     1, 2 ,3, 5
        ^
        | mid 
    删除 5 
    1,  2 ,3 
        ^
        | mid
    
      0, 1, 2 ,3, 5
            ^
            | mid 
    删除 5 
     0, 1,  2 ,3 
            ^
            | mid


 */

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int>st (nums.begin(), nums.begin() + k);
        auto mid = next(st.begin(), k/2);
        vector<double>res;
        for(int i = k ; i < nums.size(); ++i){
            double median = ((double)(*mid) + *prev(mid, (k % 2) == 0)) / 2;
            res.push_back(median);

            st.insert(nums[i]);
            if (nums[i] < *mid) 
                --mid;
            if (nums[i-k] <= *mid)
                ++mid;
            st.erase(st.lower_bound(nums[i-k]));
        }
        double median = ((double)(*mid) + *prev(mid, (k % 2) == 0)) / 2;
        res.push_back(median);
        return res;
    }
};



//两个heap 
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int>lo, hi;
        vector<double> res;
        for(int i = 0; i < nums.size(); ++i){
            lo.insert(nums[i]);
            hi.insert(*lo.rbegin());
            lo.erase(prev(lo.end()));
            if(lo.size() < hi.size() - 1){
                lo.insert(*hi.begin());
                hi.erase(hi.begin());
            }
            if (i >= k -1){
                double median;
                if (k & 1) 
                    median = *hi.begin();
                else 
                    median = ((double)(*lo.rbegin()) + *hi.begin()) / 2;
                res.push_back(median);
                if (nums[i-k + 1] >= *hi.begin())
                    hi.erase(hi.find(nums[i-k+1])); 
                else{
                    lo.erase(lo.find(nums[i-k + 1]));
                }
            }
        }
        return res;
    }
};