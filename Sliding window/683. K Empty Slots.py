class Solution:
    def kEmptySlots(self, bulbs: List[int], k: int) -> int:
        days = [0] * len(bulbs)
        for day, position in enumerate(bulbs, 1):
            days[position - 1] = day

        ans = float('inf')
        left, right = 0, k+1
        while right < len(days):
            for i in range(left + 1, right):
                if days[i] < days[left] or days[i] < days[right]:
                    left, right = i, i+k+1
                    break
            else:
                ans = min(ans, max(days[left], days[right]))
                left, right = right, right+k+1

        return ans if ans < float('inf') else -1



class MinQueue:
    def __init__(self):
        self.vec = collections.deque()
        self.minv = collections.deque()
        
    def push(self, v):
        while self.minv and self.minv[-1] > v:
            self.minv.pop()
        self.minv.append(v)
        self.vec.append(v)
    
    def getMin(self,):
        return self.minv[0]
    
    def pop(self):
        if self.vec[0] == self.minv[0]:
            self.minv.popleft()
        
        self.vec.popleft()

class Solution:
    def kEmptySlots(self, bulbs: List[int], k: int) -> int:
        days = [0] * len(bulbs)
        for day, position in enumerate(bulbs):
            days[position - 1] = day + 1

        res = float('inf')
        q = MinQueue()
        for i, v in enumerate(days):
            q.push(v)
            if i >= k and i < len(days)-1 :
                q.pop()
                if k == 0 or days[i-k] < q.getMin() and q.getMin() > days[i+1]:
                    res = min(res, max(days[i-k], days[i+1]))
                

        return res if res < float('inf') else -1


class Solution:
    def kEmptySlots(self, bulbs: List[int], k: int) -> int:
        blooming = []
        for day, bulb in enumerate(bulbs, 1):
            i = bisect.bisect(blooming, bulb)
            for neighbor in blooming[i-(i>0):i+1]:
                if abs(bulb - neighbor) - 1 == k:
                    return day
            blooming.insert(i, bulb)
        return -1


"""
If it winds up being full and data is presented as an array instead of a stream,
 why not start it as full? Then work from the back of the array,
  checking if previous() or next() are K away. 
  If they are, you have a candidate answer. 
  Either way, delete the current node, and then keep moving.

Since insertion/deletion (when you have the key) in a linked-list (including sorted) is O(1),
 you have an answer in O(n)!

Note that one complication is that as stated, this question can have multiple answers.
 Unfortunately the auto-grader only accepts the "first" (leftmost) correct answer. 
 So this method has the unfortunate pitfall of requiring you to search through the entire array, 
 instead of the first correct answer that you find! Still, it's O(n) worst case,
  which is asymptopically better than BST or skip list solutions.

An implementation detail is that my linkedlist is implemented with an array. 
If you want it to be slightly slower(but perhaps clearer to understand),
 you can use a HashMap plus explicitly declared LinkedList(as your own class) 
 to make a more formal ordered dictionary.


"""


class Solution:
    def kEmptySlots(self, bulbs: List[int], k: int) -> int:
        garden = [[i - 1, i + 1] for i in range(len(bulbs))]
        garden[0][0], garden[-1][1] = None, None
        ans = -1
        for i in range(len(bulbs) - 1, -1, -1):
            cur = bulbs[i] - 1
            left, right = garden[cur]
            if right != None and right - cur == k + 1:
                ans = i + 1
            if left != None and cur - left == k + 1:
                ans = i + 1
            if right != None:
                garden[right][0] = left
            if left != None:
                garden[left][1] = right
        return ans 