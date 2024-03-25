class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        unordered_set<string>st(forbidden.begin(), forbidden.end());
        int n = word.size();
        int res = 0, right = n -1;
        for (int left = n-1; left >= 0; --left){
            for(int k = left; k <= min(left + 10, right); ++k){
                string cur = word.substr(left, k-left + 1);
                if (st.count(cur)){
                    right = k-1;
                    break;
                }
            }
            res = max(res, right - left + 1);
        }
        return res;
    }
};