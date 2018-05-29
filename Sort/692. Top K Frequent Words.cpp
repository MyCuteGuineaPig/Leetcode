/*
692. Top K Frequent Words


Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, 
then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.

*/

/*
/ Time:  O(n + klogk) ~ O(n + nlogn)   klogk, nlogn 是insert 进set时间, 最多是每个string都不一样 nlogn sort, 最少是k个一组
// Space: O(n)
// Bucket Sort Solution
*/
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();
        unordered_map<string, int>m;
        vector<set<string>>bucket(n+1);
        vector<string>res;
        for(auto i: words) m[i]++;
        for(auto i: m) bucket[i.second].insert(i.first);
        for(int i = n; i>0 && res.size()<k; i--){
            for(auto j: bucket[i]){
                res.push_back(j);
                if(res.size()==k) break;
            }
        }
        return res;
    }
};


// Time:  O(n + klogk) on average
// Space: O(n)
// Quick Select Solution
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();
        unordered_map<string, int>m;
        vector<pair<int,string>>p;
        vector<string>res;
        for(auto i: words) m[i]++;
        for(auto i: m) p.push_back({-i.second,i.first});
        nth_element(p.begin(),p.begin()+k-1,p.end());// O(n) time on average.
        sort(p.begin(),p.begin()+k);// O(klogk) time.
        for(int i = 0; i<k; i++){
            res.push_back(p[i].second);
        }
        return res;
    }
};




// Time:  O(nlogk)
// Space: O(n)
// Heap Solution
class Solution2 {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> counts;
        for (const auto& word : words) {
            ++counts[word];
        }
        priority_queue<pair<int, string>> heap; //top 时word中频率最低的, 如果频率一样，返回的是最大的,cb在ab的前面（上面）,所以最后结果需要reverse
        for (const auto& kvp : counts) {
            heap.emplace(-kvp.second, kvp.first); 
            if (heap.size() == k + 1) {
                heap.pop();
            }
        }
        vector<string> result;
        while (!heap.empty()) {
            result.emplace_back(heap.top().second);
            heap.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();
        unordered_map<string, int>m;
        auto cmp = [](const pair<int,string>& a,const pair<int,string>&b ){
            return a.first < b.first || (a.first == b.first && a.second>b.second);
        };
        priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)>heap(cmp);
        vector<string>res;
        for(auto i: words) m[i]++;
        for(auto i: m) {
            heap.push({i.second,i.first});
        }
        while(res.size()<k){
            res.push_back(heap.top().second);
            heap.pop();
        }
        return res;
    }
};