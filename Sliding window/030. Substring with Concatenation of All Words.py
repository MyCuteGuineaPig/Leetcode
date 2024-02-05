"""
30. Substring with Concatenation of All Words

Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input:
  s = "wordgoodstudentgoodword",
  words = ["word","student"]
Output: []
"""

#保持window size不变 windowsize = m*k
import copy
class Solution:
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if len(s) == 0 or len(words) == 0: return []
        n, m, k, res = len(s), len(words), len(words[0]), []
        wdict = collections.Counter(words)
        for start_ in range(k):
            dic = copy.deepcopy(wdict) #用deepcopy 因为改变dic 会改变wdict
            count = m
            for j in range(start_,n,k):
                cur, start = s[j:j+k], j-(m-1)*k
                if dic[cur]>0:
                    count -= 1
                dic[cur] -= 1
                if count == 0: 
                    res.append(start)
                if start>=0:
                    prev =s[start: start+k]
                    dic[prev]+=1
                    if dic[prev] >0: count+=1
        return res


#两个map, 保持window size不变 windowsize = m*k，只有curstring 在words的map里出现，才发生count的变动
class Solution:
    def findSubstring(self, s, words):
        if len(s) == 0 or len(words) == 0: return []
        n, m, k, res = len(s), len(words), len(words[0]), []
        wdict = collections.Counter(words)
        for start_ in range(k):
            dic = collections.defaultdict(int)
            count = m
            for j in range(start_,n,k):
                cur, start = s[j:j+k], j-(m-1)*k
                dic[cur]+=1
                if cur in wdict and dic[cur]<=wdict[cur]:
                    count -= 1
                if count == 0: 
                    res.append(start)
                if start>=0:
                    prev =s[start: start+k]
                    dic[prev]-=1
                    if prev in wdict and dic[prev]<wdict[prev]:
                        count += 1               
        return res

#两个map，两个pointer，如果现在的map[curstring] > word map[curstring], 动start pointer
class Solution:
    def findSubstring(self, s, words):
        if len(s) == 0 or len(words) == 0: return []
        n, m, k, res = len(s), len(words), len(words[0]), []
        wdict = collections.Counter(words)
        for begin in range(k):
            dic = collections.defaultdict(int)
            count = m
            start = begin
            for j in range(begin,n,k):
                cur = s[j:j+k]
                if cur not in wdict:
                    dic = collections.defaultdict(int)
                    start = j+k
                    count = m
                else:
                    dic[cur]+=1
                    count -= 1
                    while dic[cur]>wdict[cur]:
                        dic[s[start: start+k]]-=1
                        start+=k
                        count += 1
                    if count == 0: 
                        res.append(start)
                        dic[s[start: start+k]]-=1
                        start += k
                        count += 1
        return res

#两个map，两个pointer，省去count，如果windows的间隔 m*k, append to result
class Solution:
    def findSubstring(self, s, words):
        if len(s) == 0 or len(words) == 0: return []
        n, m, k, res = len(s), len(words), len(words[0]), []
        wdict = collections.Counter(words)
        for begin in range(k):
            dic = collections.defaultdict(int)
            start = begin
            for j in range(begin,n,k):
                cur = s[j:j+k]
                if cur not in wdict:
                    dic = collections.defaultdict(int)
                    start = j+k
                else:
                    dic[cur]+=1
                    while dic[cur]>wdict[cur]:
                        dic[s[start: start+k]]-=1
                        start+=k
                    if j-start == (m-1)*k: 
                        res.append(start)
                        dic[s[start: start+k]]-=1
                        start += k
        return res