/*
697. Degree of an Array

Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.

when I tried to understand this question, 
I found that I only need to return the value that (end index minus start index) of most frequent num. no anything about subarray.

*/

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int,vector<int>>cnt; //vec[0] = cnt, vec[1] = first position, vec[2] = end position
        for(int i = 0; i<nums.size(); i++){
            if(cnt.count(nums[i])){
                cnt[nums[i]][0]++; 
                cnt[nums[i]][2] = i;
            }else{
                cnt[nums[i]] = {1,i,i};
            }
        }

        int maxcnt = 0, res = nums.size();
        for(auto i: cnt){
            if(i.second[0]>maxcnt){
                maxcnt = i.second[0];
                res = i.second[2] - i.second[1] + 1;
            }
            else if(i.second[0] == maxcnt)
                res = min(res, i.second[2] - i.second[1] + 1);
        }
        return res;
    }
};


class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int res = nums.size();
        unordered_map<int, int> startIndex, count;
        int len = nums.size(), fre = 0;
        for (int i = 0; i < nums.size() ;i++) {
            if (startIndex.count(nums[i]) == 0) startIndex[nums[i]] = i;
            count[nums[i]]++;
            if (count[nums[i]] == fre){
                len = min(i - startIndex[nums[i]] + 1, len);
            }
            if (count[nums[i]] > fre){
                len = i - startIndex[nums[i]] + 1;
                fre = count[nums[i]];
            }
        }
        return len;
    }
};

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> counter, first;
        int res = 0, degree = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (first.count(nums[i]) == 0) first[nums[i]] = i;
            if (++counter[nums[i]] > degree) {
                degree = counter[nums[i]];
                res = i - first[nums[i]] + 1;
            } else if (counter[nums[i]] == degree)
                res = min(res, i - first[nums[i]] + 1);
        }
        return res;
    }
};

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> left, right;
        unordered_map<int, int> counts;
        for (int i = 0; i < nums.size(); ++i) {
            if (left.count(nums[i]) == 0) {
                left[nums[i]] = i;
            }
            right[nums[i]] = i;
            ++counts[nums[i]];
        }
        auto degree = max_element(counts.begin(), counts.end(),
                                  [](const pair<int, int>& a,
                                     const pair<int, int>& b) {
                                      return a.second < b.second;
                                  })->second;
        auto result = numeric_limits<int>::max();
        for (const auto& kvp : counts) {
            if (kvp.second == degree) {
                result = min(result, right[kvp.first] - left[kvp.first] + 1);
            }
        }
        return result;
    }
};