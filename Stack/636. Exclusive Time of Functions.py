"""
636. Exclusive Time of Functions

Example 1:
Input:
n = 2
logs = 
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.
"""

class Solution:
    def exclusiveTime(self, n, logs):
        """
        :type n: int
        :type logs: List[str]
        :rtype: List[int]
        """
        prev = 0
        lastjobs, res = [], [0]*n  #lastjob 存的是上个job的id
        for j in logs:
            id, mode, time =  j.split(':')
            id, time = int(id), int(time)
            if mode == 'start':
                if lastjobs: res[lastjobs[-1]] += time - prev
                prev = time 
                lastjobs.append(id)
            else:
                res[id] += time - prev + 1
                prev = time + 1
                lastjobs.pop()
        return res


"""
下面是错误的解，不用用一个数表示上个job，这样可能在end 和 start中间，miss掉上一个还在运行的job
比如
3
["0:start:0","1:start:2", "1:end:5", "2:start:7","2:end:8", "0:end:12"]
正确解是
[7,4,2]
错误解是
[6,5,2]
"""
class Solution:
    def exclusiveTime(self, n, logs):
        """
        :type n: int
        :type logs: List[str]
        :rtype: List[int]
        """
        prev = 0
        lastjob, res = -1, [0]*n  #lastjob 存的是上个job的id
        for j in logs:
            id, mode, time =  j.split(':')
            id, time = int(id), int(time)
            if mode == 'start':
                if lastjob != '-1': res[lastjob] += time - prev
                prev = time 
                lastjob = id
            else:
                res[id] += time - prev + 1
                prev = time + 1
        return res



class Solution(object):
    def exclusiveTime(self, n, logs):
        ans = [0] * n
        stack = []
        for log in logs:
            uid, status, time = map(int, log.replace("start", "1").replace("end", "0").split(":"))
            if status:
                stack.append([time, 0])
            else:
                start, innerTime = stack.pop()
                ans[uid] += time - start + 1 - innerTime #innertime 是中间隔的时间
                if stack:
                    stack[-1][1] += time - start + 1 #中间别的任务隔开的时间
        return ans


