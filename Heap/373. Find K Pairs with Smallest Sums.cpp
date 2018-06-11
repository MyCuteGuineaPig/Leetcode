/*
373. Find K Pairs with Smallest Sums


You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3 

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]

*/

/*
Use priority queue, p
*/

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if(nums1.empty() || nums2.empty()) return {};
        auto comp = [&](const pair<int,int>&a, const pair<int,int>&b){
            return nums1[a.first]+nums2[a.second] > nums1[b.first]+nums2[b.second];
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>,decltype(comp)>pq(comp);
        for(int i = 0; i<nums1.size();i++)
            pq.push({i,0});
        vector<pair<int,int>>res;
        while(--k>=0 && pq.size()){
            auto it = pq.top(); pq.pop();
            res.push_back({nums1[it.first],nums2[it.second]});
            if(++it.second<nums2.size()) pq.push(it);
        }
        return res;
    }
};


class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> pairs;
        if (nums1.size() > nums2.size()) {
            vector<pair<int, int>> tmp = kSmallestPairs(nums2, nums1, k);
            for (const auto& pair : tmp) {
                pairs.emplace_back(pair.second, pair.first);
            }
            return pairs;
        }

        using P = pair<int, pair<int, int>>;
        priority_queue<P, vector<P>, greater<P>> q;
        auto push = [&nums1, &nums2, &q](int i, int j) {
            if (i < nums1.size() && j < nums2.size()) {
                q.emplace(nums1[i] + nums2[j], make_pair(i, j));
            }
        };

        push(0, 0);
        while (!q.empty() && pairs.size() < k) {
            auto tmp = q.top(); q.pop();
            int i, j;
            tie(i, j) = tmp.second;
            pairs.emplace_back(nums1[i], nums2[j]);
            push(i, j + 1);
            if (j == 0) {
                push(i + 1, 0);  // at most queue min(m, n) space.
            }
        }
        return pairs; 
    }
};
