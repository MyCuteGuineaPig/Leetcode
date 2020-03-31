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