"""
659. Split Array into Consecutive Subsequences

You are given an integer array sorted in ascending order (may contain duplicates), you need to split them into several subsequences, 
where each subsequences consist of at least 3 consecutive integers. Return whether you can make such a split.

Example 1:
Input: [1,2,3,3,4,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 

1, 2, 3
3, 4, 5

Example 2:
Input: [1,2,3,3,4,4,5,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3, 4, 5
3, 4, 5

Example 3:
Input: [1,2,3,4,4,5]
Output: False

"""
class Solution:
    def isPossible(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        count = collections.Counter(nums)
        nums = [i for i, _ in itertools.groupby(nums)]
        one = two = three = 0
        print(sorted(count.items()))
        for i in nums: 
            if i-1 not in count: 
                if one or two: 
                    return False
                one, two, three = count[i], 0, 0 
            else:
                if count[i] < one + two: return False
                one, two, three = max(0, count[i] - one - two - three), one, two + min(three, count[i]-one-two)
                #count[i] - one - two - three 三个都接不住，来新one 
                #two 等于原来的one
                #原来的two 变成现在的three, 但是注意一个情况可能count[i]给了one, two后还富裕，就给三，但是富裕的可能比three多，就不能再给了，再多的给one
                # or three 比富裕的多，那么原来的三 就terminate 一部分，把富裕的给接上
                #注: 如果count[i] > one + two + three, 那么three = two + min(three, count[i]-one-two) = two +three
                #    one = count[i] - one - two
        return one == two == 0


class Solution:
    def isPossible(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        cnt = collections.Counter(nums)
        tail = collections.defaultdict(int)
        for i in nums: 
            if cnt[i] == 0: continue
            cnt[i] -= 1
            if tail[i-1]:
                tail[i-1]-=1
                tail[i] += 1
            elif cnt[i+1] and cnt[i+2]:
                cnt[i+1] -= 1
                cnt[i+2] -=1 
                tail[i+2] += 1
            else: return False
        return True


"""
I am using a kind of greedy method. runs build a map between tail number and the current run length.
 For example, for a consecutive seq 3,4,5, the key(tail number) is 5 and length is 3.

The problem is there might be multiple sub seqs which all end with the same number, but have different length. 
like we have another subseq 4,5. So there are two entries in the value part of 5: runs: {5: [3,2]}

so, when we met a new number 6, we want to merge it into existing subseqs. Which one should we use? 
Intuitively, if we pick up the shorter one and append the new number into that,
 we are more likely to make sure all the seqs are longer than 3. So I use a PriorityQueue to store these length.
"""
import heapq
class Solution(object):
    def isPossible(self, A):
        runs = {} # end -> [lengths]
        for v in A:
            if v - 1 not in runs:
                if v not in runs:
                    runs[v] = [1]
                else:
                    heapq.heappush(runs[v], 1)
            else:
                length = heapq.heappop(runs[v-1]) + 1
                if len(runs[v-1]) == 0:
                    del runs[v-1]
                if v not in runs:
                    runs[v] = []
                heapq.heappush(runs[v], length)
        for v, arr in runs.items():
            if len(arr) > 0 and min(arr) < 3:
                return False
        return True

from  collections import defaultdict
import heapq
class Solution:
    def isPossible(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        heap, last = [], defaultdict(int)
        for num in nums:
            last[num] += 1
            if heap and heap[0][0] <= num - 1:
                if heap[0][0] < num - 1:
                    return False
                else:
                    last[num - 1] -= 1
                    n, l = heapq.heappop(heap)
                    if l == -1:
                        heapq.heappush(heap, (num, -2))
            elif num - 1 not in last or not last[num - 1]:
                heapq.heappush(heap, (num, -1))
            else:
                last[num - 1] -= 1
        return not heap