

"""
17. Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.

"""


class Solution:
    def letterCombinations(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """
        if len(digits) == 0: 
            return []
        lookup, result = ["", "", "abc", "def", "ghi", "jkl", "mno", \
                          "pqrs", "tuv", "wxyz"], []
        self.backtracking(digits,lookup,result,"",0)
        return result
    
    def backtracking(self, digits, lookup,result, cur, index):
        if index == len(digits):
            result.append(cur)
            return
        for i in lookup[int(digits[index])]:
            self.backtracking(digits,lookup,result,cur+i, index+1)
