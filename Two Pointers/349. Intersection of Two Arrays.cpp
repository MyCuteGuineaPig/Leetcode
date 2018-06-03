/*
349. Intersection of Two Arrays

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.

*/


class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return intersection(nums2, nums1);
        unordered_set<int>smap (nums1.begin(), nums1.end());
        unordered_set<int>rp;
        for(auto i: nums2){
            if(smap.find(i)!=smap.end())
                rp.insert(i);
        }
        return vector<int>(rp.begin(),rp.end());
    }
};

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return intersection(nums2, nums1);
        unordered_set<int>smap (nums1.begin(), nums1.end());
        vector<int>res;
        for(auto i: nums2){
            if(smap.find(i)!=smap.end()){
                smap.erase(i);
                res.push_back(i);
            }
        }
        return res;
    }
};




// Time:  O(max(m, n) * log(max(m, n)))
// Space: O(1)
// Binary search solution.
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return intersection(nums2, nums1);
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        auto begin = nums2.begin();
        vector<int>res;
        for(auto i: nums1){
            begin = lower_bound(begin,nums2.end(),i);
            if(begin!=nums2.end() && *begin == i){
                res.push_back(i);
                begin = upper_bound(begin,nums2.end(),i); //跳过i这个数，避免重复
            }
        }
        return res;
    }
};



// Time:  O(max(m, n) * log(max(m, n)))
// Space: O(1)
// Two pointers solution.
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return intersection(nums2, nums1);
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        auto it1 = nums1.begin(), it2 = nums2.begin();
        vector<int>res;
        while(it1!=nums1.end() && it2!=nums2.end()){
            if(*it1 < *it2)
                it1++;
            else if(*it1 > *it2) it2++;
            else{
                if(res.empty()||res.back()!=*it1)
                    res.push_back(*it1);
                it1++, it2++;
            }
        }
        return res;
    }
};
