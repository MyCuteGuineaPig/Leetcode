/*

17. Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/


/*
back tracking 
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string>res;
        if(digits.size()==0) return res;
        string cur = "";
        vector<vector<char>>table(2, vector<char>());
        table.push_back({'a','b','c'}); // index 2
        table.push_back({'d','e','f'}); // 3
        table.push_back({'g','h','i'});
        table.push_back({'j','k','l'}); // 5
        table.push_back({'m','n','o'});
        table.push_back({'p','q','r','s'}); // 7
        table.push_back({'t','u','v'});
        table.push_back({'w','x','y','z'}); // 9
        backtracking(digits,table,res,cur,0);
        return res;
    }

    void backtracking(const string& digits, const vector<vector<char>> & table,vector<string>& res, string &cur, int index){
        if(index == digits.size()){
            res.push_back(cur);
            return;
        }
        int num = digits[index]-'0';
        for(auto i: table[num]){
            cur.push_back(i);
            backtracking(digits,table,res,cur,index+1);
            cur.pop_back();
        }
    }
};


/*
iterative
*/

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string>result;
        if(digits.size()==0) return result;
        result.push_back("");
        vector<vector<char>>table(2, vector<char>());
        table.push_back({'a','b','c'}); // index 2
        table.push_back({'d','e','f'}); // 3
        table.push_back({'g','h','i'});
        table.push_back({'j','k','l'}); // 5
        table.push_back({'m','n','o'});
        table.push_back({'p','q','r','s'}); // 7
        table.push_back({'t','u','v'});
        table.push_back({'w','x','y','z'}); // 9
        for(int i = 0; i<digits.size();i++){
            int num = digits[i]-'0';
            if(table[num].empty()) continue;
            vector<string>temp;
            for(int j = 0; j<table[num].size();j++){
                for(int k = 0; k<result.size();k++){
                    temp.push_back(result[k]+table[num][j]);
                }
            }
            swap(result,temp);
        }
        return result;
    }
};
