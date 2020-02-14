from heapq import heappush, heappop
class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        if not nums1 or not nums2:
            return []
        
        heap = [(nums1[0] + nums2[0], 0, 0)]
        seen = set((0, 0))

        
        result = []
        while heap and k > 0:
            _, i, j = heappop(heap)
            result.append([nums1[i], nums2[j]])
            k -= 1
            
            if i + 1 < len(nums1) and (i + 1, j) not in seen:
                heappush(heap, (nums1[i + 1] + nums2[j], i + 1, j))
                seen.add((i + 1, j))
        
            if j + 1 < len(nums2) and (i, j + 1) not in seen:
                heappush(heap, (nums1[i] + nums2[j + 1], i, j + 1))
                seen.add((i, j + 1))
                
        return result 
        
        
 
 # map + heap
 class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        if not k or not nums1 or not nums2: 
            return []
        i = 0; j = 0
        dic1, dic2 = collections.defaultdict(int), collections.defaultdict(int)
        for n1 in nums1:
            dic1[n1]+=1
        for n2 in nums2:
            dic2[n2]+=1
        res = []
        l1, l2 = sorted(dic1.items()), sorted(dic2.items())
        q = [[l1[0][0] + l2[0][0], 0, 0]]
        i, j = 0, 0
        visited = set([(0, 0)])
        while k>0 and q:
            top = heapq.heappop(q)
            _, i, j = top
            (d1, c1), (d2,c2) = l1[i], l2[j]
            res.extend([[d1,d2]]*min(c1*c2, k))
            k -= c1*c2 
            if k > 0: 
                if i < len(l1)-1 and (i+1, j) not in visited: 
                    heapq.heappush(q, [l1[i+1][0] + d2, i+1, j])
                    visited |= {(i+1, j)}
                if j<len(l2) - 1 and (i, j+1) not in visited:
                    heapq.heappush(q, [d1 + l2[j+1][0] , i, j+1])
                    visited |= {(i, j+1)}
        return res 
        
