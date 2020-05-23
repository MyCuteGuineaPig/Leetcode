class Solution:
    def intervalIntersection(self, A: List[List[int]], B: List[List[int]]) -> List[List[int]]:
        res = []
        i = j = 0
        while i < len(A) and j < len(B):
            start, end = max(A[i][0], B[j][0]), min(A[i][1], B[j][1])
            if start <= end:
                res += [start,end],
            
            if A[i][1] < B[j][1]: i+=1 
            else:  j+=1
        return res