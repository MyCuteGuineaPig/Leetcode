"""
831. Masking Personal Information

Example 1:

Input: "LeetCode@LeetCode.com"
Output: "l*****e@leetcode.com"
Explanation: All names are converted to lowercase, and the letters between the
             first and last letter of the first name is replaced by 5 asterisks.
             Therefore, "leetcode" -> "l*****e".
Example 2:

Input: "AB@qq.com"
Output: "a*****b@qq.com"
Explanation: There must be 5 asterisks between the first and last letter 
             of the first name "ab". Therefore, "ab" -> "a*****b".
Example 3:

Input: "1(234)567-890"
Output: "***-***-7890"
Explanation: 10 digits in the phone number, which means all digits make up the local number.
Example 4:

Input: "86-(10)12345678"
Output: "+**-***-***-5678"
Explanation: 12 digits, 2 digits for country code and 10 digits for local number. 

"""

class Solution:
    def maskPII(self, S):
        """
        :type S: str
        :rtype: str
        """
        if "@" in S:
            f, l = S[0].lower(), S[S.find("@")-1].lower()
            return f+"*****"+l+S[S.find("@"):].lower()
        else:
            prefix, last = -10, ""
            for i, v in enumerate(reversed(S)):
                if v.isdigit():
                    if len(last)<4:
                        last = v+last
                    prefix +=1 
            if not prefix:
                return "***-***-"+last
            else:
                return "+"+"*"*prefix + "-***-***-"+last

class Solution:
    def maskPII(self, S):
        """
        :type S: str
        :rtype: str
        """
        at = S.find('@')
        if at >= 0:
            return (S[0] + "*" * 5 + S[at - 1:]).lower()
        S = "".join(i for i in S if i.isdigit())
        return ["", "+*-", "+**-", "+***-"][len(S) - 10] + "***-***-" + S[-4:]


class Solution:
    def maskPII(self, S):
        """
        :type S: str
        :rtype: str
        """
        if '@' in S:
            left,right = S.lower().split('@')
            return left[0]+'*****'+left[-1]+'@'+right
        # \D:匹配任何非数字，*：表示匹配前面出现的正则表达式零次或多次
        digits = re.sub('\D*', '', S)
        countryCode = ''
        if len(digits) > 10:
            countryCode = '+' + '*' * (len(digits) - 10) + '-'
        return countryCode + '***-***-' + digits[-4:]