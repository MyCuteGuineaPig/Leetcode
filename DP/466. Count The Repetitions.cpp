/*
466. Count The Repetitions

Define S = [s,n] as the string S which consists of n connected strings s. For example, ["abc", 3] ="abcabcabc".

On the other hand, we define that string s1 can be obtained from string s2 if we can remove some characters from s2 
such that it becomes s1. For example, “abc” can be obtained from “abdbec” based on our definition, but it can not be obtained from “acbbe”.

You are given two non-empty strings s1 and s2 (each at most 100 characters long) and two integers 0 ≤ n1 ≤ 106 and 1 ≤ n2 ≤ 106. 
Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2]. Find the maximum integer M such that [S2,M] can be obtained from S1.

Example:

Input:
s1="acb", n1=4
s2="ab", n2=2

Return:
2


*/



/*

It’s easy to come up with a brute force solution and to find that there will be a repetitive pattern when matching S2 through S1. 
The only problem is how to use the repetitive pattern to save computation.

Fact:
If s2 repeats in S1 R times, then S2 must repeats in S1 R / n2 times.
Conclusion:
We can simply count the repetition of s2 and then divide the count by n2.

How to denote repetition:
We need to scan s1 n1 times. Denote each scanning of s1 as a s1 segment.
After each scanning of i-th s1 segment, we will have

The accumulative count of s2 repeated in this s1 segment.
A nextIndex that s2[nextIndex] is the first letter you’ll be looking for in the next s1 segment.
Suppose s1="abc", s2="bac", nextIndex will be 1; s1="abca", s2="bac", nextIndex will be 2

It is the nextIndex that is the denotation of the repetitive pattern.

Example:

Input:
s1="abacb", n1=6
s2="bcaa", n2=1

Return:
3
                    0  1   2 3 0      1    2 3 0      1    2 3 0  
S1 --------------> abacb | abacb | abacb | abacb | abacb | abacb 
repeatCount ----->    0  |   1   |   1   |   2   |   2   |   3
Increment of 
repeatCount     ->    0  |   1   |   0   |   1   |   0   |   1
nextIndex ------->    2  |   1   |   2   |   1   |   2   |   1
The nextIndex has s2.size() possible values, ranging from 0 to s2.size() - 1. Due to PigeonHole principle, 
you must find two same nextIndex after scanning s2.size() + 1 s1 segments.

Once you meet a nextIndex you’ve met before, you’ll know that the following nextIndexs and increments of repeatCount will repeat a pattern.

So let’s separate the s1 segments into 3 parts:

the prefix part before repetitive pattern
the repetitive part
the suffix part after repetitive pattern (incomplete repetitive pattern remnant)
All you have to do is add up the repeat counts of the 3 parts.

*/


/*

"bacaba"
3
"abacab"
1

需要prefix的例子
         b a c a b a  |  b a c a b a  |  b a c a b a  | 

                a b a |      c a b a  |  b a c a b a |  
cnt                 0 |            1  |            3 |
nextindex           3 |            1  |            1 |

需要suffix的例子
          a  a  a |   a  a  a|  a  a  a |

          a  a  a |   a  a  a|  a  a  a |
cnt          1    |   2     3|     4    |
nextindex       1 |         0|        1 |



*/
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        vector<int>repeated(n1+1,0);
        vector<int>nextIndex(n1+1,0);
        int j = 0, cnt = 0;
        for(int k = 1; k<=n1; k++){
            for(int i = 0; i<s1.size(); i++){
                if(s1[i] == s2[j])
                    j++;
                if(j==s2.length())
                    cnt++, j = 0;  
            }
            repeated[k] = cnt;
            nextIndex[k] = j;
            for(int start = 0; start<k; start++){
                if(nextIndex[start] == j){
                    int prefix = repeated[start];
                    int pattern = (repeated[k] - repeated[start])*((n1-start)/(k-start));
                    int suffix = repeated[start+(n1-start)%(k-start)]-repeated[start];
                    //cout<<prefix<<" pattern "<<pattern<<" suffix "<<suffix<<endl;
                    return (prefix+pattern+suffix)/n2;
                }
            }
        }
        return cnt/n2;
    }
};

/**
 * 
 * 最efficient的解
*/
以0 为底
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1Len = s1.size(), s2Len = s2.size(), index1 = 0, index2 = 0;
        unordered_map<int,pair<int,int>>nextIndex;
        while(index1<n1*s1Len){
            int i = index1 % s1Len, j = index2 % s2Len;
            if(s1[i] == s2[j]){
                if(j== 0){
                    j = (index2+1)% s2Len;
                    if(nextIndex.count(i)==0){
                        nextIndex[i] = {index1, index2};
                    }
                    else{
                        int l1 = index1-nextIndex[i].first, l2 = index2 - nextIndex[i].second;
                        index2 += (n1*s1Len - index1)/l1*l2;
                        index1 += (n1*s1Len - index1)/l1*l1;
                    }
                }
                if (index1++ < s1Len * n1) index2++;
            }else index1++;
        }
        return index2/n2/s2Len;
    }
};


以s2.length() 为底
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1Len = s1.size(), s2Len = s2.size(), index1 = 0, index2 = 0;
        unordered_map<int,pair<int,int>>nextIndex;
        while(index1<n1*s1Len){
            int i = index1 % s1Len, j = index2 % s2Len;
            if(s1[i] == s2[j]){
                if(j==s2Len-1){
                    if(nextIndex.count(i)==0){
                        nextIndex[i] = {index1, index2};
                    }
                    else{
                        int l1 = index1-nextIndex[i].first, l2 = index2 - nextIndex[i].second;
                        index2 += (n1*s1Len-1 - index1)/l1*l2;
                        index1 += (n1*s1Len-1 - index1)/l1*l1;
                    }
                }
                index1++, index2++;
            }else index1++;
        }
        return index2/n2/s2Len;
    }
};

class Solution {


/*
"bacaba"
3
"abacab"
1
      b  a  c  a   b  a | b  a  c  a   b  a | b  a  c  a  b  a |
         a         b  a |       c  a   b  a | b  a  c  a  b  a |
j   0                 3 |                 1 |                1 | 
l1  0                 5 |                11 |                17|   
l2  0                 2 |                 6 |                12|   

map = {{3,{3,5}} {3,{5,2}}, {1,{11,6}} };
     index1 17 index2 12
      nextIndex[j].first 11 nextIndex[j].second 6
      l1 = index1-dp[j].first =  6  //l1 重复的长度
      l2 = index2 - dp[j].second = 6 //l2 重复的长度
     (n1*s1Len - index1)
    (n1*s1Len - index1) 1 while 0
new index1 17 index2 12



"acb"
4
"ab"
2
        a   c   b |  a   c   b |  a   c   b |  a   c   b |
        a       b |  a       b |

以s2 length 为base的
map = { {2,{2,1}},  }}
len1 = index1 - dp[i1].first  = 5 - 2 = 3 
len2 = index2 - dp[i1].second = 3 - 1 = 2
change2 = (n1*s1Len-1 - index1)/l1*l2 = (4*3-1 - 5)/3*2 = 7/3*2 = 4;
changed1 = (n1*s1Len-1 - index1)/l1*l1 = (4*3-1 - 5)/3*3 = 6;
index1 += (n1*s1Len - index1)/l1*l1 = 5 + 6 = 11
index2 += (n1*s1Len - index1)/l1*l2 = 3 + 4 = 7;
index1++, index2++ 

return 8/2/2 = 1;

以s2 index 0 为base
map = { {0,{0,0}},  }}
len1 = index1 - dp[i1].first  = 3 - 0 = 3 
len2 = index2 - dp[i1].second = 2 - 0 = 2
change2 = (n1*s1Len - index1)/l1*l2 = (4*3 - 3)/3*2 = 6;
changed1 = (n1*s1Len - index1)/l1*l1 = (4*3 - 3)/3*3 = 9;
index1 += (n1*s1Len - index1)/l1*l1 = 3 + 9 = 12
index2 += (n1*s1Len - index1)/l1*l2 = 2 + 6 = 8; 

return 8/2/2 = 2;

*/