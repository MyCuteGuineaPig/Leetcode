"""
816. Ambiguous Coordinates

Example 1:
Input: "(123)"
Output: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]
Example 2:
Input: "(00011)"
Output:  ["(0.001, 1)", "(0, 0.011)"]
Explanation: 
0.0, 00, 0001 or 00.01 are not allowed.
Example 3:
Input: "(0123)"
Output: ["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)", "(0.12, 3)"]
Example 4:
Input: "(100)"
Output: [(10, 0)]
Explanation: 
1.0 is not allowed.

"""
class Solution:
    def ambiguousCoordinates(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        def make(start, end):
            temp = []
            for i in range(start, end+1):
                left = S[start:i+1]
                right = S[i+1: end+1]
                if(left[0] != '0' or left == '0') and (not right or right[-1]!='0'): 
                    if right: left += "."
                    left += right
                    temp.append(left)
            return temp

        res = []
        for i in range(1, len(S)-1):
            left = make(1, i)
            right = make(i+1, len(S)-2)
            for l in left:
                for r in right:
                    res.append("("+l+", "+r+")")
        return res

class Solution:
    def ambiguousCoordinates(self, S):
        S = S[1:-1]
        def f(S):
            if not S or len(S) > 1 and S[0] == S[-1] == '0': return []
            if S[-1] == '0': return [S]
            if S[0] == '0': return [S[0] + '.' + S[1:]]
            return [S] + [S[:i] + '.' + S[i:] for i in range(1, len(S))]
        return ['(%s, %s)' % (a, b) for i in range(len(S)) for a, b in itertools.product(f(S[:i]), f(S[i:]))]


