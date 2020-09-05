class Solution:
    def strWithout3a3b(self, A: int, B: int) -> str:
        if A == 0:
            return 'b' * B
        elif B == 0:
            return 'a' * A
        elif A == B:
            return 'ab' * A
        elif A > B:
            return 'aab' + self.strWithout3a3b(A - 2, B - 1)
        else:
            return self.strWithout3a3b(A - 1, B - 2) + 'abb'


class Solution:
    def strWithout3a3b(self, A: int, B: int) -> str:
        if A == 0 or B == 0:
            return 'a'*A +'b'*B
        elif A>B:
            return 'aab' + self.strWithout3a3b(A-2, B-1)
        elif B>A:
            return self.strWithout3a3b(A-1, B-2)+ 'abb'
        else:
            return 'ab' * A


#See pictures at https://leetcode.com/problems/string-without-aaa-or-bbb/discuss/508543/APPLES-and-BANANAS-solution-(with-picture)
class Solution:
    def strWithout3a3b(self, A: int, B: int) -> str:
        if A > B:
            numberToLayDown = A
            numberToTopUp = B
            charToLayDown = "a"
            charToTopUp = "b"
        else:
            numberToLayDown = B
            numberToTopUp = A
            charToLayDown = "b"
            charToTopUp = "a"

            
        repetition = int(numberToLayDown / 2)
        remainder = numberToLayDown % 2
        
        stk = []
        for i in range(repetition):
            stk.append(charToLayDown + charToLayDown)
        if remainder:
            stk.append(charToLayDown)
        
        stkSize = len(stk)
        stkIdx = 0
        while numberToTopUp > 0:
            stk[stkIdx] += charToTopUp
            stkIdx = (stkIdx + 1) % stkSize
            numberToTopUp -= 1
            
        return "".join(stk)