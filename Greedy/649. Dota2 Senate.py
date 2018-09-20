"""
649. Dota2 Senate


Input: "RD"
Output: "Radiant"
Explanation: The first senator comes from Radiant and he can just ban the next senator's right in the round 1. 
And the second senator can't exercise any rights any more since his right has been banned. 
And in the round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.

Example 2:
Input: "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in the round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in the round 1. 
And in the round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.

"""

class Solution:
    def predictPartyVictory(self, senate):
        """
        :type senate: str
        :rtype: str
        """
        R = [0]*len(senate)
        D = [0]*len(senate)
        qR = collections.deque()
        qD = collections.deque()
        n = len(senate)
        for i,s in enumerate(senate):
            if s == 'R':
                qR.append(i)
            else:
                qD.append(i)
        while qR and qD:
            if qR[0] < qD[0]:
                qD.popleft()
                qR.append(qR.popleft()+n)
            else:
                qR.popleft()
                qD.append(qD.popleft()+n)
        return "Dire" if qD else "Radiant"


#如果s 只有一个字母代表不能消灭了
class Solution:
    def predictPartyVictory(self, senate):
        s = senate
        cnt = 0
        while len(set(s)) != 1:
            ns = ""
            for i in s: 
                if i == 'D':
                    cnt += 1 
                    if cnt > 0:
                        ns += i
                else: 
                    cnt -= 1 
                    if cnt < 0:
                        ns += i
            s = ns
        return "Dire" if set(s) == {'D'} else "Radiant"



class Solution:
    def predictPartyVictory(self, senate):
        """
        :type senate: str
        :rtype: str
        """
        ban = {'R': 0, 'D': 0}
        opp = {'R': 'D', 'D': 'R'}
        
        while len(set(senate)) == 2:
            s = ''
            for c in senate:
                if ban[c] == 0:
                    ban[opp[c]] += 1
                    s += c
                else:
                    ban[c] -= 1
            senate = s         
        return 'Dire' if senate[0] == 'D' else 'Radiant'


class Solution:    
    def predictPartyVictory(self, senate):
        A = collections.deque()
        people = [0, 0]
        bans = [0, 0]

        for person in senate:
            x = person == 'R'
            people[x] += 1
            A.append(x)

        while all(people):
            x = A.popleft()
            people[x] -= 1
            if bans[x]:
                bans[x] -= 1
            else:
                bans[x^1] += 1
                A.append(x)
                people[x] += 1

        return "Radiant" if people[1] else "Dire"

