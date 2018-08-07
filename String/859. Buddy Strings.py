"""
859. Buddy Strings

Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false

"""
class Solution:
    def buddyStrings(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: bool
        """
        if len(A) != len(B): return False
        swapa = swapb = "" 
        st = set()
        isrepeated = False
        for a, b in zip(A,B):
            if a!=b:
                if not swapa: 
                    swapa = a
                    swapb = b
                elif swapa != b or swapb != a: 
                    return False
            else:
                if a in st:isrepeated = False
                else:st.add(a)
        
        return isrepeated


class Solution:
    def buddyStrings(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: bool
        """
        if len(A) != len(B): return False
        if A == B: return len(set(A)) < len(A)
        dif = [(a,b) for a, b in zip(A,B) if a != b]
        return len(dif) == 2 and dif[0] == dif[1][::-1]