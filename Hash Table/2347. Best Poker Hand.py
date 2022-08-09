class Solution:
    def bestHand(self, r: List[int], s: List[str]) -> str:
        if max(s) == min(s):
            return "Flush" 
        match max(Counter(r).values()):
            case 5 | 4 | 3:
                return "Three of a Kind"
            case 2:
                return "Pair"
            case _:
                return "High Card"