"""
8. String to Integer (atoi)

Example 1:

Input: "42"
Output: 42
Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.
Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.

"""

class Solution:
    def myAtoi(self, str):
        """
        :type str: str
        :rtype: int
        """
        i = num = 0
        while i<len(str) and str[i] == " ":
            i+=1
        if i>=len(str) or not str[i].isdigit() and str[i]!='+' and str[i]!='-':
            return 0
        sign = -1 if str[i] == '-' else 1
        if not str[i].isdigit():
            i+=1
        while i < len(str):
            if not str[i].isdigit(): 
                break
            num = num * 10 + int(str[i])
            i+=1
        num *= sign
        return 2147483647 if num > 2147483647 else -2147483648 if num <-2147483648 else num

class Solution(object):
    def myAtoi(self, s):

        ###better to do strip before sanity check (although 8ms slower):
        #ls = list(s.strip())
        #if len(ls) == 0 : return 0
        if len(s) == 0 : return 0
        ls = list(s.strip())
        
        sign = -1 if ls[0] == '-' else 1
        if ls[0] in ['-','+'] : del ls[0]
        ret, i = 0, 0
        while i < len(ls) and ls[i].isdigit() :
            ret = ret*10 + ord(ls[i]) - ord('0')
            i += 1
        return max(-2**31, min(sign * ret,2**31-1))



# Regex
class Solution:
    # @return an integer
    def atoi(self, str):
        str = str.strip()
        str = re.findall('(^[\+\-0]*\d+)\D*', str) # 开始以加号，减号 和的0开始的，后面接一个或多个digit
        #or   str = re.findall('^[+\-]?\d+', str)
        try:
            result = int(''.join(str))
            MAX_INT = 2147483647
            MIN_INT = -2147483648
            if result > MAX_INT > 0:
                return MAX_INT
            elif result < MIN_INT < 0:
                return MIN_INT
            else:
                return result
        except:
            return 0