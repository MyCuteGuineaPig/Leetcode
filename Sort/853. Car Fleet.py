class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        pq = sorted([[p, (target-p)/v] for p, v in zip(position, speed)], key = lambda x: (-x[0], -x[1]))
        fl = 0; time = 0
        for i, t in pq:
            if t>time: 
                fl+=1
                time = t
        return fl
