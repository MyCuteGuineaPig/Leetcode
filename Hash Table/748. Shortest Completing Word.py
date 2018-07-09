"""
748. Shortest Completing Word

Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
Note that the answer is not "step", because the letter "s" must occur in the word twice.
Also note that we ignored case for the purposes of comparing whether a letter exists in the word.
Example 2:
Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
Output: "pest"
Explanation: There are 3 smallest length words that contains the letters "s".
We return the one that occurred first.
"""

class Solution:
    def shortestCompletingWord(self, licensePlate, words):
        """
        :type licensePlate: str
        :type words: List[str]
        :rtype: str
        """
        plate = collections.defaultdict(int)
        for i in licensePlate:
            if i.isalpha():
                plate[i.lower()]+=1
        res = ""
        for i in words:
            if res!= "" and len(res) <= len(i): continue
            cur = collections.Counter(i)
            match = True
            for k, v in plate.items():
                if cur[k] < v:
                    match = False
                    break
            if match: res = i
        return res


class Solution:
    def shortestCompletingWord(self, licensePlate, words):
        """
        :type licensePlate: str
        :type words: List[str]
        :rtype: str
        """
        plate = collections.defaultdict(int)
        for i in licensePlate:
            if i.isalpha():
                plate[i.lower()]+=1
        res = ""
        for i in words:
            if res!= "" and len(res) <= len(i): continue
            cur = collections.Counter(i)
            cur.subtract(plate)
            match = True
            for v in cur.values():
                if v < 0:
                    match = False
                    break
            if match: res = i
        return res

class Solution:
    def shortestCompletingWord(self, lp, words):
        cntr_lp, res = {k: v for k, v in collections.Counter(lp.lower()).items() if k.isalpha()}, [None, None]
        for word in words:
            check = collections.Counter(word.lower())
            if all(True if k in check and v <= check[k] else False for k, v in cntr_lp.items()):
                if not any(res) or len(word) < res[1]: res = [word, len(word)]
        return res[0] 

class Solution:
    def shortestCompletingWord(self, licensePlate, words):
        d = Counter(i.lower() for i in licensePlate if i.isalpha())
        res = None
        for word in words:
            if (not res or len(word) < len(res)) and not d - Counter(word.lower()): #d - Counter(word.lower()):， 把d中有的，减去word中有的，word中的d没有的，不会出现，也不会出现为负
                res = word
        return res