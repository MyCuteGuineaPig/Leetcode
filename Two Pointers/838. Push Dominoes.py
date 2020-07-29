/*
'R......R' => 'RRRRRRRR'
'R......L' => 'RRRRLLLL' or 'RRRR.LLLL'
'L......R' => 'L......R'
'L......L' => 'LLLLLLLL'
*/

class Solution:
    def pushDominoes(self, dominoes: str) -> str:
        d = 'L' + dominoes + 'R'
        res = []
        i = 0
        for j in range(1, len(d)):
            if d[j] == '.': continue
            middle = j - i - 1
            if i: res.append(d[i])
            if d[i] == d[j]: res.append(d[i] * middle)
            elif d[i] == 'L' and d[j] == 'R': res.append('.' * middle)
            else: res.append('R' * (middle // 2) + '.' * (middle % 2) + 'L' * (middle // 2))
            i = j
        return ''.join(res)


class Solution:
    def pushDominoes(self, dominoes: str) -> str:
        while(True):
            new = dominoes.replace('R.L', 'S')
            new = new.replace('.L','LL').replace('R.','RR')
            if new == dominoes:
                break
            else:
                dominoes = new
        return dominoes.replace('S', 'R.L')




"""

First pass, from left to right, only count distance of current index to previous 'R'. Save all distance in dist array
Second pass, from right to left, count distance of current index to previous 'L'. 
    If lDist < rDist (dist[i]), current cell should be 'L', if lDist == rDist, current cell should be '.'

"""


class Solution(object):
    def pushDominoes(self, dominoes):
        """
        :type dominoes: str
        :rtype: str
        """
        lst = list(dominoes)
        dist = [0] * len(dominoes)
        rDist = None
        for i, val in enumerate(lst):
            if val == 'R':
                rDist = 0
            elif val == 'L':
                rDist = None
            elif rDist != None:
                rDist += 1
                dist[i] = rDist
                lst[i] = 'R'
        lDist = None
        for i in range(len(lst) - 1, -1, -1):
            if dominoes[i] == 'L':
                lDist = 0
            elif dominoes[i] == 'R':
                lDist = None
            elif lDist != None:
                lDist += 1
                if lDist < dist[i] or lst[i] == '.':
                    lst[i] = 'L'
                elif lDist == dist[i]:
                    lst[i] = '.'
        return ''.join(lst)



class Solution:
    def pushDominoes(self, dominoes: str) -> str:
        lo, hi = 0, 0
        d = list(dominoes)
        chk = {"L", "R"}
        while hi < len(d):
		   #window needs to be filled or we might have a postfix like "R....", so fill it
            if d[hi] in chk or hi == len(d)-1:
                self.do_fill(lo, hi, d)
                lo=hi
            hi+=1
            
        return "".join(d)
    
    def do_fill(self, lo, hi, d):
        if d[hi] == "L":
            if d[lo] == "R":
			    #window is Rs from the left and Ls from the right
                while lo < hi:
                    d[lo] = "R"
                    d[hi] = "L"
                    lo+=1
                    hi-=1
            else:
			   #window is completely L
                while lo <= hi:
                    d[lo] = "L"
                    lo+=1                 
        elif d[lo] == "R":
				#window is completely R
                while lo <= hi:
                    d[lo] = "R"
                    lo+=1  