/*
434. Number of Segments in a String

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5

*/

class Solution {
public:
    int countSegments(string s) {
        int count = !s.empty() && s.back() != ' ' == true ? 1 :0;
        for(int i = 1; i<s.size(); i++){
            if(s[i] == ' ' &&s[i-1]!=' ')
                count++;
        }
        return count;
    }
};



class Solution {
public:
    int countSegments(string s) {
        int count = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] != ' ' &&  (i==0 || s[i-1]==' '))
                count++;
        }
        return count;
    }
};


class Solution {
public:
    int countSegments(string s) {
        int res = 0;
        for (int i = 0; i < s.size(); i++) 
            res += s[i] != ' ' && (i + 1 == s.size() || s[i + 1] == ' ');
        return res;
    }
};

class Solution {
public:
    int countSegments(string s) {
        stringstream ss(s);
        int result = 0;
        string temp;
        
        while(ss>>temp)
            result++;
        
        return result;
    }
};

class Solution {
public:
    int countSegments(string s) {
        return regex_replace(regex_replace(s, regex("\\S+"), "x"), regex(" "), "").size();
    }
};