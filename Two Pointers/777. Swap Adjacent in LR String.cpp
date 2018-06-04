/*
777. Swap Adjacent in LR String

In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", 
a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". 
Given the starting string start and the ending string end, 
return True if and only if there exists a sequence of moves to transform one string to the other.

Example:

Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
Output: True
Explanation:
We can transform start to end following these steps:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
Note:

1 <= len(start) = len(end) <= 10000.
Both start and end will only consist of characters in {'L', 'R', 'X'}.


"RXXXXX"
"XXXXXR"
return true
*/

/*
从swap可以看出, R是向前走，L是向后走（swap R 和L都需要X）

两个pointer，遇到X往前跳, 
如果start[i]!=start[j], 怎么换都不会把R和L调换()
    R X X X X L
    i
    L X X X X R
    j 

若start[i] == 'R' && i > j, R是需要往前走的，没办法往后退
    X R X X X L
      i
    R X X X X R
    j 

若sstart[i] == 'L' && i < j， L是需要往前后的，没办法往前退
    L X X X X L
    i
    X L X X X R
      j 

*/
class Solution {
public:
    bool canTransform(string start, string end) {
        int N = start.length();
        for (int i = 0, j = 0; i < N && j < N; ++i, ++j) {
            cout<<" in "<<i<<" j "<<j<<endl;
            while (i < N && start[i] == 'X') ++i;
            while (j < N && end[j] == 'X') ++j;
            cout<<" afterwhile i "<<i<<" j "<<j<<endl;
            if ((i < N) != (j < N)) {
                return false;
            } else if (i < N && j < N) {
                if (start[i] != end[j] ||
                    (start[i] == 'L' && i < j) ||
                    (start[i] == 'R' && i > j)) {
                    return false;
                }
            }
        }
        return true;
    }
};


class Solution {
public:
    bool canTransform(string start, string end) {
    	if (start.length() != end.length())
            return false;

        int pos = 0;

        for (int i = 0; i < start.length(); i++) {
             while (pos < end.length() && end[pos] == 'X')
		        pos++;
	         if (start[i] == 'X') continue;
	         if (pos >= end.length() || start[i] != end[pos])
		         return false;
	         if (start[i] == 'L' && i < pos || start[i] == 'R' && i > pos)
		         return false;
             pos++;
        }    
        while (pos < end.length() && end[pos] == 'X') //如果i==start.length() 而pos不等于end.length()只能是i的最后一直是X
            pos++;
        return pos == end.length();
    }
};