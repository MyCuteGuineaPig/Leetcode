/*
844. Backspace String Compare

Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

 

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.

*/


/*
两个pt，都是从s,t的尾部开始起，从后往前，while一直到当前不能skip，然后对比两个点是否一样，一样继续往前，不一样return false
*/
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int skipS = 0, skipT = 0;
        for (int i = S.length() - 1, j = T.length() - 1;
             i >= 0 || j >= 0;
             --i, --j) {
            auto x = findNextChar(S, &i, &skipS);
            auto y = findNextChar(T, &j, &skipT);
            if (x != y) {
                return false;
            }
        }
        return true;
    }

private:
    char findNextChar(const string& s, int *i, int *skip) {
        for (; *i >= 0; --(*i)) {
            if (s[*i] == '#') {
                ++(*skip);
            } else if ((*skip) > 0) {
                --(*skip);
            } else {
                return s[*i];
            }
        }
        return '\0';
    }
};



class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.size()-1, j = t.size()-1, skips=0, skipt = 0; //skips, skipt是当前可以skip的数
        while(i>=0 || j>=0){
            //cout<<i<<" j "<<j<<endl;
            while(i>=0 && (s[i]=='#' || skips>0)){  
            //一直跳到当前没有skip的i 
            //比如"a#c#" 直接跳到index = -1
                if(s[i]!='#') skips--;
                else skips++;
                i--;
            }
            while(j>=0 && (t[j]=='#' || skipt>0)){
                if(t[j]!='#') skipt--;
                else skipt++;
                j--;
            }
            //cout<<i<<" j "<<j<<endl;
            if(i<0 || j<0) break;
            if(s[i] == t[j]) {
                i--, j--; 
            }
            else{
                return false;
            }
        }
        return i==-1 && j==-1;
    }
};



class Solution {
public:
    bool backspaceCompare(string s, string t) {
        for(int i = s.size()-1, j = t.size()-1; ; i--, j--){
            for(int c = 0; i>=0 && (s[i]=='#' || c>0);) c += s[i--]=='#' ? 1: -1;
            for(int c = 0; j>=0 && (t[j]=='#' || c>0);) c += t[j--] == '#'? 1: -1;
            if(i < 0 || j<0 || s[i]!=t[j]) return i==-1 && j==-1;
        }
    }
};