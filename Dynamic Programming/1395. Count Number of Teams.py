class Solution:
    def numTeams(self, rating: List[int]) -> int:
        after = collections.Counter(rating)
        before = collections.defaultdict(int)
        res =  0
        for i in rating:
            after_large, after_small = 0, 0
            before_large, before_small = 0, 0
            for k, v in after.items():
                if k > i:
                    after_large += 1 
                if k < i:
                    after_small += 1 
            for k, v in before.items():
                if k > i:
                    before_large += 1 
                if k < i:
                    before_small += 1
            before[i] += 1
            after[i]-=1 
            if after[i] == 0: del after[i]
            res += after_large * before_small + after_small * before_large
        return int(res)


class Solution:
    def numTeams(self, rating: List[int]) -> int:
        result = 0
        for i in range(1, len(rating)-1):
            less, greater = [0]*2, [0]*2
            for j in range(len(rating)):
                if rating[i] > rating[j]:
                    less[i < j] += 1
                if rating[i] < rating[j]:
                    greater[i < j] += 1
            result += less[0]*greater[1] + greater[0]*less[1]
        return result


from collections import defaultdict

class Solution:
    def numTeams(self, rating: List[int]) -> int:
        if len(rating) < 3:
            return 0
        
        greater = defaultdict(int)
        less = defaultdict(int)
        res = 0
        
		# greater[i] is the number of elements after index i greater than ratings[i]
        # less[i] : 在 index i 后几个数小于 rating[i]
        for i in range(len(rating)-1):
            for j in range(i+1, len(rating)):
                if rating[j] > rating[i]:
                    greater[i] += 1
                else:
                    less[i] += 1
        
		# Accumulate counts
        for i in range(len(rating)-2):
            for j in range(i+1, len(rating)):
                if rating[i] < rating[j]:
                    res += greater[j] # rating[i]  < rating[j] 还需要一个大于rating[j]的数 组合
                else:
                    res += less[j] # rating[i] > rating [j] 还需要一个小于rating[j]的数 组合
        
        return res