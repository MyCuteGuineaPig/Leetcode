"""
826. Most Profit Assigning Work

Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100 
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.

"""
class Solution:
    def maxProfitAssignment(self, difficulty, profit, worker):
        """
        :type difficulty: List[int]
        :type profit: List[int]
        :type worker: List[int]
        :rtype: int
        """
        jobs = list(zip(difficulty,profit))
        jobs.sort()
        worker.sort()
        res, profit, j, n = 0, 0, 0, len(jobs)
        for i in worker:
            while j<n and jobs[j][0]<=i:
                profit = max(profit,jobs[j][1])
                j+=1        
            res += profit
        return res



class Solution:
    def maxProfitAssignment(self, difficulty, profit, worker):
        jobs = [0,]*100001
        n,res = len(difficulty), 0
        for i in range(n): jobs[difficulty[i]] = max(jobs[difficulty[i]],profit[i]) #可能一个job 两个profit取高的
        for i in range(1,100001): jobs[i] = max(jobs[i], jobs[i-1])
        for i in worker:
            res += jobs[i]
        return res


