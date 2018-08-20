"""
15. 3Sum

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

"""

class Solution:
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        nums.sort()
        res = []
        for ind, val in enumerate(nums):
            if val > 0: break
            if ind > 0 and nums[ind-1] == val:
                continue
            i, j = ind + 1, len(nums)-1
            while i < j: 
                if nums[i] + nums[j] + val == 0: 
                    res.append([val, nums[i], nums[j]])
                    while i+1 < j and nums[i] == nums[i+1]: i+=1
                    while i < j-1 and nums[j] == nums[j-1]: j-=1
                    i+=1 
                    j-=1
                elif  nums[i] + nums[j] + val < 0: i+=1
                else: j-=1
        return res


class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        if len(nums) < 3:
            return []
        nums.sort()
        res = set()
        for i, v in enumerate(nums[:-2]):
            if i >= 1 and v == nums[i-1]:
                continue
            d = {}
            for x in nums[i+1:]:
                if x not in d:
                    d[-v-x] = 1
                else:
                    res.add((v, -v-x, x))
        return map(list, res)


from collections import defaultdict
class Solution(object):
    def threeSum(self, nums):
        result=[]
        zero=0
        pos=defaultdict(int)
        neg=defaultdict(int)
        for i in (nums):
            if i==0:
                zero+=1
            elif i>0:
                pos[i]+=1
            else:
                neg[i]+=1
        if zero>2:
            result.extend([[0,0,0]])
        if zero:
            result.extend([[p,0,-p] for p in pos if -p in neg])
        
        
        result.extend([[p,p,-2*p]for p in pos if pos[p]>1 and -2*p in neg])
        
        result.extend([[n,n,-2*n]for n in neg if neg[n]>1 and -2*n in pos])
        
        result.extend([[p1,p2,-p1-p2]for p1 in pos for p2 in pos if -p1-p2 in neg and p1<p2])
        result.extend([[n1,n2,-n1-n2]for n1 in neg for n2 in neg if -n1-n2 in pos and n1>n2])
        
        return result


class Solution:
    """
    1. count the input array
    2. get positive part and negative part(including 0)  
    3. use k > i and k < j condition to avoid duplication
    """
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        from collections import Counter
        count = Counter(nums)
        ans = []
        pos = [num for num in count if num > 0]
        neg = [num for num in count if num <= 0]
        if count[0] >= 3:
            ans.append([0, 0, 0])
        for i in pos:
            for j in neg:
                k = -(i + j)
                if k in count:
                    if k in (i, j) and count[k] > 1:
                        ans.append([i, j, k])
                    elif k > i:
                        ans.append([i, j, k])
                    elif k < j:
                        ans.append([i, j, k])
        return ans
        