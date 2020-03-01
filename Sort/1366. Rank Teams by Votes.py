"""
The reason to choose 10, because in some extreme situtaion, 
for example, 'A' only appear once at first position but 'B' appear 999 times at second position. we need to rank A before B.


So we need to satistify below in equation

[(1<<(k*i)) > 999*(1<<(k*(i-1)))for i in range(1000, 1,-1)]
False in li #need to be False 
The smallest k is 10
"""


class Solution:
    def rankTeams(self, votes: List[str]) -> str:
        dic = collections.defaultdict(int)
        l = len(votes[0])
        for vote in votes:
            for i, v in enumerate(vote):
                dic[v] +=  1<<(10*(l - i-1))
        return ''.join([k for k, v in sorted(dic.items(), key = lambda item: (-item[1], item[0]))])



class Solution:
    def rankTeams(self, votes):
        count = {v: [0] * len(votes[0]) + [v] for v in votes[0]}
        for vote in votes:
            for i, v in enumerate(vote):
                count[v][i] -= 1
        return ''.join(sorted(votes[0], key=count.get))