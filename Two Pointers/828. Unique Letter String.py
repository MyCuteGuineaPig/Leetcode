"""
828. Unique Letter String

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
 
"""

class Solution:
    def uniqueLetterString(self, S):
        """
        :type S: str
        :rtype: int
        """
        dic = collections.defaultdict(list)
        res, mod = 0, 10**9+7
        for i, v in enumerate(S):
            if v not in dic:
                dic[v] = [-1,i]
            else:
                res = (res + ((i-dic[v][1])*(dic[v][1]-dic[v][0])%mod))%mod
                dic[v][0] = dic[v][1]
                dic[v][1] = i
        i = len(S)
        for key, v in dic.items():
            res = (res + ((i-v[1])*(v[1]-v[0])%mod))%mod
        return res


class Solution:
    def uniqueLetterString(self, S):
        lastpos = collections.defaultdict(lambda: -1)
        contribution = collections.defaultdict(int)
        res, mod, cur = 0, 10**9+7, 0   #cur是到当前为止，所有字母的到此位置的贡献值
        for i, v in enumerate(S):
            res, lastpos[v], contribution[v], cur = (res + cur - contribution[v]+(i-lastpos[v]))%mod, i,\
             i-lastpos[v], cur-contribution[v]+(i-lastpos[v])
        return res

class Solution:
    def uniqueLetterString(self, S):
        lastpos = collections.defaultdict(lambda: -1)
        contribution = [0]*128
        res, mod = 0, 10**9+7
        for i, v in enumerate(S):
            lastpos[v], contribution[ord(v)] =  i, i-lastpos[v]
            res += sum(contribution)%mod
        return res

"""

after each for loop,cur = contribution[0] + contribution[1] + ... + contribution[127]
cur 等于每个字母贡献值

Your input
"ABCCB"
Your stdout
A  res  1  contribution  1 cur 1
B  res  4  contribution  2 cur 3
C  res  10  contribution  3 cur 6
C  res  14  contribution  1 cur 4   4 = ABCC (2), BCC(1). C(1), CC(0) 
B  res  19  contribution  3 cur 5   5 = ABCCB(1), BCCB(0), CCB(1), CB(2), B(1)   {Contribution = 3, 贡献的3个是，3个单独的B: CCB, CB, B}

"""