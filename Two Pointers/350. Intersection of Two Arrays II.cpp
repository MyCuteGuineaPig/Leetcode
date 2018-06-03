/*
350. Intersection of Two Arrays II
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

*/



// If the given array is not sorted and the memory is unlimited.
// Time:  O(m + n)
// Space: O(min(m, n))
// Hash solution.
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return intersect(nums2,nums1);
        unordered_map<int,int>m;
        for(int i: nums1) m[i]++;
        vector<int>res;
        for(int i: nums2){
            if(m.count(i)>0 && m[i]>0){
                res.push_back(i);
                m[i]--;
            }
        }
        return res;
    }
};

// If the given array is already sorted, and the memory is limited, and (m << n or m >> n).
// Time:  O(min(m, n) * log(max(m, n)))
// Space: O(1)
// Binary search solution.
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }

        // Make sure it is sorted, doesn't count in time.
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        vector<int> result;
        auto it = nums2.cbegin();
        for (const auto& i : nums1) {
            it = lower_bound(it, nums2.cend(), i);
            if (it != nums2.end() && *it == i) {
                result.emplace_back(*it++);
            }
        }
        
        return result;
    }
};

// If the given array is not sorted, and the memory is limited.
// Time:  O(max(m, n) * log(max(m, n)))
// Space: O(1)
// Two pointers solution.
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        // O(max(m, n) * log(max(m, n)))
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        auto it1 = nums1.cbegin(), it2 = nums2.cbegin();
        while (it1 != nums1.cend() && it2 != nums2.cend()) {
            if (*it1 < *it2) {
                ++it1;
            } else if (*it1 > *it2) {
                ++it2;
            } else {
                result.emplace_back(*it1);
                ++it1, ++it2;
            }
        }
        return result;
    }
};
/*
follow-up question: given twp array sorted, cannot load elements at once
complexity O(n)
space O(1)
*/
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return intersect(nums2,nums1);
        auto it1 = nums1.begin(), it2 = nums2.begin();
        vector<int>res;
        while(it1!=nums1.end()&&it2!=nums2.end()){
            if(*it1>*it2) it2++;
            else if(*it1<*it2) it2++;
            else{
                res.push_back(*it1);
                it1++; it2++;
            }
        }
        return res;
    }
};


class Solution {
public:
    vector<int> intersect(vector<int>& v1, vector<int>& v2) {
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        
        v1.erase(set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v1.begin()), v1.end());
        //set_intersection 返回的An iterator to the end of the constructed range.
        return v1;
    }
};