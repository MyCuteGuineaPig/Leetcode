/*
006. ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Explanation:

P     A     H     N
A  P  L  S  I  I  G
Y     I     R

Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

*/

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows >= s.size() || numRows == 1) return s;
        vector<string>zz(numRows);
        int r = 0, i = 0, direc = -1;
        while (i < s.length()){
            if(r == numRows-1 || r == 0) direc *= -1;
            zz[r] += s[i];
            i++; r += direc;
        }
        string res;
        return accumulate(begin(zz),end(zz),res);
    }
};

class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> vs(numRows, "");
        int n = s.length(), i = 0;
        while (i < n) {
            for (int j = 0; j < numRows && i < n; j++)
                vs[j].push_back(s[i++]);
            for (int j = numRows - 2; j >= 1 && i < n; j--)
                vs[j].push_back(s[i++]);
        }
        string zigzag;
        for (string v : vs) zigzag += v;
        return zigzag;
    } 
};


// Time:  O(n)
// Space: O(1)


/*
这个解是直接jump, 比如s = "PAYPALISHIRING", numRows = 4

P     I    N
A   L S  I G
Y A   H R
P     I

规定step是: 2*行数 - 2, step是每横行的jump的数

外层loop 是行，内层loop是每横行的开始，每内层loop需要看zigzag 有没有中间夹着的元素，
比如第二行，第一个横着的开始是A, 第二个横着开始是S, 看中间A和S有没有夹着的元素，有，是L
中间夹着元素的，只有在第1行到第numRows - 2行可能有，第0行和最后一行，没有中间夹着的元素


*/
class Solution {
public:
    string convert(string s, int numRows) {
        if(s.size()<= numRows || numRows == 1) return s;
        string res;
        int step = 2*numRows - 2;
        for(int i = 0; i<numRows; i++){
            for(int j = i; j<s.size(); j+=step){
                res+=s[j];
                if(i>0 && i<numRows-1 && j+ step - 2*i< s.size())
                   res += s[j+step - 2*i]; 
            }
        }
        return res;
    }
};


