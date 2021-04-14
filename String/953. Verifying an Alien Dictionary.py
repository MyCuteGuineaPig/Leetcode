class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        degree = {c: i for i, c in enumerate(order)}
        
        for i in range(len(words)-1):
            for c1, c2 in zip(words[i], words[i+1]):
                if c1 != c2: 
                    if degree[c1] > degree[c2]:
                        return False
                    break
            else:
                if len(words[i]) > len(words[i+1]):
                    return False
        
        return True