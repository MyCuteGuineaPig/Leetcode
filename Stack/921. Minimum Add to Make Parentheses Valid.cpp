class Solution {
public:
    int minAddToMakeValid(string s) {
        int left_remaining = 0;
        int right_remaining = 0;
        for(int i = 0; i < s.size(); ++i){
            if (s[i] == '(') ++left_remaining;
            else {
                if (left_remaining > 0) --left_remaining;
                else ++right_remaining;
            }
        }
        return left_remaining + right_remaining;
    }
};