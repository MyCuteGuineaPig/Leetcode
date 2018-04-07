"""
784. Letter Case Permutation
"""

class Solution:
    def letterCasePermutation(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        self.res = []
        self.backtrack(S,0)
        return self.res

    def backtrack(self,s,begin):
        self.res.append(s)
        for i in range(begin,len(s)):
            if(s[i].isalpha()):
                new = s[i].lower() if s[i].isupper() else s[i].upper()
                self.backtrack(s[:i]+new+s[i+1:],i+1)



class Solution:
    def letterCasePermutation(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        if len(S) == 0:
            return [""]
        output = self.letterCasePermutation(S[1:])
        return [S[0].lower()+i for i in output] +[S[0].upper()+i for i in output] if S[0].isalpha() else [S[0]+i for i in output]


class Solution:
    def letterCasePermutation(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        res =[""]
        for ch in S:
            if ch.isalpha():
                res = [i+ch.upper() for i in res] + [i+ch.lower() for i in res]
            else:
                res = [i+ch for i in res]
        return res

class Solution:
    def letterCasePermutation(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        L = [[i.upper(), i.lower()] if i.isalpha() else i for i in S]
        return [''.join(i) for i in itertools.product(*L)]