"""
275. H-Index II

Input: citations = [0,1,3,5,6]
Output: 3 
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had 
             received 0, 1, 3, 5, 6 citations respectively. 
             Since the researcher has 3 papers with at least 3 citations each and the remaining 
             two with no more than 3 citations each, his h-index is 3.  
"""
class Solution:
    def hIndex(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        l , r, n = 0, len(citations)-1,len(citations)
        while l<=r:
            mid = (l+r)>>1
            if citations[mid]>=n-mid:
                r = mid-1
            else l = mid+1

        return n-l    
        