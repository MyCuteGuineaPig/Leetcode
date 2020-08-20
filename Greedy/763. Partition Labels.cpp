/*
763. Partition Labels

A string S of lowercase letters is given. 
We want to partition this string into as many parts as possible so that each letter appears in at most one part, 
and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.

*/


/*
Solution1 思路：
用unordered_map 记录最后出现的字母位置

把当前最后出现S的位置用last 表示, first表示当前set的其实
loop S, last = max(last, unordered_map[S[i]]), 这样last 就会一直表示当前出现最后一个字母的位置，
当index = last 的时候，make cut; 长度= last - fist + 1; first = i + 1
*/
class Solution {
public:
    vector<int> partitionLabels(string S) {
        unordered_map<int, int> lookup;
        for (int i = 0; i < S.length(); ++i) {
            lookup[S[i]] = i;
        }
        int first = 0, last = 0;
        vector<int> result;
        for (int i = 0; i < S.length(); ++i) {
            last = max(last, lookup[S[i]]);
            if (i == last) {
                result.emplace_back(i - first + 1);
                first = i + 1;
            }
        }
        return result;
    }
};

/*
Solution2 思路：
sliding window: 当现在这个字母不是最后一个出现时候，push 进set
当最后一次出现时候 erase 它，

如果set.size() 为0，表示之前所有字母都是最后出现，make cut

*/

class Solution {
public:
    vector<int> partitionLabels(string S) {
        unordered_map<int,int>cnt;
        for(auto s: S) cnt[s]++;
        int count = 0;
        vector<int>res; unordered_set<char>set;
        for(auto s: S){
            cnt[s]--;
            count++;
            if(cnt[s] == 0){ //先于!set.count(s) 是因为有的字母可能只出现一遍
                set.erase(s);
            }
            else if(!set.count(s)){
                set.insert(s);
            }
            if(set.empty()){
                res.push_back(count);
                count = 0;
            }
        }
        return res;
    }
};
/*

思路：
 unordered_map cnt记录后面还有此元素多少个
用一个unordered_set 记录当先出现的字母，
然后loop S，记录现在字母的长度，往unordered_set insert当字母，
然后loop 每个set中字母看后面是不是都没有set 中的char了，如果是, make cut;

*/
class Solution {
public:
    vector<int> partitionLabels(string S) {
        unordered_map<int,int>cnt;
        for(auto s: S) cnt[s]++;
        int count = 0;
        unordered_set<char>set;
        vector<int>res;
        for(auto s: S){
            set.insert(s);
            cnt[s]--;
            count++;
            bool flag = true;
            for(auto pre: set){
                if(cnt[pre]) {
                    flag = false;
                    break;
                }
            }
            if(flag){
                res.push_back(count);
                set.clear();
                count = 0;
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> partitionLabels(string S) {
        unordered_map<char,int>mp;
        for(auto i: S) mp[i]++;
        unordered_set<char>appear;
        vector<int>res;
        for(int i = 0, l = 0; i<S.size(); ++i){
            appear.insert(S[i]);
            if(--mp[S[i]] == 0){
                for(auto it = appear.begin(); it!=appear.end();)
                    if(mp[*it] == 0) appear.erase(it++);
                    else ++it;
                if(appear.empty()){
                    res.push_back(i-l+1);
                    l = i+1;
                }
            }
        }
        return res;
    }
};
