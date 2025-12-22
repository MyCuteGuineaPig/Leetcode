class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        dic = collections.defaultdict(int)
        cnt = 0
        max_single = 0
        for i, (num, f) in enumerate(zip(nums, forbidden)):
            if num == f: 
                dic[num] += 1 
                cnt += 1 
                max_single = max(max_single, dic[num])
        
        num_dic = Counter(nums)
        f_dic = Counter(forbidden)
        n = len(nums)
        for num in dic:
            if num_dic[num] > n - f_dic[num]:
                return -1 

        return max((cnt + 1)//2, max_single)