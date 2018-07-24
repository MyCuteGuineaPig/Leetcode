/*
551. Student Attendance Record I

You are given a string representing an attendance record for a student. 
The record only contains the following three characters:
'A' : Absent.
'L' : Late.
'P' : Present.
A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his attendance record.

Example 1:
Input: "PPALLP"
Output: True
Example 2:
Input: "PPALLL"
Output: False

*/

class Solution {
public:
    bool checkRecord(string s) {
        int a = 0;
        for(int i = 0; i<s.size();i++){
            if(s[i] == 'A' && ++a>1) return false;
            if(s[i] == 'L'){
                int j = i;
                while(j<s.size() && s[j] == 'L') j++;
                if(j - i>=3) return false;
                i = j-1;
            }
        }
        return true;
    }
};


class Solution {
public:
    bool checkRecord(string s) {
        int count_A = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == 'A') {
                if (++count_A == 2) {
                    return false;
                }
            }
            if (i + 2 < s.length() && s[i] == 'L' && s[i + 1] == 'L' && s[i + 2] == 'L') {
                return false;
            }
        }
        return true;
    }
};


class Solution {
public:
    bool checkRecord(string s) {
        /*
        1- A.*A : 表示中间任意个数字符 
        */
        return !std::regex_search(s, std::regex("A.*A|LLL"));
    }
};