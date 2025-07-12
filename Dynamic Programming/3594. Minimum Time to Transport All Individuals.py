"""
Each state is defined as a tuple (t, p, mask, j):

t: current time.
p: boat position (0 = camp, 1 = destination).
mask: bitmask of people already at the destination.
j: current stage index.


We use a visited map seen[(p, mask, j)] = t
to avoid revisiting worse states.


## Transition

From camp (p == 0):
Try sending every group of size 1 to k to the other side.

From destination (p == 1):
Try returning each person (individually) to bring the boat back.

Each time we cross or return, we update the stage index:
new_j = (j + floor(time_taken)) % 

## Termination 

If all n people are on the destination side and the boat is also there
(mask == (1 << n) - 1 and p == 1)
return the current time rounded to 5 decimals.
If the queue is exhausted without achieving that, return -1.0.


"""

"""

Some question why don't use the fastest person to go back 

returning the fastest one might not give optimal answer since the time also manipulates the stage
so a slower person might give a better stage than a faster one, (因为慢的人回去可能有更好的stage)


"""

class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        heap = [(0, 0, 0, 0)]
        seen = dict()

        full_mask = (1 << n) - 1 

        while heap: 
            t, p, mask, j = heappop(heap)
            state = (p, mask, j)
            if state in seen and seen[state] <= t:
                continue
            seen[state] = t
            if mask == full_mask and p == 1: 
                return round(t, 5)

            if p == 0:
                camp = [i for i in range(n) if not (mask >> i) & 1]
                for r in range(1, min(k, len(camp)) + 1):
                    for group in combinations(camp, r):
                        cross = max(time[i] for i in group) * mul[j]
                        new_j = (j + floor(cross)) % m
                        new_mask = mask
                        for i in group:
                            new_mask |= (1<<i)
                        heappush(heap, (t+cross, 1, new_mask, new_j))
            else:
                dst = [i for i in range(n) if (mask >> i) & 1]
                for i in dst:
                    return_time = time[i] * mul[j]
                    new_j = (j + floor(return_time)) % m
                    new_mask = mask & ~(1 << i)
                    heappush(heap, (t+return_time, 0, new_mask, new_j))
        

        return -1.0