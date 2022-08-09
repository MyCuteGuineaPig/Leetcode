import collections
import heapq

class NumberContainers:

    def __init__(self):
        self.number_to_index_set = defaultdict(set)
        self.number_to_index_heap = defaultdict(list)
        self.index_map = {}

    def change(self, index: int, number: int) -> None:
        if index in self.index_map:
            old_number = self.index_map[index]
            self.number_to_index_set[old_number].remove(index)
        self.index_map[index] = number
        self.number_to_index_set[number].add(index)
        heapq.heappush(self.number_to_index_heap[number],index)
            

    def find(self, number: int) -> int:
        while self.number_to_index_heap[number] and self.number_to_index_heap[number][0] not in self.number_to_index_set[number]:
            heapq.heappop(self.number_to_index_heap[number])
            
        return -1 if not self.number_to_index_heap[number]  else  self.number_to_index_heap[number][0]


# Your NumberContainers object will be instantiated and called as such:
# obj = NumberContainers()
# obj.change(index,number)
# param_2 = obj.find(number)