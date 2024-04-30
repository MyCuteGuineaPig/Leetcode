class Solution {
public:
    string hash(const string& s){
        string res = "";
        for(int i = 1; i < s.size(); i++){
            res += (s[i] - s[i-1] + 26)%26 + 'a';
        }
        return res;
    }

    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>>key_set;
        for(auto & s:strings){
            key_set[hash(s)].push_back(s);
        }
        vector<vector<string>>res;
        for(auto it: key_set){
            res.push_back(it.second);
        }
        return res;
    }
};