class Solution {
public:
    int minSteps(string s, string t) {
        vector<int> freq(26, 0);
        for(int i=0;i<t.size();i++) freq[t[i]-'a']++;
        for(int i=0;i<s.size();i++) freq[s[i]-'a']--;
        int res=0;
        for(int i=0;i<26;i++) res+=max(0, freq[i]);
        return res;
    }
};


class Solution {
public:
    int minSteps(string s, string t) {
        int cnt[26] = {};
        for (auto ch : s) ++cnt[ch - 'a'];
        for (auto ch : t) --cnt[ch - 'a'];
        return accumulate(begin(cnt), end(cnt), 0, [](int s, int n) {return s + abs(n); }) / 2;
    }
};