/*
347. Top K Frequent Elements
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.


*/


// Bucket Sort Solution
// Time:  O(n)
// Space: O(n)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int>m;
        for(auto i: nums)
            m[i]++;
        vector<vector<int>>bucket(n+1);
        for(auto j: m)
            bucket[j.second].push_back(j.first);
        vector<int>res;
        for(int i = n; i>=0; i--){
            for(int j = 0; j<bucket[i].size();j++){
                res.push_back(bucket[i][j]);
                if(res.size()==k) return res;
            }
        }
    }
};


// Quick Select Solution
// Time:  O(n) ~ O(n^2), O(n) on average.
// Space: O(n)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int>m;
        for(auto i: nums)
            m[i]++;
        vector<pair<int,int>>p;
        for(auto j: m)
            p.push_back({-j.second, j.first});
        nth_element(p.begin(),p.begin()+k-1, p.end());
        vector<int>res;
        for(int i = 0; i<k; i++){
            res.push_back(p[i].second);
        }
        return res;
    }
};


// Heap solution.
// Time:  O(nlogk)
// Space: O(n)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int>m;
        vector<int>res;
        priority_queue<pair<int,int>>p;
        for(auto i: nums) m[i]++;
        for(auto j: m) p.push({j.second, j.first});
        for(int i = 0; i<k; i++){
            res.push_back(p.top().second);
            p.pop();
        }
        return res;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counts;
        for (const auto& i : nums) {
            ++counts[i];
        }
        priority_queue<pair<int, int>> heap;
        for (const auto& kvp : counts) {
            heap.emplace(-kvp.second, kvp.first); 
            if (heap.size() == k + 1) { //一直保持k个元素在priority queue中
                heap.pop();
            }
        }
        vector<int> result;
        while (!heap.empty()) {
            result.emplace_back(heap.top().second);
            heap.pop();
        }
        return result;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int>m;
        vector<int>res;
        multiset<pair<int,int>>heap;
        for(auto i: nums) m[i]++;
        for(auto j: m) heap.insert({j.second, j.first});
        for(int i = 0; i<k; i++){
            res.push_back((*heap.rbegin()).second);
            heap.erase(*heap.rbegin());
        }
        return res;
    }
};



class Solution {
public:

vector<int> topKFrequent(vector<int>& nums, int k) {
	unordered_map<int, int>m;
	vector<unordered_set<int>>count(nums.size() + 1);
	for (auto i : nums)
		m[i]++;
	for (auto i : m)
		count[i.second].insert(i.first);
	vector<int>re;
	for (int i = nums.size(); re.size()<k && i >= 0; i--) {
		if (count[i].size()) {
			for (unordered_set<int>::iterator it = count[i].begin(); (re.size() < k) && it != count[i].end(); it++) {
				re.push_back(*it);
			}
		}
	}
	return re;
}

};

