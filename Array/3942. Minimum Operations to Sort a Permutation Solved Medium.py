class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0
        ind_zero = nums.index(0)

        is_rotated = True 
        for i in range(n):
            if nums[(ind_zero + i) % n] != i:
                is_rotated = False 
                break

        if is_rotated: 
            # Strategy A: Just rotate left until 0 is at the front
            cost1 = ind_zero
        
            # Strategy B: Reverse it, then rotate, then reverse again
            # For [1, 2, 3, 4, 0], idx_zero is 4.
            # Reverse (1) -> [0, 4, 3, 2, 1]. Shift left 1 (1) -> [4, 3, 2, 1, 0]. Reverse (1) -> sorted.
            # Total cost: 1 + (n - idx_zero) + 1
            
            cost2 = 1 + (n - ind_zero) + 1  if ind_zero != 0 else float('inf')
            # 0要到 n-1的位置
            return min(cost1, cost2)

        is_rotated = True 
        for i in range(n):
            if nums[(ind_zero - i + n) % n] != i:
                is_rotated = False 
                break

        if is_rotated:
            # Strategy C: Rotate left until it matches the pure reversed state [n-1, ..., 0], then reverse once.
            # Pure reversed state has 0 at index n-1.  比如[3,2,1,0,4] -> [4,3,2,1,0] 需要rotate 4次
            # Distance to shift left to get 0 to index n-1:
            # 先 rotate 再reverse 

            shift_to_end = (ind_zero + 1 ) % n #n次rotate left后0
             # 0要到 n-1的位置 再 shift_to_end 之后
            cost1 = shift_to_end + 1 # reverse

            # Strategy D: Reverse it first, which turns it into a sorted config, then rotate left.
            # After a reverse, the new index of 0 is (n - 1 - idx_zero)
            # 先rotate 再rotate

            cost2 = 1 + (n-1 - ind_zero) #(n-1 - ind_zero) 0距离n-1的距离,表示reverse后需要rotate 的次数
            # For example, for [3, 2, 1, 0, 4], idx_zero is 3.  fter reverse, we get [4, 0, 1, 2, 3]. 
            # The new index of 0 is (n - 1 - idx_zero) = (5 - 1 - 3) = 1.
            #  We need to rotate left once to get [0, 1, 2, 3, 4]. Total cost: reverse (1) + rotate (1) = 2.
            return min(cost1, cost2)
    
        return -1
        