"""
Math
To get a point at room k sarting from room i:
hp - (damage from i to k) >= requirement[k]

Let's rearrange this:
hp + (damage from k + 1 to n) - (damage from i to n) >= requirement[k]

So that
hp + (damage from k + 1 to n) - requirement[k] >= (damage from i to n)

"""


"""
选择bisect_right 因为要点 是 cur >= prefix[i]
bisect_right 返回第一个大于cur的index
ind - 1 是等于或者小于cur的点

"""
class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        #st = sortedList()
        prefix = [0]
        for d in damage[::-1]:
            prefix.append(prefix[-1] + d)

        res = 0
        for k, r in enumerate(requirement[::-1]):
            cur =  hp + prefix[k] - r 
            ind = bisect.bisect_right(prefix, cur) -1

            res += max((ind - k), 0)
            """
            ind, i 都是反序的index
            ind 对于 原数中 n - ind 的位置（prefix length = requirement + 1）
            k 对应requirement中 n - k - 1的位置

            所以从index 到 k 的距离就是
            差是 (n - k - 1) - (n - ind) + 1 = ind - i - 1
            """
        return res
        
"""

hp + (damage from k + 1 to n) - requirement[k] >= (damage from i to n)

st 是 formula 左边的值
total 是右边的，看有几dmange 满足condition

"""


class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        st = SortedList()
        res = total = 0
        for d, r in list(zip(damage, requirement))[::-1]:
            st.add(hp + total - r )
            total += d
            res += len(st) - st.bisect_left(total)
        return res





    

class Fenwick:
    def __init__(self,n):
        self.n = n
        self.tree = [0]*(n + 1)

    def add(self, i, v):
        while i <= self.n:
            self.tree[i] += v 
            i += i & -i

    def sum(self, i):
        cur = 0
        while i > 0 : 
            cur += self.tree[i]
            i -= i & -i
        return cur

    def range_sum(self, l, r):
        return self.sum(r) - self.sum(l-1)


class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        prefix = [0]
        for d in damage:
            prefix.append(prefix[-1] + d)

        n = len(damage)
        life = [0]
        for i in range(1, n+1):
            life.append(prefix[i] + requirement[i-1] - hp)

        #print(life)

        vals = []
        for i in range(n):
            vals.append(prefix[i])
        for i in range(1, n+1):
            vals.append(life[i])

        uniq = sorted(set(vals))
        index = {v: i + 1 for i , v in enumerate(uniq)}
        print(index)

        tree = Fenwick(len(uniq))
        ans = 0
        for i in range(1, n+1):
            pos2 = index[prefix[i-1]]
            tree.add(pos2, 1)
            
            pos = index[life[i]]
            ans += tree.range_sum(pos, len(uniq))
            

        return ans