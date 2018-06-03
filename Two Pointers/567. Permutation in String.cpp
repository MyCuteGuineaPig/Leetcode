/*
567. Permutation in String

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. 
In other words, one of the first string's permutations is the substring of the second string.
Example 1:
Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].

input s1 = "pqzhi" s2 = "ghrqpihzybre"
Output: True
*/

/*
sliding window 可以是
1. 用一个vector 记录，++新来的，--过去的，直到vector所有数全为0，这样s1于s2吻合
2. 用两个vector 记录，一个记录s1, 一个记录s2, 直到s1 == s2
3. 用一个vector 记录, 记录符合s1,现在还剩多少的长度,

s1 = "a   d  c"
s2 = "d  c  d  a"
      0  1  2  3

i = 0,  m = [a: 1, d: 0, c:1] l = 2
i = 1,  m = [a: 1, d: 0, c:0] l = 1
i = 2,  m = [a: 1, d: -1, c:0] l = 1 (因为d小于0了，不减l)
++m[d] = 0  =>  m = [a: 1, d: 0, c:0]  
i = 3,  m = [a: 0, d: 0, c:0]  l = 0
 
*/



/*
sliding Window: window的框长为s1的长，

loop s2,
假如没有遇到s1中的，m[s2[i]-'a']-- 会变成负数, 
如果遇到s1中的， m[s2[i]-'a']-- 在自减之前就是正数，这样再让l自减， 直到自减成0，得到答案

如果没有到i没有答案，我们要在window中抹去窗口最左面的
如果窗口最左面没有出现在s1，自加后肯定会小于等于0，
但是如果最左面的出现在s1里，自加后会大于0，还有再自加l
                     0 1 2 3 4 5 6 7 8 9 10
比如 s1 = "abc", s2= "u i j i n j a b l l o"
                                 |    |  
                                 窗口在a到l之间，i=8的位置，i+1-s1.length() = 6
                                
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int>m(26);
        for(auto c: s1)
            m[c-'a']++;
        for(int i = 0, l = s1.length();i<s2.length();i++){
            if(m[s2[i]-'a']-->0) l--;
            if(l==0) return true;
            int start = i+1-s1.length();
            if(start>=0 && ++m[s2[start]-'a']>0)
                l++;
        }
        return false;
    }
};

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int>m(26);
        for(auto c: s1)
            m[c-'a']++;
        for(int i = 0, l = s1.length();i<s2.length();i++){
            int start = i - s1.length();
            if(start>=0 && ++m[s2[start]-'a']>0) l++;
            if(m[s2[i]-'a']-->0) l--;
            if(l==0) return true;
        }
        return false;
    }
};

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int s1s = s1.size(), s2s = s2.size(), start = 0, cnt = 0, arr[26] = {};
        for (auto l : s1) ++arr[l - 'a'];
        for (auto i = 0; i < s2s && cnt < s1s; ++i) {
            if (arr[s2[i] - 'a'] > 0) {
                --arr[s2[i] - 'a'];
                ++cnt;
            }
            else {
                while (s2[start++] != s2[i]) {
                    ++arr[s2[start - 1] - 'a'];
                    --cnt;
                }
            }
        }
        return cnt == s1s;
    }
};

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<int, int> counts;
        for(auto c : s1) counts[c]--;
        for(int i = 0; i < s2.length(); i++) {
            counts[s2[i]]++;
            if (counts[s2[i]] == 0) counts.erase(s2[i]);
            if (i >= s1.length()) {
                counts[s2[i - s1.length()]]--;
                if (counts[s2[i - s1.length()]] == 0) counts.erase(s2[i - s1.length()]);
            }
            if (!counts.size()) return true;
        }
        return false;
    }
};
/*
跟上面解原理是一样的
*/
class Solution {
    vector<int> count;
    int non_zero;
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        
        count = vector<int>(26, 0);
        non_zero = 0;
        for (auto c: s1) {
            update(c - 'a', 1);
        }
        for (int i = 0; i < n1; i++) {
            update(s2[i] - 'a', -1);
        }
        if (non_zero == 0) {
            return true;
        }
        for (int i = n1; i < n2; i++) {
            update(s2[i - n1] - 'a', 1);
            update(s2[i] - 'a', -1);
            
            if (non_zero == 0) {
                return true;
            }
        }
        return false;
    }
    
    void update(int index, int delta) {
        int before = count[index];
        int after = before + delta;
        count[index] = after;
        
        if (before != 0 && after == 0) {
            non_zero--;
        }
        if (before == 0 && after != 0) {
            non_zero++;
        }
    }
};


/*
用两个vector slide 如果两个vector（window）一样，证明温和
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1=s1.size(),n2=s2.size();
        vector<int> m1(128),m2(128);
        for(int i=0;i<n1;i++){
            ++m1[s1[i]],++m2[s2[i]];
        }
        if(m1==m2) return true;
        for(int i=n1;i<n2;i++){
            ++m2[s2[i]];
            --m2[s2[i-n1]];
            if(m1==m2) return true;
        }
        return false;
    }
};


/*
用一个vector 记录，++新来的，--过去的，直到vector所有数全为0，这样s1于s2吻合
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int>m(26);
        for(int i = 0; i<s1.length();i++)
            m[s1[i]-'a']++;
        for(int i = 0;i<s2.length();i++){
            m[s2[i]-'a']--;
            if(i>=s1.length()) m[s2[i-s1.length()]-'a']++;
            if(allzero(m)) return true;
        }
        return false;
    }
    
    bool allzero(vector<int>&m){
        for(int i = 0; i<26;i++){
            if(m[i]!=0) return false;
        }
        return true;
    }
};