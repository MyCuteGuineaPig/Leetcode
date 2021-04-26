class Solution:
    def maxBuilding(self, n: int, r: List[List[int]]) -> int:
        r += [[1, 0], [n, n-1]]
        r.sort()
        res = 0
        for i in range(len(r) - 2, -1, -1):
            r[i][1] = min(r[i][1], r[i + 1][1] + r[i + 1][0] - r[i][0]) 
        for i in range(1, len(r)):
            r[i][1] = min(r[i][1], r[i - 1][1] + r[i][0] - r[i - 1][0]) 
            x = r[i][0] - r[i - 1][0] - abs(r[i][1] - r[i - 1][1]) 
            res = max(res, x // 2 + max(r[i][1], r[i - 1][1])) 
        return res


class Solution:
    def maxBuilding(self, n: int, arr: List[List[int]]) -> int:
        arr.extend([[1, 0], [n, n - 1]])
        arr.sort()
        m = len(arr)
        
        for i in range(1, m):
            arr[i][1] = min(arr[i][1], arr[i-1][1] + arr[i][0] - arr[i-1][0])
        for i in range(m - 2, -1, -1):
            arr[i][1] = min(arr[i][1], arr[i+1][1] + arr[i+1][0] - arr[i][0])
        
        ans = 0
        for i in range(1, m):
            l, h1 = arr[i-1]
            r, h2 = arr[i]
            ans = max(ans, max(h1, h2) + (r - l - abs(h1 - h2)) // 2)
        return ans
