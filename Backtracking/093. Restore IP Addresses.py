#93. Restore IP Addresses

class Solution:
    def restoreIpAddresses(self,s):
        """
        :type s: str
        :rtype: List[str]
        """
        res = []
        for a in range(1,4):
            for b in range(1,4):
                for c in range(1,4):
                    for d in range(1,4):
                        if(a+b+c+d == len(s)):
                            A, B, C, D = s[:a],s[a:a+b],s[a+b: a+b+c], s[a+b+c: a+b+c+d] 
                            if(int(A)<=255 and int(B)<=255 and int(C)<=255 and int(D)<=255 ):
                                if(str(int(A)) == A and  str(int(B)) == B and str(int(C)) == C and str(int(D)) == D):
                                    res.append(A+'.'+B+'.'+C+'.'+D)
        return res


#不转化两次int，直接存int
class Solution:
    def restoreIpAddresses(self,s):
        """
        :type s: str
        :rtype: List[str]
        """
        res = []
        for a in range(1,4):
            for b in range(1,4):
                for c in range(1,4):
                    for d in range(1,4):
                        if a+b+c+d == len(s):
                            A, B, C, D = int(s[:a]),int(s[a:a+b]),int(s[a+b: a+b+c]), int(s[a+b+c: a+b+c+d]) 
                            if(A<=255 and B <=255 and C <=255 and D <=255 ):
                                ip = str(A)+'.' +str(B)+'.'  +str(C)+'.' +str(D)
                                if len(ip) == len(s)+ 3 :
                                    res.append(ip)
        return res