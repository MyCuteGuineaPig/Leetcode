"""
315. Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array. 
The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0] 
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
"""

"""
MergeSort 
"""
class Solution:
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        self.nums = nums
        self.n = len(nums)
        self.smaller = [0,]*self.n
        self.indices = [i for i in range(self.n)]
        self.mergeSort(0,self.n-1)
        return self.smaller
    
    def mergeSort(self,start, end):
        #print(" in ",start,end)
        if start>= end: return
        mid = (start + end)>>1
        self.mergeSort(start,mid)
        self.mergeSort(mid+1, end)
        i, j = mid, end
        temp = []
        while i>=start or j>mid:
            #print(" in while i ",i," j ",j," start ",start, " mid ",mid,"end",end)
            if i<start or (j>mid and self.nums[self.indices[j]]>=self.nums[self.indices[i]]):
                temp.append(self.indices[j])
                j-=1
            else:
                
                temp.append(self.indices[i])
                self.smaller[self.indices[i]] += j-mid
                #print(" start ",start,"end",end,"mid",mid,"i",i,"j",j, " smaller", self.smaller)
                i-=1
        self.indices[start:end+1] = temp[::-1]
        #print(" end indices i "," start ",start, "end",end," self.indices ",self.indices)


class Solution:
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        def sort(arrs):
            mid = len(arrs) // 2
            if mid:
                left, right = sort(arrs[:mid]), sort(arrs[mid:])
                for i in range(len(arrs) - 1, -1, -1):
                    if not right or left and left[-1][1] > right[-1][1]:
                        res[left[-1][0]] += len(right)
                        arrs[i] = left.pop()
                    else:
                        arrs[i] = right.pop()
            return arrs
        
        res = [0] * len(nums)
        sort(list(enumerate(nums)))
        return res
                        
            


"""
O(n^2)
"""
class Solution:
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        s = sorted(nums)
        c = []
        for n in nums:
            p = bisect.bisect_left(s, n) #第一个数(n)在nums后面比它小的是s中所有比n小的
            c.append(p)
            s.pop(p)#把第一个数n pop 掉，这样第二数后面比它小的，是所有数比他小的
        return c



#BIT tree
class Solution:
    def countSmaller(self, nums):
        rank, N, res = {val: i + 1 for i, val in enumerate(sorted(nums))}, len(nums), []
        BITree = [0] * (N + 1)

        def update(i):
            while i <= N:
                BITree[i] += 1
                i += (i & -i)

        def getSum(i):
            s = 0
            while i:
                s += BITree[i]
                i -= (i & -i)
            return s

        for x in reversed(nums):
            res += getSum(rank[x] - 1),
            update(rank[x])
        return res[::-1]

"""
BIT解:
比如[5,2,6,1], 先sort然后存成dictionary, key是num, value是排第几个  {1: 1, 2: 2, 5: 3, 6: 4}
然后从后往前loop, 每到一个数先get sum,然后再update,

比如1，getsum = 0, rank[1]-1 = 0,没有比1更小的了，所以smaller[3] = 0
然后update,因为rank[1] =1, 更新1,2,4 position, BIT = [0,1,1,0,1]

下一个是6,6的rank是4, 4-1 = 3, getSum 当i=2是，有1，smaller[2] = 1
然后update, rank[6] = 4, 只更新第四个, BIT = [0,1,1,0,2]

下一个是2,2的rank是1,2-1 = 1, getSum 当i=1是，有1，smaller[1] = 1
然后update, rank[2] = 2, 更新第2个，第四个, BIT = [0, 1, 2, 0, 3]

下一个是5,5的rank是3,3-1 = 2, getSum 当i=2是，有2，smaller[0] = 2
然后update, rank[5] = 3, 更新第3个，第2个, BIT = [0, 1, 2, 1, 4]

class Solution:
    def countSmaller(self, nums):
        rank, N, res = {val: i + 1 for i, val in enumerate(sorted(nums))}, len(nums), []
        BITree = [0] * (N + 1)

        def update(i):
            print(" update i ", i)
            while i <= N:
                BITree[i] += 1
                print(i, " BIT ", BITree)
                i += (i & -i)

        def getSum(i):
            s = 0
            print(" get sum i ", i)
            while i:
                s += BITree[i]
                print(" sum i ", i, " s ",s)
                i -= (i & -i)
            return s

        print(" rank ",rank)
        for x in reversed(nums):
            print(" cur num ", x)
            res += getSum(rank[x] - 1),
            update(rank[x])
        return res[::-1]

"""


            
        

from collections import deque
class Solution:
    def countSmaller(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        if not nums:
            return []
        maxx = max(nums)
        maii = min(nums)
        a = BIT(maxx - maii + 1)
        res = deque()
        for i in nums[::-1]:
            a.update(1, i - maii + 1)
            smaller = a.read(i - maii)
            res.appendleft(smaller)
        return list(res)


class BIT:
    def __init__(self, n):
        #virtual nodes
        self._nodes = [0] *(n+1)
        self._length = n
    
    def update(self, value, position):
        while position <= self._length:
            self._nodes[position] += value
            position += position & -position
    
    def read(self, position):
        if position == 0 :
            return 0
        res = 0
        while position > 0:
            res += self._nodes[position]
            position -= position & -position
        return res






