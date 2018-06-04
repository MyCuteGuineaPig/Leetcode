"""
406. Queue Reconstruction by Height

Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

"""
class Solution:
    def reconstructQueue(self, people):
        """
        :type people: List[List[int]]
        :rtype: List[List[int]]
        """
        people.sort(key = lambda k: (-k[0],k[1]))
        li = []
        for i in people:
            li.insert(i[1],i)
        return li


class Solution:
    def reconstructQueue(self, people):
        """
        :type people: List[List[int]]
        :rtype: List[List[int]]
        """
        people.sort(key = lambda k: (-k[0],k[1]))
        block = [[]]
        for p in people:
            index = p[1]
            for j in range(len(block)):
                if index <= len(block[j]):
                    break
                index -= len(block[j])
            block[j].insert(index, p)
            m = len(block[j])
            if m**2 > len(people):
                block.insert(j+1, block[j][m//2:])
                del block[j][m//2:]
        return  [p for b in block for p in b]