"""
401. Binary Watch

"""
class Solution:
    def readBinaryWatch(self, num):
        """
        :type num: int
        :rtype: List[str]
        """
        res = []
        for i in range(12):
            for j in range(60):
                if bin(i).count('1') + bin(j).count('1') == num:
                    res.append(str(i)+':'+('0'+str(j) if j<10 else str(j)))
        return res 

class Solution:
    def readBinaryWatch2(self, num):
        """
        :type num: int
        :rtype: List[str]
        """
        return ['{0}:{1}'.format(str(h), str(m).zfill(2))
                for h in range(12) for m in range(60)
                if (bin(h) + bin(m)).count('1') == num]