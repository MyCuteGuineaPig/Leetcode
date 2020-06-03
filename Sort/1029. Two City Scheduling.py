class Solution:
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:
        costs.sort(key=lambda cost: cost[0] - cost[1])
        costs_for_A = sum([cost[0] for cost in costs[:len(costs) // 2]])
        costs_for_B = sum([cost[1] for cost in costs[len(costs) // 2:]])
        return costs_for_A + costs_for_B

"""
比如

costs = [[10,20],[30,200],[400,50],[30,20]]

Diff = 10, 170, -350, -10.
answer = 10 + 30 + 400 + 30 + -350 + -10 = 110


"""
class Solution:
    def twoCitySchedCost(self, costs):
        FirstCity = [i for i,j in costs]
        Diff = [j - i for i,j in costs]
        return sum(FirstCity) + sum(sorted(Diff)[:len(costs)//2])


class Solution:
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:
        costs.sort(key = lambda x: x[0]-x[1])
        return sum(i[0] for i in costs[:len(costs)//2]) + sum(j[1] for j in costs[len(costs)//2:])

class Solution:
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:
        return sum([v[i // (len(costs)//2)] for i, v in enumerate(sorted(costs, key=lambda x: x[0] - x[1]))])