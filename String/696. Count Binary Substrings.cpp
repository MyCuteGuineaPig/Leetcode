/*
696. Count Binary Substrings

Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, 
and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's 
and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
Example 2:
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
Note:

s.length will be between 1 and 50,000.
s will only consist of "0" or "1" characters.

*/

/*
manacher 马拉车的变形： i + j的是右边界, j是最长半径

*/
class Solution {
public:
    int countBinarySubstrings(string s) {
        int res = 0;
        for(int i = 1; i<s.size();){
            if(s[i]!=s[i-1]){
                int j = 1;
                while( i+ j < s.size() && i-j-1>=0 && s[i-j-1] == s[i-1] && s[i+j] == s[i])
                    j++;
                res += j;
                //cout<<" i "<<i<<" j "<<j<<endl;
                i+=j;
            }
            else i++;
        }
        return res;
    }
};


// Time:  O(n)
// Space: O(1)

/*
cur是到现在之前，跟现在不同的连续的有几个
prevr是到第一个cur之前，跟cur不同的连续的有几个，
就是prev 代表的是上一个连续的s[i], cur是代表i之前连续的s[i-1]

比如   0 0  1  1  0  end
cur   1 2  1  2  1   1
prev  0 0  2  2  2   2 
res   0 0  0  0  2   3


*/
class Solution {
public:
    int countBinarySubstrings(string s) {
        auto result = 0, prev = 0, curr = 1;
        for (int i = 1; i < s.length(); ++i) {
            if (s[i - 1] != s[i]) {
                result += min(prev, curr);
                prev = curr, curr = 1;
            } else {
                ++curr;
            }
        }
        result += min(prev, curr);
        return result;
    }
};

class Solution {
public:
int countBinarySubstrings(string s) {
    int prevRunLength = 0, curRunLength = 1, res = 0;
    for (int i=1;i<s.length();i++) {
        if (s[i] == s[i-1]) curRunLength++;
        else {
            prevRunLength = curRunLength;
            curRunLength = 1;
        }
        if (prevRunLength >= curRunLength) res++;
    }
    return res;
}
};


class Solution {
public:
    int countBinarySubstrings(string s) {
        int t = 0;
        int zero = 0;
        int one = 0;
        int i = 0;
        while(i<s.length()){
            if(s[i]=='0'){
                while(i<s.length()&&s[i]=='0'){
                    i++;
                    zero++;
                }
                t+= min(zero,one);
                one = 0;
            }
            else{
                while(i<s.length()&&s[i]=='1'){
                    i++;
                    one++;
                }
                t+= min(one,zero);
                zero = 0;
            }
        }
        return t;
    }
};