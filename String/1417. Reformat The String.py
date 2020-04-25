class Solution:
    def reformat(self, s: str) -> str:
        str_list = []
        digit_list = []
        for  i in s:
          if i.isdigit():
            digit_list += i, 
          elif i.isalpha():
            str_list +=  i,
        
        if abs( len(str_list) - len(digit_list)) > 1:
            return ""

        res = "" 
        if len(str_list) < len(digit_list):
            str_list, digit_list = digit_list, str_list #str_list always bigger than digit_list


        for i, j in zip(str_list,digit_list):
            res += i + j
        return res + ("" if len(str_list) == len(digit_list) else str_list[-1])


class Solution(object):
    def reformat(self, s):
        """
        :type s: str
        :rtype: str
        """
        def char_gen(start, end, count):
            for c in range(ord(start), ord(end)+1):
                c = chr(c)
                for i in range(count[c]):
                    yield c
            yield ''
    
        count = collections.defaultdict(int)
        alpha_cnt = 0
        for c in s:
            count[c] += 1
            if c.isalpha():
                alpha_cnt += 1
        if abs(len(s)-2*alpha_cnt) > 1:
            return ""

        result = []
        it1, it2 = char_gen('a', 'z', count), char_gen('0', '9', count)
        if alpha_cnt < len(s)-alpha_cnt:
            it1, it2 = it2, it1
        while len(result) < len(s):
            result.append(next(it1))
            result.append(next(it2))
        return "".join(result)

class Solution:
    def reformat(self, s: str) -> str:
            a, b = [], []
        for c in s:
            if 'a' <= c <= 'z':
                a.append(c)
            else:
                b.append(c)
        if len(a) < len(b):
            a, b = b, a
        if len(a) - len(b) >= 2:
            return ''
        ans = ''
        for i in range(len(a)+len(b)):
            if i % 2 == 0:
                ans += a[i//2]
            else:
                ans += b[i//2]
        return ans