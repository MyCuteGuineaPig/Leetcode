class Solution:
    def getMinSwaps(self, num: str, k: int) -> int:
        org = [i for i in num]
        num = [i for i in num]
        def nxtPermuate(nums):
            k, l = -1, 0
            for i in reversed(range(len(nums)-1)):
                if nums[i] < nums[i+1]: # 5 6 3 1 的 5
                    k = i
                    break

            for i in reversed(range(k+1, len(nums))):
                if nums[i] > nums[k]: # 后面第一个大于nums[k]的点 5 6 3 1 的 6
                    l = i
                    break
            nums[k], nums[l] = nums[l], nums[k]
            nums[k+1:] = nums[:k:-1] # reverse nums[k+1:]
            
        for i in range(k):
            nxtPermuate(num)
        
        res = 0
        for i in range(len(num)):
            if num[i] != org[i]:
                j = i + 1 
                while j < len(num) and num[j] != org[i]:
                    j += 1
                while j > i:
                    num[j-1], num[j] =  num[j],  num[j-1]
                    j -= 1
                    res += 1
        return res



class Solution:
    def getMinSwaps(self, num: str, k: int) -> int:
        def nxt_perm(num: list) -> list:
            i = n - 1
            while i > 0 and num[i-1] >= num[i]:
                i -= 1
            j = i
            while j < n and num[i-1] < num[j]:
                j += 1
            num[i-1], num[j-1] = num[j-1], num[i-1]
            num[i:] = num[i:][::-1] # credit to @ye15, reduce time from nlogn to n
            return num

        n = len(num)
        nxt_k_num = list(num)
        for _ in range(k):
            nxt_k_num = nxt_perm(nxt_k_num)

        ans = 0
        num = list(num)
        for i in range(n):
            j = i
            while j < n and nxt_k_num[i] != num[j]:
                j += 1
            ans += j - i
            num[i:j+1] = [num[j]] + num[i:j]
        return ans