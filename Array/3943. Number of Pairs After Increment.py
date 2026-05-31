class Solution:
    def numberOfPairs(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        n1_cnt = Counter(nums1)
        n = len(nums2)

        block_size = int(math.ceil(n**0.5))
        num_blocks = int(math.ceil(n / block_size))

        blocks_freq = [Counter() for _  in range(num_blocks)]

        lazy = [0]* num_blocks

        for i, val in enumerate(nums2):
            b_idx = i // block_size
            blocks_freq[b_idx][val] += 1

        res = []

        for query in queries:

            if query[0] == 1: 
                _, x, y, val = query
                start_block = x // block_size 
                end_block = y // block_size 

                if start_block == end_block: 
                    b = start_block
                    for i in range(x, y + 1):
                        blocks_freq[b][nums2[i]] -= 1 
                        nums2[i] += val 
                        blocks_freq[b][nums2[i]] += 1 

                else: 
                    b = start_block 
                    for i in range(x, (start_block + 1) * block_size):
                        blocks_freq[b][nums2[i]] -= 1 
                        nums2[i] += val 
                        blocks_freq[b][nums2[i]] += 1 

                    for b in range(start_block + 1, end_block):
                        lazy[b] += val


                    b = end_block 
                    for i in range(end_block * block_size , y + 1):
                        blocks_freq[b][nums2[i]] -= 1 
                        nums2[i] += val 
                        blocks_freq[b][nums2[i]] += 1 
                print(nums2, blocks_freq, lazy)
            else: 
                _, tot = query 
                total = 0 
                for v1, count1 in n1_cnt.items():
                    target = tot - v1 

                    for b in range(num_blocks):
                        needed_in_block = target - lazy[b]
                        if needed_in_block in blocks_freq[b]:
                            total += blocks_freq[b][needed_in_block] * count1 

                res.append(total)

                """
                
                This is where the lazy tag comes into play.
                
                Imagine Block 0 contains the numbers [10, 20, 30].
                
                If a previous Type 1 query told us to add 5 to this entire block, 
                we don't actually change 10, 20, 30 inside our frequency map (that would take too long). 
                Instead, we leave the map alone and set lazy[0] = 5.
                
                So, inside our frequency map, the numbers still look like 10, 20, 30. 
                But in reality, their actual values are 15, 25, 35.
                
                The Math: needed_in_block = target - lazy[b]
                
                If our target is 25, we look at Block 0. 
                We know that everything inside Block 0 has secretly been boosted by lazy[b] (which is 5)
                .So, what number are we actually looking for inside the un-updated frequency map 
                needed_in_block = 25 - 5 = 20. 

                $We check if 20 exists in our stored frequency map for that block. 
                If it does, it means its real, boosted value is 25!
                
                """

        return res
    