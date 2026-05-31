class Solution:
    def maximumMEX(self, nums: List[int]) -> List[int]:
        cnt = Counter(nums)

        res = []
        i = 0
        n = len(nums)

        max_possible = 0
        while i < n: 
            while cnt[max_possible] > 0:
                max_possible += 1 

            if max_possible == 0:
                res.append(0)
                cnt[nums[i]] -= 1 
                i += 1 
                continue 

            seen = set() 
            while i < n and len(seen) < max_possible:
                if nums[i] < max_possible:
                    seen.add(nums[i])
                cnt[nums[i]] -= 1 
                i += 1 

            res.append(max_possible)
            max_possible = 0

        return res