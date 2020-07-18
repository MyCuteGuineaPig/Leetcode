"""
788. Rotated Digits

"""

class Solution:
    def rotatedDigits(self, N):
        """
        :type N: int
        :rtype: int
        """
        dp = [0,]*(N+1)
        count = 0
        for i in range(N+1):
            if i<=10:
                if i == 0 or i == 1 or i == 8 or i == 10: 
                    dp[i] = 1
                elif i == 2 or i == 5 or i == 6 or i == 9: 
                    dp[i] = 2
                    count += 1
            else:
                a = dp[i//10]
                b = dp[i%10]
                if a==1 and b==1:
                    dp[i] = 1
                elif a>=1 and b>=1:
                    dp[i] = 2 
                    count += 1
        return count


class Solution:
    def rotatedDigits(self, N):
        """
        :type N: int
        :rtype: int  2 5 6 9 
        """
        count = 0
        for i in range(1,N+1):
            i = str(i)
            if '3'in i or '4'in i or '7' in i:
                continue
            if '2'in i or '5'in i or '9' in i or '6' in i:
                count +=1
        return count       

class Solution:
    def rotatedDigits(self, N: int) -> int:
        def isValidRotation(num):
            return (not any(s in {'3', '4', '7'} for s in num)) and any(s in {'2', '5', '6', '9'} for s in num)

        return sum([isValidRotation(str(i)) for i in range(1, N+1)])

class Solution:
    def rotatedDigits(self, N: int) -> int:
        s1 = set([1, 8, 0])
        s2 = set([1, 8, 0, 6, 9, 2, 5])
        def isGood(x):
            s = set([int(i) for i in str(x)])
            return s.issubset(s2) and not s.issubset(s1)  #s 是s2 子集，但不是s1的子集
        return sum(isGood(i) for i in range(N + 1))

"""
+= 7 ** means you could pick digits from this set [0, 1, 8, 2, 5, 6, 9], 
    there are 7 different kinds of digits in this set, right?

7**len, permutation: 比如有两位数， [0, 1, 8, 2, 5, 6, 9]可以组合成49个


-= 3 ** is similar to the above, except that this time the set is [0, 1, 8].

比如 i = 249,
i = 0, v = 2 
    j = 0,  res = 49 - 9,  49 表示 0-100 有几位可以倒过来的,  9 表示几个倒过来是自己: 0(00), 1(01), 8(08), 10, 11, 18, 80,81,88
    j = 1,  表示 100 到 200 有多少位是可以倒过来的

i = 1, v = 2
    j = 0,  res += 7, 表示 200 到 210 有7位可以倒过来，因为set s插入了2, s = [2], 所以 s不是subset of s1 不会减去3 
    j = 1,  res += 7, 表示 210 到 220 有7位可以倒过来
    j = 2, res += 7, 表示 220 到 230 有7位可以倒过来
    j = 4, res += 0(4 not sub setset of s2), 表示 220 到 230 有0位可以倒过来
"""

class Solution:
    def rotatedDigits(self, N: int) -> int:
        s1 = set([0, 1, 8])
        s2 = set([0, 1, 8, 2, 5, 6, 9])
        s = set()
        res = 0
        N = map(int, str(N))
        for i, v in enumerate(N):
            for j in range(v):
                if s.issubset(s2) and j in s2:
                    res += 7**(len(N) - i - 1)
                if s.issubset(s1) and j in s1:
                    res -= 3**(len(N) - i - 1)
            if v not in s2:
                return res
            s.add(v)
        return res + (s.issubset(s2) and not s.issubset(s1))


class Solution:
    def rotatedDigits(self, N):
        """
        :type N: int
        :rtype: int
        """
        
        validCount =   [1,2,3,3,3,4,5,5,6,7]; #0, 1, 2, 5, 6, 8, 9
        excludeCount = [1,2,2,2,2,2,2,2,3,3]; #0, 1, 8
        breakDigit =  [0,0,0,1,1,0,0,1,0,0];
        excludeDigit = [1,1,0,0,0,0,0,0,1,0];
        
        s = str(N)
        n = len(s)
        count, base7, base3 = 0, 7**(n-1), 3**(n-1)
        exclude = 1
        for i in range(n):
            index = int(s[i])
            if index == 0 and i!=n-1: 
                base7 /= 7
                base3 /= 3
                continue
            if i != n-1: index -= 1
            v = validCount[index]*base7
            e = excludeCount[index]*base3 if exclude else 0
            print(v,e, base7, base3)
            count += v - e
            if breakDigit[int(s[i])]:
                break
            exclude = exclude & excludeDigit[int(s[i])]
            
            base7 /= 7
            base3 /= 3
    
        return int(count)
