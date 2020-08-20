
class Solution:
    def candy(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """
        n = len(ratings)
        res = [1]*len(ratings)
        for i in range(n-1):
            if ratings[i+1] > ratings[i]:
                res[i+1] = res[i] + 1
        for i in reversed(range(n-1)):
            if ratings[i] > ratings[i+1]:
                res[i] = max(res[i], res[i+1] + 1)
        return sum(res) 
