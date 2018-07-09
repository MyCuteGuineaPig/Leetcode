"""
438. Find All Anagrams in a String


Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
"""

# sliding window 用count记录p中出现次数, count = 0, append res 
class Solution:
    def findAnagrams(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: List[int]
        """
        lenn = count = len(p)
        res = []
        dic = collections.Counter(p)
        for i, v in enumerate(s):
            start= i - lenn + 1
            if dic[v] > 0: 
                count -=1 
            dic[v]-=1
            if count == 0: 
                res.append(start)
            if start>=0:
                dic[s[start]]+=1
                if dic[s[start]] > 0:
                    count += 1
        return res 

#sliding window 用 two pointer, 一个map，只有在比较对象中出现过得加减， 如果two pointer之间距离 ==p的长度 append to res 
class Solution:
    def findAnagrams(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: List[int]
        """
        lenn, j = len(p), 0
        res = []
        dic = collections.Counter(p)
        for i, v in enumerate(s):
            if v in dic: 
                dic[v]-=1
                while dic[v] < 0: 
                    dic[s[j]]+=1
                    j+=1
                if dic[v] == 0 and i - j == lenn - 1:
                    res.append(j)
            else: 
                while j <= i: 
                    if s[j] in dic:
                        dic[s[j]]+=1
                    j+=1
        return res 


#sliding window 用 two pointer, 一个map, 所有字母相加减, 如果two pointer之间距离 ==p的长度 append to res 
class Solution:
    def findAnagrams(self, s, p):
        lenn, j = len(p), 0
        res = []
        dic = collections.Counter(p)
        for i, v in enumerate(s):
            dic[v]-=1
            while j<=i and dic[v] < 0: 
                dic[s[j]]+=1
                j+=1
            if dic[v] == 0 and i - j == lenn - 1:
                res.append(j)
        return res 

