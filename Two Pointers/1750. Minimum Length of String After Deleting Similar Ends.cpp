class Solution {
public:
    int minimumLength(string s) {
        int l = 0, r = s.size()-1;
        while(l < r && s[l] == s[r]){
            char org = s[l];
            while(s[l] == org && l <= r){
                ++l;
            }
            while(s[r] == org && l <= r){
                --r;
            }
        }
        return r-l + 1;
    }
};