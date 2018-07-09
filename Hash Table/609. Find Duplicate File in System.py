"""
609. Find Duplicate File in System

Example 1:
Input:
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
Output:  
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
"""

class Solution:
    def findDuplicate(self, paths):
        """
        :type paths: List[str]
        :rtype: List[List[str]]
        """
        dic = collections.defaultdict(list)
        for path in paths:
            text = path.split(" ")
            root = text[0]
            for i in text[1:]:
                pos = i.find('(')
                content = i[pos:]
                dic[content].append(root+"/"+i[:pos])
        return [j for j in dic.values() if len(j)>1 ]