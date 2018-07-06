"""
388. Longest Absolute File Path

"""

class Solution:
    def lengthLongestPath(self, input):
        """
        :type input: str
        :rtype: int
        """
        input = input.split('\n')
        dic = collections.defaultdict(int)
        res = 0
        for i in input: 
            content = i.lstrip("\t") #"dir\n    file.txt",  "    file.txt"不处去这个空格，"    file.txt"还算第0层的
            level = len(i)-len(content)
            if '.' in content:
                res = max(res, dic[level] + len(content))
            else:
                dic[level+1] =  dic[level] +len(content)+1
        return res

class Solution(object):
    def lengthLongestPath(self, input):
        path, maxLen = [], 0
        for s in input.split('\n'):
            path[s.count('\t'):] = [len(s.strip('\t'))]
            maxLen = max(maxLen, sum(path)+len(path)-1 if '.' in s else 0)
        return maxLen