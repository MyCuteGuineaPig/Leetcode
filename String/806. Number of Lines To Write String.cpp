/*
806. Number of Lines To Write String

We are to write the letters of a given string S, from left to right into lines. 
Each line has maximum width 100 units, and if writing a letter would cause the width of the line to exceed 100 units, 
it is written on the next line. We are given an array widths, an array where widths[0] is the width of 'a', 
widths[1] is the width of 'b', ..., and widths[25] is the width of 'z'.

Now answer two questions: how many lines have at least one character from S, and what is the width used by the last such line? 
Return your answer as an integer list of length 2.

 

Example :
Input: 
widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "abcdefghijklmnopqrstuvwxyz"
Output: [3, 60]
Explanation: 
All letters have the same length of 10. To write all 26 letters,
we need two full lines and one line with 60 units.
Example :
Input: 
widths = [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "bbbcccdddaaa"
Output: [2, 4]
Explanation: 
All letters except 'a' have the same length of 10, and 
"bbbcccdddaa" will cover 9 * 10 + 2 * 4 = 98 units.
For the last 'a', it is written on the second line because
there is only 2 units left in the first line.
So the answer is 2 lines, plus 4 units in the second line.
 

Note:

The length of S will be in the range [1, 1000].
S will only contain lowercase letters.
widths is an array of length 26.
widths[i] will be in the range of [2, 10].


I literally have no idea what the problem is asking. I've been staring at it for 5 minutes
EDIT: Okay figured out what it was asking. Basically think of the widths list like microsoft word fonts, and the lines as holding

10 letters with 10 font
20 letters with 5 font
5 letters with 10 font and 10 letters with 5 font
50 letters with 2 font, and so forth.
The widths is an array of fonts per each letter of the alphabet, and the S is the string we are given to examine.
The answer is the number of lines we used up and the font we used up on the last line. 
Append these two answers into an array and return it.
*/


class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string S) {
        int lines = 0, cur = 0;
        for(auto i : S){
            if(cur + widths[i-'a'] > 100){
                cur =  widths[i-'a'];
                lines++;
            }else{
                cur += widths[i-'a'];
            }
        }
        return {lines+1, cur};
    }
};

class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string S) {
        vector<int> result(2);
        result.front() = 1;
        for (const auto& c : S) {
            const auto& w = widths[c - 'a'];
            result.back() += w;
            if (result.back() > 100) {
                ++result.front();
                result.back() = w;
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string S) {
        int res = 1, cur = 0;
        for (char c : S) {
            int width = widths[c - 'a'];
            res = cur + width > 100 ? res + 1 : res;
            cur = cur + width > 100 ? width : cur + width;
        }
        return {res, cur};
    }
};

class Solution {
public:
    vector<int> numberOfLines(vector<int>& ws, string s, int w = 0) {
    for (int c : s) w = (w % 100 + ws[c-'a'] > 100 ? w + 100 - w % 100 : w) + ws[c-'a'];
    return { w / 100 + 1, w % 100 };
    }
};