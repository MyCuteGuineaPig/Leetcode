class Solution {
public:
    int minimumKeypresses(string s) {
        unordered_map<char, int>cnt;
        for(int i = 0; i < s.size(); ++i){
            ++cnt[s[i]];
        }
        auto cmp = [](const pair<char,int>&a, const pair<char,int>&b){
            return a.second < b.second;
        };
        priority_queue<pair<char,int>, vector<pair<char,int>>,decltype(cmp)>pq(cmp);
        for(auto it: cnt)
            pq.push({it.first, it.second});

        int res = 0;
        int tot = 9;
        int counter = 1;
        while (pq.size()){
            if(--tot < 0){
                tot = 8;
                ++counter;
            }
            auto [ch, c] = pq.top(); pq.pop();
            res += c*counter;
        }
        return res;
    }   
};


class Solution {
public:
    int minimumKeypresses(string s) {
        vector<int> freq (26, 0);
        for (char c: s) {
            freq[c - 'a']++;
        }
        
        sort(freq.begin(), freq.end(), greater<>());
        
        int ans = 0;
        int count = 0;
        for (int i = 0; i < 26; i++) {
            // whenever we start a new cycle of number (10th, 19th...), increase the count.
            // This is equivalent to saying: we need to press "two" keys for each character from now on.
            // Think what would happen if we had nine "a"s followed by more characters.  We will have to
            // do at least two presses for each character after first 9 most frequent characters.
            if (i%9 == 0)
                count++;
            ans += count * freq[i];
        }
        
        return ans;
    }
};