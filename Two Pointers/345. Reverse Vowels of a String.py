"""
345. Reverse Vowels of a String

"""
class Solution(object):
    def reverseVowels(self, s):
        """
        :type s: str
        :rtype: str
        """
        v="AEIOUaeiou"
        i = 0
        j = len(s)-1
        li = list(s)
        while i<j:
            while i<j and li[i] not in v: i+=1
            while i<j and li[j] not in v: j-=1
            if i<j:
                li[i], li[j] = li[j], li[i]
            i+=1; j-=1
        
        return "".join(li)


class Solution(object):
    def reverseVowels(self, s):
        vowels = re.findall('(?i)[aeiou]', s)
        return re.sub('(?i)[aeiou]', lambda m: vowels.pop(), s)