class Solution:
    def mergeSimilarItems(self, items1: List[List[int]], items2: List[List[int]]) -> List[List[int]]:
        dic = {k[0]:k[1] for k in items1 }
        for k in items2:
            dic[k[0]]= dic.get(k[0], 0) + k[1]
        return [[k, v] for k, v in sorted(dic.items())]

class Solution:
    def mergeSimilarItems(self, items1: List[List[int]], items2: List[List[int]]) -> List[List[int]]:
        cnt = Counter()
        for v, w in items1 + items2:
            cnt[v] += w
        return sorted(cnt.items())

class Solution:
    def mergeSimilarItems(self, items1: List[List[int]], items2: List[List[int]]) -> List[List[int]]:
        cnt = Counter(dict(items1))
        cnt += Counter(dict(items2))
        return sorted(cnt.items())

class Solution:
    def mergeSimilarItems(self, items1: List[List[int]], items2: List[List[int]]) -> List[List[int]]:
        return sorted((Counter(dict(items1)) + Counter(dict(items2))).items())