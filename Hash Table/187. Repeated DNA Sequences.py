"""
187. Repeated DNA Sequences


All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, 
for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

Example:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"

Output: ["AAAAACCCCC", "CCCCCAAAAA"]

"""

class Solution:
    def findRepeatedDnaSequences(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        st, res = set(), set()
        temp, mp = 0, {"A":0, 'C': 1, 'G': 2, 'T':3}
        for i, v in enumerate(s):
            temp = temp << 2 | mp[v]
            if i >= 9: 
                if temp in st:
                    res |= {s[i-9:i+1]}
                st |= {temp}
                temp = temp & (2**18 -1)
        return list(res)