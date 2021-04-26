/*
The basic idea is 'a' < 'e' < 'i' < 'o' < 'u'. So this problem is to find the length of the longest non-decreasing
 substring that has five different chars.

*/

class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int start = 0, cnt = 1, res = 0;
        for(int i = 1; i<word.size(); ++i){
            if(word[i] < word[i-1]){
                start = i;
                cnt = 1;
            }
            if(word[i] > word[i-1])
                ++cnt;
            if(cnt == 5)
                res = max(res, i-start+1);
        }
        return res;
    }
};



class Solution {
public:
    int longestBeautifulSubstring(string word) {
        const auto n = word.size();

        int cnt = 1;
        int len = 1;
        int max_len = 0;
        for (int i = 1; i != n; ++i) {
            if (word[i - 1] == word[i]) {
                ++len;
            } else if (word[i - 1] < word[i]) {
                ++len;
                ++cnt;
            } else {
                cnt = 1;
                len = 1;
            }
            
            if (cnt == 5) {
                max_len = max(max_len, len);
            }
        }
        return max_len;
    }
};

class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int res = 0;
        for (int i = 0, j = 0; i < word.size(); ++i) {
            if (word[i] == 'a') {
                int cnt = 0;
                for (j = i + 1; j < word.size() && word[j - 1] <= word[j]; ++j)
                    cnt += word[j - 1] < word[j];
                if (cnt == 4)
                    res = max(res, j - i);
                i = j - 1;
            }
        }
        return res;
    }
};