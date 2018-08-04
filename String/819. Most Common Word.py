"""
819. Most Common Word

"""

class Solution:
    def mostCommonWord(self, paragraph, banned):
        """
        :type paragraph: str
        :type banned: List[str]
        :rtype: str
        """
        paragraph = paragraph.replace("!","").replace("?","").replace("'","").replace(",","").replace(";","").replace(".","")
        for i,v in collections.Counter(paragraph.lower().split()).most_common():
            if i not in banned:
                return i


class Solution(object):
    def mostCommonWord(self, paragraph, banned):
        lookup = set(banned)
        counts = collections.Counter(word.strip("!?',;.")
                                     for word in paragraph.lower().split())

        result = ''
        for word in counts:
            if (not result or counts[word] > counts[result]) and \
               word not in lookup:
                result = word
        return result

class Solution:
    def mostCommonWord(self, paragraph, banned):
        """
        :type paragraph: str
        :type banned: List[str]
        :rtype: str
        """
        m = {}
        words = paragraph.split()
        for w in words:
            w = w.lower()
            if not w.isalpha():
                w = w[0:-1]
            if w not in m:
                m[w] = 1
            else:
                m[w] = m[w] + 1
        maxm = 0
        for w in m:
            if w not in banned:
                if m[w] > maxm:
                    maxm = m[w]
                    ans = w
        return ans


class Solution:
    def mostCommonWord(self, p, banned):
        ban = set(banned)
        words = re.findall(r'\w+', p.lower())
        return collections.Counter(w for w in words if w not in ban).most_common(1)[0][0]


class Solution:
    def mostCommonWord(self, paragraph, banned):
        return collections.Counter(i.lower() for i in re.split("\W+", paragraph) if i and i.lower() not in banned).most_common(1)[0][0]