/*
134. Gas Station
https://leetcode.com/problems/gas-station/description/


There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). 
You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

Example 1:

Input: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: 
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.


input = [3,1,1]
        [1,2,2]
output = 0 


*/




/*
If car starts at A and can not reach B. Any station between A and B
can not reach B.(B is the first station that A can not reach.)
如果从A出发 不能到达B，A和B之前任何点都不能到B，假设B是从A出发第一个点到不了的
prove: A和B 之间有个C点, A可以到达C 但是不能到达B， 因为A 到B gas 积累为负，但是A可以到C，到C时，gas积累>=0, 
如果从A到不了B，从C出发也到不了B


If the total number of gas is bigger than the total number of cost. There must be a solution.
用反证法证明： total gas - total cost >=0, there is no solution, 假如任意选个点i，从i出发到j(j是第一个点不能到达的从i)，
那么从i到j的gas - cost < 0, 接下来从 j出发，到k（k是从j出发第一个点不能到达的），gas - cost < 0. 
repeat the process unitl we already travel a circul, 我们发现gas - cost < 0，与上面contradict


The reason why I think this works:
1, if sum of gas is more than sum of cost, then there must be a solution. 
And the question guaranteed that the solution is unique
(The first one I found is the right one).
2, The tank should never be negative, so restart whenever there is a negative number.

因为油箱不能为负数，所以当负数的时，起点是下一个

*/
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int tank = 0, totaltank = 0, start = 0, totalcost = 0;
        for(int i = 0; i<gas.size();i++){
            totaltank += gas[i];
            totalcost += cost[i];
            tank = tank + gas[i] -cost[i];
            
            if(tank < 0)
                start = i+1, tank = 0;
        }
        return totaltank >= totalcost ?start:-1;
    }
};



class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalgas = accumulate(gas.begin(), gas.end(),0);
        int totalcost = accumulate(cost.begin(), cost.end(), 0);
        if(totalgas < totalcost) return -1;
        int id = -1, cursum  = 0, rightmost = -1;
        /* 
            从右面向左往回走，因为是轮回的, 到最后一点后要回到0点, 
            
            每个点积累的gas = gas[i] - cost[i]

            所以要积累尽可能多的gas在回到0点前，从id点到结尾 积累最多的gas的点, id就是结果
        */
        for(int i = gas.size()-1; i>=0; i--){
            cursum += gas[i] - cost[i];
            if(cursum > rightmost){
                rightmost = cursum;
                id = i;
            }
        }
        return id;
    }
};

/*
从最后一位开始，如果现在积累的大于0，表示我们可以从start点到现在，就再往前走，知道end与起点重合，我们知道由start开始，可以开始
如果现在积累的小于0，表示这个起点不合适，我们换另一个起点，往后倒一步，这样好处是，只是增加一个积累值，不会吧之前做的累积白做，

trick: 每次往后退一步 so that we can check all stations on the circuit

another trick: 从末尾开始， avoid corner cases

*/
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {

       int start = gas.size()-1;
       int end = 0;
       int sum = gas[start] - cost[start];
       while (start > end) {
          if (sum >= 0) {
             sum += gas[end] - cost[end];
             ++end;
          }
          else {
             --start;
             sum += gas[start] - cost[start];
          }
       }
       return sum >= 0 ? start : -1;
    }
};