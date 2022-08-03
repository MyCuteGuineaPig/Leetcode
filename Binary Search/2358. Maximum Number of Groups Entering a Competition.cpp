/*
Sort all grades,
assign 1 student to the first group,
assign 2 student to the second group...
This can satify ith group < i+1th group for both size and sum.

So we need to find out the maximum result k that
1 + 2 + ... + k <= n

Prove:
Sort groups by size,
so the first group has size at least 1
so the second group has size at least 2
kth group has size at least k...

*/

class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int total = 0, k = 0, n = grades.size();
        while (total + k + 1 <= n) 
            total += ++k;
        return k;
    }
};

class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        if (grades.empty()) return 0;
        int l = 1, r = grades.size(), n = grades.size();
        while (l < r){
            long mid = l + (r-l + 1)/2;
            if ( mid *(mid+1)/2 <= n) 
                l = mid;
            else 
                r = mid -1;
        }
        return l;
    }
};

class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        return (int)(sqrt(grades.size() * 2 + 0.25) - 0.5);
    }
};