class Solution:
    def findTheDistanceValue(self, arr1: List[int], arr2: List[int], d: int) -> int:
        arr2.sort()
        cnt = 0
        for i in arr1:
            if bisect.bisect_left(arr2,i-d) == bisect.bisect_right(arr2, i+d):
                cnt += 1
        return cnt


class Solution:
    def findTheDistanceValue(self, arr1: List[int], arr2: List[int], d: int) -> int:
        arr2.sort()
        cnt = 0
        for i in arr1:
            j = bisect.bisect_left(arr2,i)
            left = -10**4 if j == 0 else arr2[j-1]
            right = 10**4 if j == len(arr2) else arr2[j]
            cnt += 1 if left + d < i and right - d > i else 0 
        return cnt


class Solution:
    def findTheDistanceValue(self, arr1: List[int], arr2: List[int], d: int) -> int:
        arr2.sort()
        arr1.sort()
        cnt = 0
        i = j = 0
        while i < len(arr1) and j < len(arr2):
            if arr2[j] < arr1[i] - d:
                j += 1
            else:
                cnt += 1 if arr2[j] > arr1[i] + d else 0
                i+=1
        return cnt + len(arr1) - i

 class Solution:   
    def findTheDistanceValue(self, A, B, d):
        return sum(all(abs(a - b) > d for b in B) for a in A)