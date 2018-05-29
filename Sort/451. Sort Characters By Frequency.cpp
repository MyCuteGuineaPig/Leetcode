/*
451. Sort Characters By Frequency

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

*/


// Bucket Sort Solution
// Time:  O(n)
// Space: O(n)
class Solution {
public:
    string frequencySort(string s) {
        int n = s.size();
        unordered_map<char,int>m;
        vector<vector<char>>bucket(n+1);
        string res;
        for(char i: s) m[i]++;
        for(auto it: m) bucket[it.second].push_back(it.first);
        for(int i = n; i>=1; i--)
            for(auto j: bucket[i])
                res+=string(i,j);
        return res;
    }
};


class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string,int> hash;
        vector<priority_queue<string,vector<string>,greater<string>>> cnt(words.size()+1);
        vector<string> res;
        for(int i=0; i < words.size(); i++)
            hash[words[i]]++;
        for(auto kv : hash)
            cnt[kv.second].push(kv.first);
        for(int i = cnt.size()-1; i > 0; i--)
        {
            while(!cnt[i].empty())
            {
                res.push_back(cnt[i].top());
                if(res.size() == k)
                    return res;
                cnt[i].pop();
            }
        }
    }
};


// Heap solution.
// Time:  O(nlogn)
// Space: O(n)
class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<char,int>m;
        priority_queue<pair<int,char>>pq;
        string res;
        for(char i: s) m[i]++;
        for(auto it: m) pq.push({it.second, it.first});
        while(pq.size()){
            res += string(pq.top().first,pq.top().second);
            pq.pop();
        }
        return res;
    }
};

class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<int,int>m;
        priority_queue<pair<int,int>>pq;
        string res;
        for(char i: s) m[i]++;
        for(auto it: m) pq.push({it.second, it.first});
        while(pq.size()){
            res += string(pq.top().first,pq.top().second);
            pq.pop();
        }
        return res;
    }
};

class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<int,int>m;
        set<pair<int,int>>heap;
        string res;
        for(char i: s) m[i]++;
        for(auto it: m) heap.insert({it.second, it.first});
        while(heap.size()){
            res += string((*heap.rbegin()).first,(*heap.rbegin()).second);
            heap.erase(*heap.rbegin());
        }
        return res;
    }
};


/*
sort 的解
// Time:  O(nlogn)

*/
class Solution {
public:
    string frequencySort(string s) {
        vector<int> v(256, 0);
        for (char c:s){
            ++v[c];
        }
        vector< pair<int, char>> vp;
        for(int i = 0; i < 256; i++){
            if(v[i]!= 0) vp.emplace_back(v[i], i);
        }
        sort(vp.rbegin(), vp.rend());
        string result;
        for (auto kp: vp ){
            result.append(kp.first, kp.second);
        }
        return result;
    }
};

class Solution {
public:
    string frequencySort(string s) {
        int counts[256] = {0};
        for (char ch : s)
            ++counts[ch];
        sort(s.begin(), s.end(), [&](char a, char b) { 
            return counts[a] > counts[b] || (counts[a] == counts[b] && a < b); 
        });
        return s;
    }
};