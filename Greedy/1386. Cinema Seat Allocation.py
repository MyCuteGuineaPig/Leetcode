class Solution:
    def maxNumberOfFamilies(self, n: int, rs: List[List[int]]) -> int:
        st = collections.defaultdict(set)
        for r,c in rs:
            if c in set([2,3,4,5]):
                st[r].add(1)
            if c in set([4,5,6,7]):
                st[r].add(2)
            if c in set([6,7,8,9]):
                st[r].add(3)
        
        pr = 0
        cnt = 0
        for i, s in sorted(st.items()):
            if i -1 != pr:
                cnt += (i -1 - pr)*2
            t1 = t2 = t3 = 1
            if 1 in s:
                t1 = 0
            if t1 or 2 in s:
                t2 = 0
            if t2 or 3 in s:
                t3 = 0
            pr = i
            cnt += t1 + t2 + t3

        cnt += (n - pr)  *2
        return cnt


class Solution(object):
    def maxNumberOfFamilies(self, n, reservedSeats):
        """
        :type n: int
        :type reservedSeats: List[List[int]]
        :rtype: int
        """
        lookup = collections.defaultdict(lambda: [False]*3)
        for r, c in reservedSeats:
            if 2 <= c <= 5:
                lookup[r][0] = True
            if 4 <= c <= 7:
                lookup[r][1] = True
            if 6 <= c <= 9:
                lookup[r][2] = True
        result = 2*n
        for a, b, c in lookup.itervalues():
            if not a and not c:
                continue
            if not a or not b or not c:
                result -= 1
                continue
            result -= 2
        return result


class Solution2(object):
    def maxNumberOfFamilies(self, n, reservedSeats):
        """
        :type n: int
        :type reservedSeats: List[List[int]]
        :rtype: int
        """
        reservedSeats.sort()
        result, i = 2*n, 0
        while i < len(reservedSeats):
            reserved = [False]*3
            curr = reservedSeats[i][0]
            while i < len(reservedSeats) and reservedSeats[i][0] == curr:
                _, c  = reservedSeats[i]
                if 2 <= c <= 5:
                    reserved[0] = True
                if 4 <= c <= 7:
                    reserved[1] = True
                if 6 <= c <= 9:
                    reserved[2] = True
                i += 1
            if not reserved[0] and not reserved[2]:
                continue
            if not all(reserved):
                result -= 1
                continue
            result -= 2
        return result

class Solution(object):
    def maxNumberOfFamilies(self, n, reservedSeats):
        """
        :type n: int
        :type reservedSeats: List[List[int]]
        :rtype: int
        """
        res = 2*n
        ht = {}
        for r in reservedSeats:
            if r[0] not in ht:
                ht[r[0]] = {r[1]}
            else:
                ht[r[0]].add(r[1])
        for x in ht:
            cnt = 0
            if 2 not in ht[x] and 3 not in ht[x] and 4 not in ht[x] and 5 not in ht[x]:
                cnt +=1
            if 6 not in ht[x] and 7 not in ht[x] and 8 not in ht[x] and 9 not in ht[x]:
                cnt += 1
            if 4 not in ht[x] and 5 not in ht[x] and 6 not in ht[x] and 7 not in ht[x] and cnt == 0:
                cnt += 1
            res += (cnt-2)
        return res