/*
424. Longest Repeating Character Replacement


Given a string that consists of only uppercase English letters, 
you can replace any letter in the string with another letter at most k times. 
Find the length of a longest substring containing all repeating letters you can get after performing the above operations.

Note:
Both the string's length and k will not exceed 104.

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.

*/


/*
This solution is great, best so far. However, it requires a bit more explanation.

Since we are only interested in the longest valid substring, our sliding windows need not shrink, 
even if a window may cover an invalid substring.
 We either grow the window by appending one char on the right, 
 or shift the whole window to the right by one. 
 And we only grow the window when the count of the new char exceeds the historical max count 
 (from a previous window that covers a valid substring).

That is, we do not need the accurate max count of the current window; 
we only care if the max count exceeds the historical max count; and that can only happen because of the new char.

*/

/*

Awesome solution, but it needs some more detailed explanation.
Many people know the problem can be reiterated as :
"longest substring where (length - max occurrence) <= k"
The key point is we are focusing on "longest".
So assume we initially found a valid substring, what do we do next?

Still valid even appended by one more char——then we are happy, just expand the window
It became invalid. But at this time, do we have to shrink the window?
——No, we shift the whole window rightwards by one unit. So that the length is unchanged.
The reason for that is , any index smaller than original "start", 
will never have the chance to lead a longer valid substring than current length of our window.
Do we need to update max in time?
——No. Once again, we focus on "longest". The length of valid substring is determined by what?
Max Occurrence + k
We only need to update max occurrence when it becomes larger, because only that can we generate a longer valid substring.
If we can't surpass the historic max occurrence, then we can not generate a longer valid substring from current "start", 
I mean the new windows's left bound. To some extend, this becomes a game to find max occurrence.
Or , a better understanding is:
"A game to eliminate inferior 'left bounds'.
*/


/*
当现在即使不满足最大window时（比如之前看最大window是7，出现最多数是3，k=2, res + 2 < 7, 不满足），
不需要减少window长度，只需增加window的开始位置，让最大windows保持不变

当前最大的windows是： 当前最多的数 + k,比如size = 7，  k=3,  ABAACCD, 只要更改3个，7个都可以变成A
所以看当前是不是满足最大window数是  end - start + 1 <= res + k, 如果end - start + 1(windows长度)，大于当前最大的长度，++start，保持当前长度


只增加start的position
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size(), start = 0, res = 0;
        unordered_map<char, int>m;
        for(int i = 0; i<n; i++){
            res = max(res, ++m[s[i]]);
            if(res + k < i - start + 1){
                m[s[start++]]--;
            }
        }
        return n - start;
    }
};

class Solution {
public:
    int characterReplacement(string s, int k) {
        int ans = 0, maxCnt = 0;
        vector<int> cnt(26);
        int n = s.length();
        int i = 0;
        for(int j = 0; j < n;) {
            maxCnt = max(maxCnt, ++cnt[s[j++] - 'A']);
            if(maxCnt + k < j - i)
                cnt[s[i++] - 'A']--;
        }
        return n - i;
    }
};



class Solution {
public:
    /*
    s = "AABACCA", k = 1
    (length of substring - number of times of the maximum occurring character in the substring) <= k
    */
    int characterReplacement(string s, int k) {
        if (s.empty())
        {
            return 0;
        }
        int start = 0, end = 0, maxCount = 0, ret = INT_MIN;
        vector<int> m(26, 0);
        while (end < s.size())
        {
            maxCount = max(maxCount, ++m[s[end++] - 'A']);
            
            while (end - start - maxCount > k)
            {
              --m[s[start++] - 'A'];
            }
            ret = max(ret, end - start);
        }
        return ret;
    }
};

class Solution {
public:
    int characterReplacement(string s, int k) {
        int i = 0, j = 0, ctr[91] = {};
        while (j < s.size()) {
            ctr[s[j++]]++;
            if (j-i - *max_element(ctr+65, ctr+91) > k)
                ctr[s[i++]]--;
        }
        return j - i;
    }
};


/*
Why binary search? If we can convert a substring of length x into a valid one (a string with all unique letters) using no more than k replacements, 
then it is clear that we can also convert a substring of length no more than x into a valid one. 
Thus, if we know how to answer the following decision problem efficiently, we can use binary search to guess the final answer.

The decision problem:
Is there a substring of length x such that we can make it consist of some unique letter with no more than k replacements?

The solution to this question is simple. We enumerate all substring of length x. 
For each substring, we denote the frequency of the most frequent letters in it as mode.
 Then, if x - mode <= k, the answer is yes. If x - mode > k holds for all substrings of length x, the answer is no. 
 This process can be done via a sliding-window in O(26 * n) = O(n) time.

Therefore, the total runtime is O(n log n).

*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        if(s.empty() || k >= s.size()) return s.size();
        int l = 1, r = s.size();
        while(l+1<r){
            int mid = (l+r)>>1;
            if(isValid(s,k, mid)) l = mid;
            else r = mid-1;
        }
        if(isValid(s,k, l+1)) l++;
        return l;
    }
    
    
    bool isValid(const string & s, const int& k, int len){
        vector<int>m(26,0);
        int n = s.size();
        for(int i = 0; i<n; i++){
            m[s[i]-'A'] ++;
            if(i>=len-1){
                if(*max_element(m.begin(), m.end()) + k >= len) {return true;  } 
                m[s[i-len+1]-'A']--;
            }  
        }
        return false;
    }
};