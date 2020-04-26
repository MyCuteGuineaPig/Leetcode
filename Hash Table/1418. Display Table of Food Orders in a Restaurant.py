class Solution:
    def displayTable(self, orders: List[List[str]]) -> List[List[str]]:
         t = collections.defaultdict(lambda: collections.defaultdict(int))
         dishes = set()
         for _, num, d in orders:
            t[int(num)][d] += 1
            dishes.add(d)
         dishes = sorted(dishes)
         print(t)
         res = [["Table"] + dishes ]
         for num, cnt in sorted(t.items()):
            tmp = [str(num)] 
            for d in dishes:
                if d in cnt:
                    tmp += str(cnt[d]), 
                else:
                    tmp += "0",
            res += tmp,
         return res
            

class Solution(object):
    def displayTable(self, orders):
        """
        :type orders: List[List[str]]
        :rtype: List[List[str]]
        """
        table_count = collections.defaultdict(collections.Counter)
        for _, table, food in orders:
            table_count[int(table)][food] += 1
        foods = sorted({food for _, _, food in orders})
        result = [["Table"]]
        result[0].extend(foods)
        for table in sorted(table_count):
            result.append([str(table)])
            result[-1].extend(str(table_count[table][food]) for food in foods)
        return result