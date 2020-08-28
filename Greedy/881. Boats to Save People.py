
class Solution:
    def numRescueBoats(self, people, limit):
        """
        :type people: List[int]
        :type limit: int
        :rtype: int
        """
        people.sort()
        i, j = 0, len(people)-1
        boats = 0
        while i< j:
            boats+=1
            if people[i]+people[j]<=limit:
                i+=1 
                j-=1
            else: 
                j-=1
            
        return boats if i>j else boats+1



class Solution:
    def numRescueBoats(self, people, limit):
        people.sort()
        i, j = 0, len(people)-1
        boats = 0
        while i<= j:
            boats+=1
            if people[i]+people[j]<=limit:
                i+=1 
                j-=1
            else: 
                j-=1
        return len(people) - j - 1


class Solution:
    def numRescueBoats(self, people, limit):
        people.sort(reverse=True)
        i, j = 0, len(people) - 1
        while i <= j:
            if people[i] + people[j] <= limit: j -= 1
            i += 1
        return i



class Solution:
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        people.sort()
        l, n = 0, len(people)
        for r in range(n - 1, -1, -1):
            if people[l] + people[r] <= limit: l += 1
            if l >= r: return n - r