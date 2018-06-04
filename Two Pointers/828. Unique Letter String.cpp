/*
828. Unique Letter String

A character is unique in string S if it occurs exactly once in it.

For example, in string S = "LETTER", the only unique characters are "L" and "R".

Let's define UNIQ(S) as the number of unique characters in string S.

For example, UNIQ("LETTER") =  2.

Given a string S with only uppercases, calculate the sum of UNIQ(substring) over all non-empty substrings of S.

If there are two or more equal substrings at different positions in S, we consider them different.

Since the answer can be very large, retrun the answer modulo 10 ^ 9 + 7.

 

Example 1:

Input: "ABC"
Output: 10
Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
Evey substring is composed with only unique letters.
Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
Example 2:

Input: "ABA"
Output: 8
Explanation: The same as example 1, except uni("ABA") = 1.
 

Note: 0 <= S.length <= 10000.



*/

/*

Intuition:

Let's think about how a character can be found as a unique character.

Think about string "XAXAXXAX" and focus on making the second "A" a unique character.
We can take "XA(XAXX)AX" and between "()" is our substring.
We can see here, to make the second "A" counted as a uniq character, we need to:

insert "(" somewhere between the first and second A
insert ")" somewhere between the second and third A
For step 1 we have "A(XA" and "AX(A", 2 possibility.
For step 2 we have "A)XXA", "AX)XA" and "AXX)A", 3 possibilities.

So there are in total 2 * 3 = 6 ways to make the second A a unique character in a substring.
In other words, there are only 6 substring, in which this A contribute 1 point as unique string.

Instead of counting all unique characters and struggling with all possible substrings,
we can count for every char in S, how many ways to be found as a unique char.
We count and sum, and it will be out answer.

Explanation:

index[26][2] record last two occurrence index for every upper characters.
Initialise all values in index to -1.
Loop on string S, for every character c, update its last two occurrence index to index[c].
Count when loop. For example, if "A" appears twice at index 3, 6, 9 seperately, we need to count:
For the first "A": (6-3) * (3-(-1))"
For the second "A": (9-6) * (6-3)"
For the third "A": (N-9) * (9-6)"
Complexity:
One pass, time complexity O(N).
Space complexity O(1).


*/


/*
vector存上一个这个字母出现位置，和上上次这个字母出现位置,

(i - index[c][1]) * (index[c][1] - index[c][0]) 算的是在i之前, 
上一个与s[i]一样字母 s[ii], 所有包含s[ii]的unique letter的个数, 

s = "ABAB"
i 0 index[c][1] -1 index[c][0] -1 res 0
i 1 index[c][1] -1 index[c][0] -1 res 0
i 2 index[c][1] 0 index[c][0] -1 res 2  "A"(i=0), "AB"(i=0,1) 贡献了两个substring
i 3 index[c][1] 1 index[c][0] -1 res 6  "ABA"(i=[0,2]), "BA"(i=[1,2]), "AB"  (i=[0,1]), "B"(i=1) 贡献了四个substring

N
c = A,  index[c][1] = 2 index[c][0] = 1,  "BAB" (i=[1,3]), "BA" (i=[1,2]), "AB" (i=[2,3]), "A" (i=2)贡献了四个substring
C = B, index[c][1] = 3, index[c][0] = 2,  "AB" (i=[2,3]), B(i=3), 贡献了两个substring

"AB" 都会算两次，因为“A","B"都是在这个区间里出现了一次
"ABA" ”BAB" 会算一次，因为A出现了两回，B出现了两回，不会算

*/

class Solution {
public:
    int uniqueLetterString(string S) {
        int index[26][2], res = 0, N = S.length(), mod = pow(10, 9) + 7;
        memset(index, -1, sizeof(int) * 52);
        for (int i = 0; i < N; ++i) {
            int c = S[i] - 'A';
            cout<<"i "<<i<<" index[c][1] "<<index[c][1]<<" index[c][0] "<<index[c][0];
            res = (res + (i - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
            cout<<" res "<<res<<endl;
            index[c][0] = index[c][1];
            index[c][1] = i;
        }
        for (int c = 0; c < 26; ++c)
            res = (res + (N - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
        return res;
    }
};


/*
DP 解

showLastPosition是存的上一个以这个字母结束的最后一位
contribution[x] 以x结束的贡献的长度

cur[i] = cur[i - 1] - contribution[S.charAt(i)] + (i - showLastPosition[S.charAt(i)])
*/
class Solution {
public:
    int uniqueLetterString(string S) {
        
        int res = 0;
        if (S.size() == 0)
            return res;    
        vector<int>showLastPosition(128,-1);
        vector<int>contribution(128);
        int cur = 0;
        for (int i = 0; i < S.length(); i++) {
            char x = S[i];
            cur -= contribution[x]; 
            contribution[x] = (i - showLastPosition[x]);
            cur += contribution[x]; 
            showLastPosition[x] = i ;
            res += cur;
        }   
        return res;
    }

};