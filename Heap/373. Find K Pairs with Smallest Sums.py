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
    
    
    
 class Solution:        
    def kSmallestPairs(self, nums1, nums2, k):
        queue = []
        def push(i, j):
            if i < len(nums1) and j < len(nums2):
                heapq.heappush(queue, [nums1[i] + nums2[j], i, j])
        push(0, 0)
        pairs = []
        while queue and len(pairs) < k:
            _, i, j = heapq.heappop(queue)
            pairs.append([nums1[i], nums2[j]])
            push(i, j + 1)
            if j == 0:
                push(i + 1, 0)
        return pairs
    
    
#Brute Force  O(k) extra memory and O(mn log k) time.
class Solution: 
    def kSmallestPairs(self, nums1, nums2, k):
        return map(list, sorted(itertools.product(nums1, nums2), key=sum)[:k])

 #Brute Force       
 class Solution: 
    def kSmallestPairs(self, nums1, nums2, k):
        return map(list, heapq.nsmallest(k, itertools.product(nums1, nums2), key=sum))

#or 
class Solution: 
    def kSmallestPairs(self, nums1, nums2, k):
        return heapq.nsmallest(k, ([u, v] for u in nums1 for v in nums2), key=sum)
    
class Solution: 
    def kSmallestPairs(self, nums1, nums2, k):
        streams = map(lambda u: ([u+v, u, v] for v in nums2), nums1)
        stream = heapq.merge(*streams)
        return [suv[1:] for suv in itertools.islice(stream, k)]
