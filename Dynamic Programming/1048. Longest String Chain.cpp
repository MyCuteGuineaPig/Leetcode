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