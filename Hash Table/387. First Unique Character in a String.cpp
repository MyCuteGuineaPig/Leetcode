/*
387. First Unique Character in a String


Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.

*/




class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> m;
        for (auto &c : s) {
            m[c]++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (m[s[i]] == 1) return i;
        }
        return -1;
    }
};

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, pair<int, int>> m;
        int idx = s.size();
        for (int i = 0; i < s.size(); i++) {
            m[s[i]].first++;
            m[s[i]].second = i;
        }
        for (auto &p : m) {
            if (p.second.first == 1) idx = min(idx, p.second.second);
        }
        return idx == s.size() ? -1 : idx;
    }
};

class Solution {
public:
    int firstUniqChar(string s) {
        vector<int>v(26,0);
        for(int i =0,j=0;i<s.size();i++){
            v[s[i]-'a']++;
        }
        for(int i =0,j=0;i<s.size();i++){
            if(v[s[i]-'a']==1)
                return i;
        }
        return -1;
    }
};

// Time:  O(n)
// Space: O(n)

// One-pass solution.
//candidate 是pass一次的，如果pass 第二次，就把它删了，不是最优解，因为erase浪费太多时间
class Solution {
public:
    int firstUniqChar(string s) {
        using IT = list<int>::iterator;

    	list<int> candidates;
    	unordered_map<char, IT> lookup;
    	for (int i = 0; i < s.length(); ++i) {
    		const auto c = s[i];
    		if (lookup.count(c)) {
    			if (lookup[c] != candidates.end()) { //之前插入，第二次进来，删除candidate
    				candidates.erase(lookup[c]);//erase浪费太多时间
    			}
    			lookup[c] = candidates.end(); //把lookup[c]设成end，避免再次删除
    		} else {
    			lookup[c] = candidates.emplace(candidates.end(), i); //每次都指向最后一个candidate iter，不是end
    		}
    	}
    	return candidates.empty() ? -1 : candidates.front();
    }
};