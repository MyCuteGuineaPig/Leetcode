"""
443. String Compression


Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.


"""


class Solution:
    def compress(self, chars):
        """
        :type chars: List[str]
        :rtype: int
        """
        if not chars: return chars
        j = rcd = 0
        cnt = 1
        for i, v in enumerate(chars[1:]):
            if v != chars[j]:
                chars[rcd] = chars[j]
                rcd += 1
                start = rcd
                if cnt >1:
                    while cnt: 
                        chars[rcd], cnt = str(cnt % 10), cnt//10 
                        rcd+=1
                    chars[start: rcd] = chars[start:rcd][::-1]
                j = i+1
                cnt = 1
            else:
                cnt+=1
        chars[rcd] = chars[j]
        rcd += 1
        start = rcd
        if cnt >1:
            while cnt: 
                chars[rcd], cnt = str(cnt % 10), cnt//10 
                rcd+=1
            chars[start: rcd] = chars[start:rcd][::-1]          
    
        return rcd


class Solution:
    def compress(self, chars):
        n = 0
        curr = chars[0]
        count = 0
        for i in range(len(chars)):
            if chars[i] != curr:
                chars[n] = curr
                n += 1
                if count > 1:
                    for digit in str(count):
                        chars[n] = digit
                        n += 1
                curr = chars[i]
                count = 1
            else:
                count += 1
                
        chars[n] = curr
        n += 1
        if count > 1:
            for digit in str(count):
                chars[n] = digit
                n += 1
        return n

class Solution:
    def compress(self, chars):
        """
        :type chars: List[str]
        :rtype: int
        """
        write, anchor = 0, 0
        for read, c in enumerate(chars):
            if read == len(chars) - 1 or c != chars[read + 1]:
                chars[write] = chars[anchor]
                write += 1
                if read > anchor:
                    for d in str(read - anchor + 1):
                        chars[write] = d
                        write += 1
                anchor = read + 1
        return write
            

class Solution(object):
    def compress(self, c):
        flips = [(c[0], 0)] + [(c[i], i) for i in range(1, len(c)) if c[i] != c[i - 1]] + [(None, len(c))]
        chunks = [(b[0], a[1] - b[1]) for (a, b) in zip(flips[1:], flips)]
        compressed = reduce(lambda a, b: (a + [b[0]] + (list(str(b[1])) if (b[1] > 1) else [])), chunks, [])
        c[:len(compressed)] = compressed
        return len(compressed)