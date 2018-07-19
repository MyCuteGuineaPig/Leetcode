/*
214. Shortest Palindrome


Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"

dcbaabcd



*/

/*
解法思路： 
把这个题目转化下： 其实是在问从index 0开始，部分最长的palindrome, 
如果我们得到这个最长的palidrome了, 可以reverse这个s内部分最长的palindrome 后面的，构成全体最短的palidrome 

比如 catacbd, 单词内部分最长的palidrome 是catac, 所以把部分最长的palidrom后面部分reverse 就构成了我们想要的最短的 dbcatacbd

可以利用kmp找到以index 0 开始最长的palindrome，
用 s + "#" + reverse(s) 这样从0开始最长的palidrome 就会在最后一个prefix显示出来，因为如果是最长的，会以#对称 + 头尾一样相等 （prefix即是suffix)，
比如catac, reverse 还是catac, 所以会以# 对称，并且相等，但是abc, reverse cba, 

最后一位肯定是部分最长的suffix（prefix即是suffix， 头尾相等，且掉个也相等）

input:

catacb

Temp String:

catacb # bcatac

KMP table:

c a t a c b # b c a t a c

0 0 0 0 1 0 0 0 1 2 3 4 5
*/


class Solution {
public:
    string shortestPalindrome(string s) {
        string rev = string(s.rbegin(), s.rend());
        vector<int>prefix = getPrefix(s+"#"+rev);
        string end = s.substr(prefix[prefix.size()-1]);
        reverse(end.begin(),end.end());
        return end+s;
    }

    vector<int>getPrefix(string && s){
        vector<int>vec(s.size());
        int j = 0;
        for(int i = 1; i<s.size();i++){
            while(j>0 && s[j]!=s[i])
                j = vec[j-1];
            if(s[i] == s[j])
                j++;
            vec[i] = j;
        }
        return vec;
    }
};


/*
不用#
先用kmp 求整个s的prefix array 

然后两个pointer， 一个pointer从s最后出发， 一个记录match的个数，如果s[i] == s[match] match++
如果match > 0 && s[i] != s[match] 不动i，动match回到上一个即是prefix 又是suffix的
比如 a b a b c... a b a b a
            -    -
一个在c，一个在a不match， 把match = prefix[match - 1] = 2, 发现match继续寻找
比如 a b a b c... a b a b a
        -        -
*/

class Solution {
public:
    string shortestPalindrome(string s) {
        vector<int>prefix = getPrefix(s);
        int maxPalLen = getmaxPalindrome(prefix, s);
        string nonPalindrome = s.substr(maxPalLen);
        reverse(nonPalindrome.begin(), nonPalindrome.end());
        return nonPalindrome+s;
    }

    vector<int>getPrefix(string & s){
        vector<int>vec(s.size());
        int j = 0;
        for(int i = 1; i<s.size();i++){
            while(j>0 && s[j]!=s[i])
                j = vec[j-1];
            if(s[i] == s[j])
                j++;
            vec[i] = j;
        }
        return vec;
    }

    int getmaxPalindrome(const vector<int>&prefix, const string &s){
        int match = 0;
        for(int i = s.size()-1; i>=0; i--){
            while(match > 0 && s[match]!= s[i]) match = prefix[match-1];
            if(s[match] == s[i]) match++;
        }
        return match;
    }
};



class Solution {
public:
    string shortestPalindrome(string s) {
        string snew = "$#";
        for(int i = 0; i<s.size();i++){
            snew += s[i];
            snew += "#";
        }
        snew += "^";
        int mxlen = manacher(snew);
        string nonPal = s.substr(mxlen);
        reverse(nonPal.begin(), nonPal.end());
        return nonPal + s;
    }

    int manacher(const string &snew){
        int id = 0, mx = 0;
        int mxlen = 1;
        vector<int>p(snew.size(), 0);
        for(int i = 1; i<snew.size()-1; i++){
            if(i<mx){
                p[i] = min(p[id*2 - i], mx - i);
            }else 
                p[i] = 1;
            while(snew[i-p[i]] == snew[i+p[i]])
                p[i]++;
            if(p[i] + i > mx){
                mx = p[i] + i;
                id = i;
                if(i - p[i] == 0) mxlen = p[i];
            }
        }
        return mxlen-1;
    }
};