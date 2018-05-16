"""
658. Find K Closest Elements

Example 1:
Input: [1,2,3,4,5], k=4, x=3
Output: [1,2,3,4]
Example 2:
Input: [1,2,3,4,5], k=4, x=-1
Output: [1,2,3,4]

"""
class Solution:
    def findClosestElements(self, arr, k, x):
        """
        :type arr: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        i = bisect.bisect_left(arr,x)
        j = i
        while k>0:
            k-=1
            if j>=len(arr) or (i>=1 and x-arr[i-1]<=arr[j]-x): i-=1
            else: j+=1
        return arr[i:j]

class Solution:
    def findClosestElements(self, arr, k, x):
        """
        :type arr: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        low, high = 0, len(arr) - k
        while low < high:
            mid = (low + high) // 2
            #print("x - arr[mid] - ", x - arr[mid], ",arr[mid+k] - x - ", arr[mid+k] - x, ",x - ", x, ",arr[mid]", arr[mid], ",arr[mid+k]", arr[mid+k])
            if x - arr[mid] > arr[mid+k] - x:
                low = mid + 1
            else:
                high = mid
        return arr[low : low+k]
            
