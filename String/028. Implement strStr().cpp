/*
28. Implement strStr()

Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

*/

/*
KMP Algorithm


Prefix array存的是在i点的最长的prefix 也是suffix长度 比如"ABA", 第三个a的最长的prefix 也是suffix 的长度是1 A 
而prefix array[i], 作为index, 是当前最长prefix 也是suffix 的下一位
"ABCAB" 最后一个B存的是2，最长的prefix也是suffix是AB，AB 下一位index是2 ('A')



prefix array存的是suffix 和prefix 重合的部分，一旦pattern 和text不符，我们不用回到pattern的起点和text相对应起点的下一个再开始下个寻找
我们可以不动text的位置，来移动pattern的位置，移动到上一个prefix也是suffix的后一位就是 j = prefix array[j-1]

比如下面的  text =    "ABABAB"   
           pattern = "ABABAC"
           到最后一位B 'B'!='C',  保持text位置不变, 动pattern， 动pattern到的上一个最长suffix也是prefix的下一位
            text =    "ABABAB"   
              pattern = "ABABAC" ， 发现match 继续寻找
 
"ABABABCABABABCABABABC"
"ABABAC"
             "A B A B A  C"
prefix array  0 0 1 2 3  0


*/
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()){
            return 0;
        }
        return kmp(haystack, needle);
    }

    int kmp(const string &text, const string & pattern){
        vector<int>prefix = computePrefix(pattern);
        int j = 0; 
        for(int i = 0; i<text.size(); i++){
            while(j>0 && pattern[j]!=text[i])
                j = prefix[j-1];
            if(pattern[j] == text[i])
                j++;
            //else j = 0; //可以不用else
            if(j == pattern.size())
                return i - j + 1;
        }
        return -1;
    }

    vector<int>computePrefix(const string& pattern){
        vector<int>p(pattern.size());
        int j = 0;
        for(int i = 1; i<pattern.size(); i++){
            while(j>0 && pattern[j]!= pattern[i]){
                j = p[j-1];
            }
            if(pattern[j] ==pattern[i])
                j++;
            //else j = 0;
           p[i] = j;
        }
        return p;
    }
};


// Time:  O(n * k)
// Space: O(k)
class Solution2 {
public:
    int strStr(string haystack, string needle) {
        for (int i = 0; i + needle.length() < haystack.length() + 1; ++i) {
            if (haystack.substr(i, needle.length()) == needle) {
                return i;
            }
        }
        return -1;
    }
};