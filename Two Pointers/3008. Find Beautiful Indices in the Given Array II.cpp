class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int>match_a; 
        vector<int>match_b;
        kmp(a, s, match_a);
        kmp(b, s, match_b);
        vector<int>res;
        int i = 0, j = 0, match_a_size = match_a.size(), match_b_size = match_b.size();
        for(int i = 0; i < match_a_size; ++i){
            while(j < match_b_size && match_a[i] - match_b[j] > k){
                ++j;
            }
            if (j < match_b_size &&  abs(match_a[i] - match_b[j]) <= k ){
                res.push_back(match_a[i]);
            }
        }
        return res;
    }

    void kmp(const string& pattern, const string& text, vector<int>&res){
        vector<int>lps(pattern.size(), 0);
        computeLps(pattern, lps);
        int j = 0; 
        for(int i = 0; i<text.size(); ++i){
            while (j > 0 && pattern[j] != text[i])
                j = lps[j-1];
            if (pattern[j] == text[i])
                ++j;
            if (j == pattern.size()){
                res.push_back(i-j+1);
                j = lps[j-1];
            }
        }
    }

    void computeLps(const string& pattern, vector<int>&lps){
        int j = 0; 
        for(int i = 1; i < pattern.size(); ++i){
            while(j > 0 && pattern[j] != pattern[i])
                j = lps[j-1];
            if (pattern[j] == pattern[i])
                ++j;
            lps[i] = j;
        }
    }
};


class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int>match_a; 
        vector<int>match_b;
        kmp(a, s, match_a);
        kmp(b, s, match_b);
        vector<int>res;
        int i = 0, j = 0, match_a_size = match_a.size(), match_b_size = match_b.size();
        for(int i = 0; i < match_a_size; ++i){
            while(j < match_b_size && match_a[i] - match_b[j] > k){
                ++j;
            }
            if (j < match_b_size &&  abs(match_a[i] - match_b[j]) <= k ){
                res.push_back(match_a[i]);
            }
        }
        return res;
    }

    void kmp(const string& pattern, const string& text, vector<int>&res){
        string combine = pattern + "@" + text;
        int pattern_size = pattern.size();
        vector<int>lps(combine.size(), 0);
        
        int j = 0; 
        for(int i = 1; i < combine.size(); ++i){
            while(j > 0 && combine[i]!=combine[j])
                j = lps[j-1];
            if (combine[i] == combine[j])
                ++j;
            lps[i] = j;
        }
        for(int i = 0; i<combine.size(); ++i){
            if(lps[i] == pattern.size())
                res.push_back(i-2*pattern_size);
        }
        return;
    }
};