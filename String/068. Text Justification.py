import functools
class Solution:
    def fullJustify(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        out = []
        i  = 0
        while i < len(words):
            cur = len(words[i])
            start = i
            i+=1
            while i < len(words) and cur + len(words[i]) + 1 <= maxWidth:
                cur = cur + len(words[i]) + 1
                i+=1
            if i-start > 1 and i!=len(words):
                space, extra = (maxWidth - cur)//(i-start-1),    (maxWidth - cur)%(i-start-1)
            else:
                space, extra = 0, 0
            string = functools.reduce(lambda x, y: x + y[1]+(" "*(space+1) if y[0]!=i-start-1 else "") + (" " if y[0]<extra else ""), enumerate(words[start: i]), "")
            string += " "*(maxWidth-len(string))
            
            out.append(string)
        return out


class Solution:
    def fullJustify(self, words, maxWidth):
        out = []
        i  = 0
        while i < len(words):
            cur = len(words[i])
            start = i
            i+=1
            while i < len(words) and cur + len(words[i]) + 1 <= maxWidth:
                cur = cur + len(words[i]) + 1
                i+=1
            if i-start > 1 and i!=len(words):
                space, extra = (maxWidth - cur)//(i-start-1),    (maxWidth - cur)%(i-start-1)
            else:
                space, extra = 0, 0
            string = ""
            for j in range(start, i):
                string += words[ j]
                if j != i-1: 
                    string += " "*(space+1)
                if  j - start < extra:
                    string += " "
            string += " "*(maxWidth-len(string))
            
            out.append(string)
        return out


class Solution:
    def fullJustify(self, words, maxWidth):
        res, cur, num_of_letters = [], [], 0
        for w in words:
            if num_of_letters + len(w) + len(cur) > maxWidth:
                for i in range(maxWidth - num_of_letters):
                    cur[i%(len(cur)-1 or 1)] += ' '
                res.append(''.join(cur))
                cur, num_of_letters = [], 0
            cur += [w]
            num_of_letters += len(w)
        return res + [' '.join(cur).ljust(maxWidth)]