class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int>maxLen(nums.size(),1);
        vector<int>cnt(nums.size(),1);
        int curmaxLen = 0, res = 0;
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<i; j++){
                if(nums[i]>nums[j] && maxLen[j]+1>maxLen[i]){
                    maxLen[i] =  maxLen[j]+1;
                    cnt[i] = cnt[j];
                }
                else if(nums[i]>nums[j] && maxLen[j]+1 == maxLen[i]){
                    cnt[i]+=cnt[j];
                }
            }
            if(curmaxLen < maxLen[i]){
                curmaxLen = maxLen[i];
                res = cnt[i];
            }else if(curmaxLen ==  maxLen[i])
                res += cnt[i];
        }
        return res;
    }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int>maxLen(nums.size(),1);
        vector<int>cnt(nums.size(),1);
        int curmaxLen = 0, res = 0;
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<i; j++){
                if(nums[i]>nums[j] && maxLen[j]+1>maxLen[i]){
                    maxLen[i] =  maxLen[j]+1;
                    cnt[i] = cnt[j];
                }
                else if(nums[i]>nums[j] && maxLen[j]+1 == maxLen[i]){
                    cnt[i]+=cnt[j];
                }
            }
            curmaxLen = max(curmaxLen,maxLen[i]);
        }
        for(int i = 0; i<nums.size();i++){
            if(maxLen[i] == curmaxLen)
                res+=cnt[i];
        }
        return res;
    }
};


/*
O(nlogn)

 [1,4,2,5,3]

num = 1, dyn 空, add dyn[1] = [{seq: [1], count: 1}]. The index 1 in dyn[1] means LIS length

num = 4, s > 1 from dyn[1], 所以length = 2
    copy its count 1(dyn[1]). Now we have, dyn[2] = [{seq: [*, 4], count: 1}]

num = 2,  2 < 4 from dyn[2], but 2 > 1 from dyn[1], belongs to length 2
    add one more item to dyn[2] where the index 2 means LIS length: 
     dyn[2] = [{seq: [*, 4], count: 1}, {seq: [*, 2], count: 1}]

num =5, check previous dyn, 5 > 2 frm dyn2[] annd 5 > 1 from dyn[1], length 3
    But calculating its count is harder now: we need to get counts from dyn[2] and sum them somehow.
    5 > [ *, 4], we add count 1.
    5 > [ *, 2], we add another count 1.
    So this count is 2.
    Now we have dyn[3] = [{seq: [*, *, 5], count: 2}]. Here [*,*,5] count 2 means [1,4,5], [1,2,5].


num = 3, 3 < 5 from dyn[3] but 3 > 2 from dyn[2], this belongs to length 3

    And another difficult calculation: we still need to get counts from dyn[2], but we can't take all of them.
    3 < [ *, 4], we skip it
    3 > [ *, 2], we add count 1.
    So this count is 1.
    Now we have dyn[3] = [{seq: [*, *, 5], count: 2}, {seq: [*, *, 3], count: 1}]

What was optimized in this solution is that count was replaced by accumulated count.
So instead of [{seq: [*, *, 5], count: 2}, {seq: [*, *, 3], count: 1}] we use [{seq: [*, *, 5], acc_count: 2}, {seq: [*, *, 3], acc_count: 3}] and in the answer just return the last acc_count 3.

 */


class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.empty())
            return 0;
        
        vector<vector<pair<int, int>>> dyn(nums.size() + 1);
        int max_so_far = 0;
        for (int i = 0; i < nums.size(); ++i) {
            // bsearch insertion point
            int l = 0, r = max_so_far;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (dyn[mid].back().first < nums[i]) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            
            // bsearch number of options
            int options = 1;
            int row = l - 1;
            if (row >= 0) {
                int l1 = 0, r1 = dyn[row].size();
                while (l1 < r1) {
                    int mid = l1 + (r1 - l1) / 2;
                    if (dyn[row][mid].first < nums[i]) {
                        r1 = mid;
                    } else {
                        l1 = mid + 1;
                    }
                }
                
                options = dyn[row].back().second;
                options -= (l1 == 0) ? 0 : dyn[row][l1 - 1].second;
            }
            
            
            dyn[l].push_back({nums[i], (dyn[l].empty() ? options : dyn[l].back().second + options)});
            if (l == max_so_far) {
                max_so_far++;
            }
        }
        
        return dyn[max_so_far-1].back().second;
        
    }