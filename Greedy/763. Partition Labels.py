"""

763. Partition Labels

Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.

"""
# sliding window
class Solution:
    def partitionLabels(self, S):
        """
        :type S: str
        :rtype: List[int]
        """
        cnt = collections.Counter(S)
        cur = 0
        start = -1
        res = []
        for i, s in enumerate(S):
            cnt[s]-=1
            #print("i", i,"s",s,"cnt[s]",cnt[s])
            
            if cnt[s] == 0:
                while cur < i and cnt[S[cur]] == 0:
                    cur += 1
                if cur == i: 
                    res.append(i-start)
                    start = i
            #print("cur",cur,"start", start,"i", i ,"s", s)
        return res


class Solution:
    def partitionLabels(self, S):
        cnt = collections.Counter(S)
        count = 0
        res = []
        st = set()
        for s in S:
            cnt[s]-=1
            count+=1
            if cnt[s] > 0: 
                st.add(s)
            else:
                st.discard(s)
            if len(st) == 0:
                res.append(count)
                count = 0 
        return res


#last index position
class Solution:
    def partitionLabels(self, S):
        cnt = collections.defaultdict(int)
        for i, v in enumerate(S):
            cnt[v] = i
        
        res = []
        last = count = 0
        for i, s in enumerate(S):
            last = max(last, cnt[s])
            count+=1
            if last == i: 
                res.append(count)
                count = 0
        return res

#short but unefficient
class Solution:
    def partitionLabels(self, S):
        sizes = []
        while S:
            i = 1
            while set(S[:i]) & set(S[i:]):
                i += 1
            sizes.append(i)
            S = S[i:]
        return sizes