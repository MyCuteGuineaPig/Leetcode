
class Solution {
public:


    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j = 0;
        for(; i < word.size() && j < abbr.size(); ){
            if(isdigit(abbr[j])){
                int jump = 0;
                if(abbr[j] == '0') return false;
                while(j < abbr.size() && isdigit(abbr[j])){
                    jump = jump*10 + (abbr[j] - '0');
                    ++j;
                }
                i += jump;
            } else if ( word[i++] != abbr[j++]){
                return false;
            }
        }
        return i == word.size() && j == abbr.size();
    }
};

class Solution {
public:


    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j = 0;
        for(; i < word.size() && j < abbr.size(); ){
            if(isdigit(abbr[j])){
                int jump = 0;
                if(abbr[j] == '0') return false;
                while(j < abbr.size() && isdigit(abbr[j])){
                    jump = jump*10 + (abbr[j] - '0');
                    ++j;
                }
                i += jump;
            }
            if(i >= word.size() && j < abbr.size() || i<word.size() && j>=abbr.size() || i < word.size() && j < abbr.size() && word[i] != abbr[j]){
                return false;
            }
            if(i<word.size()) ++i;
            if(j < abbr.size())  ++j;
        }
        return i == word.size() && j == abbr.size();
    }
};