/*

532. K-diff Pairs in an Array

Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. 

Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.

Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
Note:
The pairs (i, j) and (j, i) count as the same pair.
The length of the array won't exceed 10,000.
All the integers in the given input belong to the range: [-1e7, 1e7].


*/


/*
One pass Solution
找的时候是 nums[i] + k, 和nums[i] - k， push的时候，nums[i]+k push nums[i], 而nums[i] - k push nums[i] - k
为了避免重复, set只push 下限，比如 k=2，现有[1,3,5], res set只push[1,3]
*/

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(k<0) return 0;
        unordered_set<int>set;
        unordered_set<int>res;
        for(auto i: nums){
            if(set.count(i-k) && !res.count(i-k))
                res.insert(i-k);
            if(set.count(i+k) && !res.count(i)) 
                res.insert(i);
            set.insert(i);
        }
        return res.size();
    }
};

/*
Two pass Solution
第一次pass 得到map
第二次pass，只向上数（+k) 或只向下数（-k),不能既向上数又向下数
*/



class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0)
            return 0;

        unordered_map<int, int> count;
        
        for (const auto& x : nums)
            ++count[x];
        
        int result = 0;
        for (const auto& kv : count) {
            if (!k) {
                if (kv.second >= 2)
                    ++result;
            } else if (count.count(kv.first - k)) {
                ++result;
            }
        }
        
        return result;
    }
};


class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(k<0)
            return 0;
        int ret=0;
        if(k==0){
            unordered_map<int,int> mp;
            for(int i=0; i<nums.size(); i++){
                if(++mp[nums[i]]==2)
                    ret++;
            }
        }else{
            unordered_set<int> us;
            for(int i=0; i<nums.size(); i++){
                us.insert(nums[i]);
            }
            for(auto num: us){
                if(us.find(num+k)!=us.end())
                    ret++;
            }
        }
        return ret;
    }
};
