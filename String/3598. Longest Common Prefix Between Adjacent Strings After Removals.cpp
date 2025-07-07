/**
 * @brief 
 * 
 *  prefix[i] store the max between combination of i-1 and i or prefix[i-1]
 *  suffix[i] store the max between combination of i and i+1 or suffix[i+1]
 * 
 */
class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        function<int(int, int)> lcp = [&](int i, int j){
            for(int k = 0; k < min(words[i].length(), words[j].length()); ++k){
                if (words[i][k] != words[j][k])
                    return k;
            }
            return min((int)words[i].length(), (int)words[j].length());
        };

        int n = words.size();
        vector<int>res(n); 
        if (n == 1) return res;
        vector<int>suffix(n);
        vector<int>prefix(n);
        for(int i = 1; i < n - 1; ++i){
            prefix[i] = max(prefix[i-1], lcp(i, i-1));
        }
        for(int i = n - 2; i>0; --i){
            suffix[i] = max(suffix[i+1], lcp(i, i+1));
        }

        res[0] = suffix[1];
        res[n-1] = prefix[n-2];
        for(int i = 1; i<n-1; ++i){
            res[i] = max(prefix[i-1], max(suffix[i+1], lcp(i-1, i+1)));
        }
        return res;
    }
};