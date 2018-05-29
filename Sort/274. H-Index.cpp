/*
274. H-Index

Given an array of citations (each citation is a non-negative integer) of a researcher, 
write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: 
"A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

Example:

Input: citations = [3,0,6,1,5]
Output: 3 
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had 
             received 3, 0, 6, 1, 5 citations respectively. 
             Since the researcher has 3 papers with at least 3 citations each and the remaining 
             two with no more than 3 citations each, his h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.



*/

// Time:  O(n)
// Space: O(n)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int>count(n+1, 0);
        for(auto c: citations){
            if(c>=n) count[n]++;
            else count[c]++;
        }
        int c = 0;
        for(int h = n; h>=0; h--){
            c+=count[h];
            if(c>=h) return h;
        }
        return -1;
    }
};


// Time:  O(nlogn)
// Space: O(1)
class Solution2 {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), greater<int>());
        int h = 0;
        for (const auto& x : citations) {
            if (x >= h + 1) {
                ++h;
            } else {
                break;
            }
        }
        return h;
    }
};