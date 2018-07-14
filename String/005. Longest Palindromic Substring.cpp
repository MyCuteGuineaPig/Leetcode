/*
005. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"

*/


/*
*/


class Solution {
public:
    string longestPalindrome(string s) {
        int maxlen = 0, start = 0;
        for(int i = 0; i<s.size(); i++){
            int len1 = PalLen(s, i, i);
            int len2 = PalLen(s, i-1, i);
            if(len1 > maxlen){
                maxlen = len1; 
                start = i - maxlen/2;
            }
            if(len2 > maxlen){
                maxlen = len2; 
                start = i - maxlen/2;
            }
        }
        return s.substr(start, maxlen);
    }
    
    int PalLen(const string &s, int i , int j){
        while(i>=0 && j <s.size() && s[i]==s[j]){
            i--; j++;
        }
        return j-i-1;
    }
};

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        if (s.size() == 1) return s;
        int min_start = 0, max_len = 1;
        for (int i = 0; i < s.size();) {
        if (s.size() - i <= max_len / 2) break;
        int j = i, k = i;
        while (k < s.size()-1 && s[k+1] == s[k]) ++k; // Skip duplicate characters.
        i = k+1;
        while (k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1]) { ++k; --j; } // Expand.
        int new_len = k - j + 1;
        if (new_len > max_len) { min_start = j; max_len = new_len; }
        }
        return s.substr(min_start, max_len);
    }
};


/*
https://segmentfault.com/a/1190000008484167

manacher 算法：
建一个新的string 开头用$, 结尾用^(为了防止越界), 中间用#
这样可以把偶回文 和 奇回文 都转化成奇数，比如
如此，s 里起初有一个偶回文abba和一个奇回文opxpo，被转换为#a#b#b#a#和#o#p#x#p#o#，长度都转换成了奇数。

p[i] 表示以i为中小心的最长回文半径

i	        0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19  20 
s_new[i]	$	#	a	#	b	#	b	#	a	#	h	#	o	#	p	#	x	#	p	#   ^
p[i]		    1	2	1	2	5	2	1	2	1	2	1	2	1	2	1	4	1	2	1   
两个int mx，和id, mx 代表以 id 为中心的最长回文的右边界，也就是mx = id + p[id]。
mx是在当前回文右侧外的第一个点 mx点不包括在当前回文内


假设我们现在求p[i]，也就是以 i 为中心的最长回文半径，如果i < mx：
if (i < mx)  
    p[i] = min(p[2 * id - i], mx - i);

2 * id - i为 i 关于 id 的对称点，而p[j]表示以 j 为中心的最长回文半径，
因此我们可以利用p[j]来加快查找。

因为i小于mx, given (id - p[id], id + p[id])每个点都是对称的,不包括两端的点
做min的原因是 因为 i关于id的对称点是 id - (i-id) = 2*id - i = j, 我们要比较是p[j] 大还是 mx - i 
so  [i, mx) 也是对称(id - p[id], 2*id-i]的
    - p[2*id-i] 小于mx-i, p[j]的半径完全包括在当前最大回文内,  (为了方便解释，省去了#),
      p[i] = p[2*id - i],p[i]跟与id对称点一样
      比如 abcbzbcbao, 现在第二个c点, i=6, id = 4(z), mx =9(o), p[2*id -i] = p[2] = 2, mx - i = 3 
    - p[2*id - i] 大于mx - i, p[j]的半径部分包括在当前最大回文内, 
      表示i与id的对称点j, j 左面的点，不包括在当前回文内
      所以2*id - i左面的有些点与 i右侧的点不能对称
      比如 abcbazbcbo, 现在第二个c点, i=7, id = 5(z), mx =9(o), p[2*id -i] = p[2] = 3, mx - i = 2
      a(0) 没有包括在当前的回文内 a与o不等

而答案需要找到最长的substring回文, 通过snew的id，要找到s的开始的起点
字母位置是在2,4,6,8,10 (2n+2)
#的位置在1,3,5,7,9 (2n+1)
而snew[2] 对于s[0]， (2-1)/2 = 0, snew[4] 对于s[1] (4-1)/2 = 1
而以#为中心的最长的回文，代表偶回文，p[i]是奇数, 以字母为中心的代表奇回文，长度是偶数, 
# - 奇数会回到字母上or $,  字母减偶数还在字母上or $
所以maxid-maxlen(maxlen = p[i] = 最长回文长度+1) 会到当前最长回文最左侧(2n+2)的前一点(2n), 再除以2就是原来的s的回文的起始点n


            0	1	2	3	4	5	6	7	8	
s_new[i]	$	#	a	#	b	#	b	#	a
s                   0       1       2       3  

*/

class Solution {
public:
    string snew;
    string longestPalindrome(string s) {
        init(s);
        return manacher(s);
    }
    
    string manacher(const string & s){
        int mx = 0, maxlen = 0;
        int id, maxid;
        vector<int>p(snew.size());
        
        for(int i = 1; i<snew.size()-1;i++){
            if(i<mx){
                p[i] = min(p[id*2 - i], mx - i);
            }else 
                p[i] = 1;
            while(snew[ i + p[i]] == snew[i - p[i]])
                p[i]++;
            if(mx < i + p[i]){
                mx = i+p[i];
                id = i;
            }
            if( maxlen < p[i]){
                maxlen = p[i];
                maxid = i;
            }
            
        }
        //cout<<snew<<endl;
        //cout<<maxid<<" len "<<maxlen<<endl;
        return s.substr((maxid-maxlen)/2, maxlen-1);
    }
    
    void init(const string & s){
        snew = "$";
        for(int i = 0; i<s.size();i++){
            snew += "#";
            snew += s[i];
        }
        snew+="#^";
    }
    
};