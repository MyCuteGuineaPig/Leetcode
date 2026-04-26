class Solution {
public:
    int longestStrChain(vector<string>& words) {
        unordered_map<string, int>dp;
        sort(words.begin(), words.end(), [](const string& word1, const string& word2){
            return word1.size() < word2.size();
        });

        int res = 1;
        for(auto& word: words){
            int depth = 1;
            for(int i = 0; i< word.size(); ++i){
                string tmp = word.substr(0, i) + word.substr(i+1, word.size()-i-1);
                if (dp.count(tmp)){
                    depth = max(depth, dp[tmp]+1);
                }
            }
            dp[word] = depth;
            res = max(res, dp[word]);
        }
        return res;
    }
};



// Two pointer
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), [&](const string& a, const string& b){
            return a.size() < b.size();
        });
        unordered_map<int, int>dp;
        int res = 1;
        for(int i = 0; i < words.size(); ++i){
            if(dp.count(i) == 0)
                dp[i] = 1;
            for(int j = i + 1; j < words.size() && words[j].size() <= words[i].size() + 1; ++j){
                if(words[j].size() == words[i].size()) continue; 
                int a = 0, b = 0; 
                while(b <words[j].size()) {
                    if (words[i][a] != words[j][b]) {
                        if(a != b) break;
                        ++b;
                    }
                    else{
                        ++a, ++b;
                    }
                }
                if(a == words[i].size() && b == a + 1) {
                    dp[j] = max(dp[j], dp[i]+1);
                    res = max(res, dp[j]);
                }
            }
        }
        return res;
    }
};

/*

Which one is faster 

🚀 So which is actually better?

Approach	            Complexity	Practical behavior
two pointer matching	O(n² · L)	Slow when n large
Substring DP (standard)	O(n · L²)	Much faster in practice


 */