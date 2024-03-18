class TimeMap:

    def __init__(self):
        self.mp = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        bisect.insort(self.mp[key], (timestamp, value))
        #print(self.mp)

    def get(self, key: str, timestamp: int) -> str:
        ind = bisect.bisect_left(self.mp[key], (timestamp+1, ''))
        #print(self.mp[key], key, timestamp, "ind ",ind)
        if ind == 0:
            return ""
        return self.mp[key][ind-1][1]


# Your TimeMap object will be instantiated and called as such:
# obj = TimeMap()
# obj.set(key,value,timestamp)
# param_2 = obj.get(key,timestamp)