class Solution {
public:
    string applySubstitutions(vector<vector<string>>& replacements, string text) {
        unordered_map<char, string> my_map;
        for(auto& pairs: replacements){
            my_map[pairs[0][0]] = pairs[1];
        }
        
        auto solve = [&](this auto&& solve, string& text)->string{
            if (text.find('%') == string::npos)
                return text;
            string res = "";
            for(int i = 0; i < text.length();++i){
                if(text[i] == '%'){
                    char c = text[i+1];
                    if(my_map[c].find('%') != string::npos){
                        my_map[c] = solve(my_map[c]);
                    }
                    res += my_map[c];
                    i+=2;
                    //skip %A%;
                }
                else {
                    res += text[i];
                }
            }
            return res;
        };
        return solve(text);
    }
};