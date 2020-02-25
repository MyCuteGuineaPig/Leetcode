#write by own
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        def generate(cur, target, index):
            if target == 0:
                yield cur
            if target > 0:
                for i in range(index, len(candidates)):
                     for p in generate(cur+[candidates[i]],target-candidates[i],i):
                            yield p
        return [*generate([],target,0)];



class Solution(object):
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        candidates.sort()
        res, cur = [], []
        self.backtracking(candidates,res,cur,target,0)
        return res
    
    def backtracking(self, candidates,res, cur, target, index):
        if target <0: return
        if target == 0: 
            res.append(cur) 
            return
        for i in range(index, len(candidates)):
            self.backtracking(candidates,res,cur+[candidates[i]],target-candidates[i],i)

            
 
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        res = []
        cur = []
        candidates.sort()
        def helper(j, target):
            if target >= 0 :
                if target == 0: 
                    res.append([i for i in cur])
                for i, v in enumerate(candidates[j:], j): 
                    cur.append(v)
                    helper(i, target-v)
                    cur.pop()
        helper(0, target)
        return res

class Solution:
    def combinationSum(self, candidates: List[int], target: int, isStart = True) -> List[List[int]]:
        if isStart:
            candidates.sort()
        return [[]] if target == 0 else [] if target < 0  else \
         [ [v] + r for i, v in enumerate(candidates) for r in self.combinationSum(candidates[i:], target - v, False) ] 


class Solution:
    def combinationSum(self, candidates: List[int], target: int, isStart = True) -> List[List[int]]:
        candidates.sort()
        def helper(i, t):
            if t >= 0:
                if t == 0:
                    yield [] #　yield 和 return 区别,    for i in yield的: 会loop 直接loop yield object, 而不是yield 内层object, 
                    #如果是return, 只肯可以 return [[]]， for i in return的: 会loop return 内层object, 
                for j, v in enumerate(candidates[i:],i):
                    for p in helper(j, t-v): # 
                        yield [v] + p
        return [*helper(0, target)] 
            


#yield 
def func(i):
    for i in range(n):
        yield i 

func(5): print 1 2 3 4 5




def func1():
    yield []

for i in func1():
    print(i) #print []


def func2():
    return [[]]


for i in func2():
    print(i) #print []




