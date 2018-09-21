"""

757. Set Intersection Size At Least Two

Example 1:
Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
Output: 3
Explanation:
Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
Also, there isn't a smaller size set that fulfills the above condition.
Thus, we output the size of this set, which is 3.

Example 2:
Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
Output: 5
Explanation:
An example of a minimum sized set is {1, 2, 3, 4, 5}.

"""

class Solution:
    def intersectionSizeTwo(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key = lambda x: (x[1]))
        largest = second = -1
        res = 0
        for p in intervals:
            islargest = p[0] <= largest
            issecond = p[0] <= second
            if islargest and issecond: continue
            
            second =  p[1] -1 if islargest is False or p[1] == largest else largest  
            #比如[1,3], [3,7], [5,7], [4,8] 到[5,7]时 largest = 7, second = 3, 这 时候不调整largest, 调整second
            largest = p[1]
            res += 1 if islargest else 2
        return res



class Solution(object):
    def intersectionSizeTwo(self, intervals):
        max2 = [float('-inf')] * 2
        cnt = 0
        for lo, hi in sorted(intervals, key=lambda t:(t[1], -t[0])):
            intcnt = sum(x>=lo for x in max2)
            cnt += 2 - intcnt
            if intcnt == 0:
                max2 = hi-1, hi
            elif intcnt == 1:
                max2 = max2[1], hi
        return cnt


class Solution(object):
    def intersectionSizeTwo(self, intervals):
        max2 = [float('-inf')] * 2
        cnt = 0
        for lo, hi in sorted(intervals, key=lambda t:(t[0])): #sort by start, 下个区间的start <max2更新, 并缩小区间, 因为是用之前end点作为max2, end>prestart, 
            #下个start>prestart, 缩小区间，不会影响之前的点
            intcnt = sum(x>=lo for x in max2) 
            cnt += 2 - intcnt
            if intcnt == 0:
                max2 = hi-1, hi
            elif intcnt == 1 and hi<max2[1]: #缩小区间, 肯定是lo < hi[0], max2 = [5,8], lo,hi = [6,7], 更新max2 为[6,7]
                max2 = hi-1, hi
            elif intcnt == 1:       #此时 h1 > max2[i], 造成intcnt == 1, 肯定还是lo < hi[0], 比如 max2[5,10], lo, hi = [6,15], new max2 = [10,15]
                max2 = max2[1], hi
            elif intcnt == 2 and hi<max2[1]: #缩小区间, 比如[[0,20], [0,1]] max2 = [19,20], 到了[0,1] max2变成[0,1] 
                max2 = min(max2[0], hi-1), hi  #比如[[1,5], [5,16], [5,13]], max2 = [4,5], [5,16]touch上一个5,变成max2 = [5,16], [5,13] 再缩小间距, max2 变成[5,13]
        return cnt

"""
第一个if intcnt == 0: 
    maxh2   *******************
    cur                          ************

第二个if intcnt == 1 and hi<max2[1]
    maxh2   ************
    cur        *****

第三个if intcnt == 1 and hi>=max2[1]
    maxh2   ************
    cur             *************    

第四个if intcnt == 2 and hi<max2[1]
    maxh2     ************
    cur    *********************    

    maxh2               ************
    cur    **********


"""

[[0, 1], [1, 4], [0, 5], [2, 6], [4, 7], [5, 8], [7, 8], [7, 9], [1, 9], [5, 10]]

[[0, 1], [0, 5], [1, 4], [1, 9], [2, 6], [4, 7], [5, 8], [5, 10], [7, 8], [7, 9]]
[0,1];             
                  [1,4]    3
                                 [4,6] 4
                                                [6,8] 5 
                                                                 [7,8] 6

[[0, 10], [0, 6], [0, 1], [1, 3], [1, 2], [2, 5], [4, 9], [6, 7], [6, 8], [7, 9]]
0 10 (9, 10) 2
0 6 (5, 6) 2
0 1 (0, 1) 2
1 3 (1, 3) 3
1 2 (1, 2) 3
2 5 (2, 5) 4
4 9 (5, 9) 5
6 7 (9, 7) 6
6 8 (9, 7) 6
7 9 (9, 7) 6


[[0, 20], [1, 2], [1, 4], [1, 11], [2, 14], [3, 6], [4, 13], [4, 5], [5, 16], [5, 13], [6, 20], [6, 15], [7, 19], [9, 12], [10, 19], [11, 12], [12, 13], [13, 17], [16, 20], [16, 18]]
0 20 (19, 20) 2
1 2 (1, 2) 2
1 4 (1, 2) 2
1 11 (1, 2) 2
2 14 (2, 14) 3
3 6 (5, 6) 4
4 13 (5, 6) 4
4 5 (4, 5) 4
5 16 (5, 16) 5
5 13 (5, 13) 5
6 20 (13, 20) 6
6 15 (13, 15) 6
7 19 (13, 15) 6
9 12 (11, 12) 6
10 19 (11, 12) 6
11 12 (11, 12) 6
12 13 (12, 13) 7
13 17 (13, 17) 8
16 20 (17, 20) 9
16 18 (17, 18) 9