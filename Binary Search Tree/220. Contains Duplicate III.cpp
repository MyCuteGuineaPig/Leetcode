/*

220. Contains Duplicate III

Given an array of integers, find out whether there are two distinct indices i and j in the array such that 
the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.

*/

/*
O(nlogn) 因为set的lowerbound 是log（n) binary search
*/
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<long>s;
        for(int i = 0; i<nums.size();i++){
            if(i>k) s.erase(nums[i-k-1]);
            auto p = s.lower_bound(static_cast<long>(nums[i])-t);
            if (p!=s.end() && *p - nums[i]<=t){ 
                // lower_bound保证 nums[i] - *p <=t, 还要保证 *p - num <=t, 因为比如num[i] = 4, *p = 10, t = 3
                // p!=s.end() true 但是它们difference 不小于3
                return true;
            }
            s.insert(nums[i]);
        }
        return false;
    }
};


/*
O(n^2)的解
*/
class Solution {
public:
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
         if(nums.size() < 2) return false;
         vector<pair<long, int>> value;
         for (int i = 0; i < nums.size(); ++i)
            value.push_back(pair<long, int>(nums[i], i));
         sort(value.begin(), value.end());
         for (int i = nums.size() - 1; i >= 1; --i)
         {
             for (int j = i - 1; j >= 0; --j)
             {
                 if (value[i].first - value[j].first > t) break;
                 else if (abs(value[i].second - value[j].second) <= k) return true;
                 else continue;
             }
         }
         return false;
    }
};


class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k < 0 || t < 0) {
            return false;
        }
        
        queue<int64_t> window;
        multiset<int64_t> bst;
        for (int i = 0; i < nums.size(); ++i) {
            // Only keep at most k elements.
            if (bst.size() > k) {
                int num = window.front();
                window.pop();
                bst.erase(bst.find(num));
            }
            // Every search costs time: O(logk).
            const auto it = bst.lower_bound(nums[i] - t);
            if (it == bst.cend() || (*it - nums[i]) > t) {
                // Not found.
                window.emplace(nums[i]);
                bst.emplace(nums[i]);
            } else {
                return true;
            }
        }
        return false;
    }
};



/*
O(n) 解，但是不快
*/
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(nums.empty() || k < 1 || t < 0) return false;
        unordered_map<long,long> bucket_mapper;
        long min_val = * std::min_element(nums.begin(),nums.end());
        long bucket_size = t+1; // t could be 0
        for(int i=0;i<nums.size();++i){
            long bucket_id = (nums[i] - min_val) / bucket_size;
            if(bucket_mapper.size() > k) {
                long old_id = (nums[i-k-1] - min_val)/ bucket_size ;
                bucket_mapper.erase( old_id );
            }
            if ( bucket_mapper.find(bucket_id) != bucket_mapper.end()
                || bucket_mapper.find(bucket_id+1) != bucket_mapper.end() 
                    && std::abs(bucket_mapper[bucket_id+1] - nums[i]) <=t 
                || bucket_mapper.find(bucket_id-1) != bucket_mapper.end() 
                    && std::abs(bucket_mapper[bucket_id-1] - nums[i]) <=t 
                    ) {
             return true;           
            }
            bucket_mapper[bucket_id] = nums[i];
        }
        return false;
    }
};