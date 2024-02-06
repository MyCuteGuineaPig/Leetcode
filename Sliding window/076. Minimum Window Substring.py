"""
76. Minimum Window Substring

Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

"""

"""
Input:
"aaaaaaaaaaaabbbbbcdd"
"abcdd"

Expected:
"abbbbbcdd"

"""

class Solution:
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        if len(s) < len(t) or len(s) == 0 or len(t) == 0: return ""
        tdict = collections.Counter(t)
        dict = collections.defaultdict(int)
        start, count= 0, len(t)
        minID, minLen = 0, float('inf')
        for i, v in enumerate(s):
            if v in tdict: #只有当s[i]在t里，才变更count
                dict[v]+=1
                if dict[v] <= tdict[v]: #比如t是abc, s = "aaaab", 第一个a,count减到2，到第二个a，count一直是2，到b才减到1
                    count-=1
            while count == 0:
                if minLen > i - start + 1:
                    minLen = i-start+1
                    minID = start 
                if s[start] in tdict:
                    dict[s[start]]-=1
                    if dict[s[start]] <tdict[s[start]]: #比如t是abc, s = "aaaabc", 前面a都不减，直到最后一个a，count-1， 前面不减的原因是，前面a相比t是多余的
                        count+=1
                start+=1
        return s[minID: minLen+minID] if minLen != float('inf') else ""



class Solution:
    def minWindow(self, s, t):
        need, missing = collections.Counter(t), len(t)
        i = I = J = 0
        for j, c in enumerate(s, 1):
            missing -= need[c] > 0
            need[c] -= 1
            if not missing:
                while i < j and need[s[i]] < 0:
                    need[s[i]] += 1
                    i += 1
                if not J or j - i <= J - I:
                    I, J = i, j
        return s[I:J]