"""

151. Reverse Words in a String

"""

class Solution:
    # @param s, a string
    # @return a string
    def reverseWords(self, s):
        return " ".join(s.strip().split()[::-1])

class Solution(object):
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        trim_string = s.strip()
        words = trim_string.split(" ")
        new_words = ""
        for i in range(len(words)-1, -1, -1):
            word = words[i].strip()
            if not word == "":
                new_words = new_words +" "+ word
        return new_words.strip()