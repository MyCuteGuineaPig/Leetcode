class Solution {
public:
    bool isNumber(string s) {
        bool seenDigit = false; 
        bool seenExponent = false;
        bool seenDot = false;
        for(int i = 0; i < s.size(); ++i){
            char c = s[i];
            if (c >= '0' && c <= '9')
                seenDigit = true;
            else if (c == '+' || c == '-'){
                if(i > 0 && s[i-1] != 'E' && s[i-1] != 'e') return false;
            } else if (c == 'e' || c == 'E'){
                if (seenExponent || !seenDigit)
                    return false;
                seenExponent = true;
                seenDigit = false; //require number after e, E
            } else if (c == '.'){ 
                if (seenDot || seenExponent)//e 不能在. 前面
                    return false;
                seenDot = true;
            } else 
                return false;
        }
        return seenDigit;
    }
};


class Solution {
public:
    bool isNumber(string s) {
        // This is the DFA we have designed above
        map<string, int> dfa[8] = {
            {{"digit", 1}, {"sign", 2}, {"dot", 3}},
            {{"digit", 1}, {"dot", 4}, {"exponent", 5}},
            {{"digit", 1}, {"dot", 3}},
            {{"digit", 4}},
            {{"digit", 4}, {"exponent", 5}},
            {{"sign", 6}, {"digit", 7}},
            {{"digit", 7}},
            {{"digit", 7}}
        };
        int current_state = 0;
        string group;
        for (char c : s) {
            if (isdigit(c)) {
                group = "digit";
            } else if (c == '+' || c == '-') {
                group = "sign";
            } else if (c == 'e' || c == 'E') {
                group = "exponent";
            } else if (c == '.') {
                group = "dot";
            } else {
                return false;
            }
            if (dfa[current_state].find(group) == dfa[current_state].end()) {
                return false;
            }
            current_state = dfa[current_state][group];
        }
        return current_state == 1 || current_state == 4 || current_state == 7;
    }
};