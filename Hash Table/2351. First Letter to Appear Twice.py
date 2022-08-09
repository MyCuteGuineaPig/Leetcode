class Solution:
    def repeatedCharacter(self, s: str) -> str:
        
        setS = set()

        for x in s:
            if x in setS:
                return x
            else:
                setS.add(x)