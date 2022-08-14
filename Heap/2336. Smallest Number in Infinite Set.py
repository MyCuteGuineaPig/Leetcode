class SmallestInfiniteSet:

    def __init__(self):
        self.cur = 1
        self.heap = []
        self.set = set()

    def popSmallest(self) -> int:
        if self.heap:
            num = heapq.heappop(self.heap)
            self.set.remove(num)
            return num
        self.cur += 1
        return self.cur - 1

    def addBack(self, num: int) -> None:
        if num < self.cur and num not in self.set:
            self.set.add(num)
            heapq.heappush(self.heap, num)


# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)