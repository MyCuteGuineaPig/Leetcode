
/*
784. Letter Case Permutation

Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.
  Return a list of all possible strings we could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length at most 12.
S will consist only of letters or digits.

*/

/*

For Toogling the case of letter, xor with 32 beacuse letters are in such a way that toggling
 the 6th LSB will change its case from lower to upper and vice verse


 
*/

class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string>res;
        backtrack(res,S,0);
        return res;
    }
    
    void backtrack(vector<string>&res, string &S, int begin){
        res.push_back(S);
        for(int i = begin; i<S.size();i++){
            if(isalpha(S[i])){
                S[i] ^= 32;
                backtrack(res,S,i+1);
                S[i] ^= 32;
            }   
        }
    }
};



class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string>res;
        backtrack(res,S,0);
        return res;
    }
    
    void backtrack(vector<string>&res, string &S, int begin){
        res.push_back(S);
        for(int i = begin; i<S.size();i++){
            if(isalpha(S[i])){
                char ch = S[i];
                if(toupper(S[i])!=S[i])
                    S[i] = toupper(S[i]);
                else S[i] = tolower(S[i]);
                backtrack(res,S,i+1);
                S[i] = ch;
            }   
        }
    }
};



