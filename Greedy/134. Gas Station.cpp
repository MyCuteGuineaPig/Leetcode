 
/*
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
Two Pointer

从最后一位开始，如果现在积累的大于0，表示我们可以从start点到现在，就再往前走，直到end与起点重合，我们知道由start可以开始
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


/*
What does "i < n * 2 - 1" mean?


Simulate a cycle by an array, such as:
0,1,2...n-1,0,1,2....n-2
total 2n-1 elements.

 */
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        for(int i = 0; i < gas.size(); i++) {
            gas[i] -= cost[i];
        }
        int sum = 0;
        int result = 0;
        int n = gas.size();
        for(int i = 0; i < n * 2 - 1; i++) {
            sum += gas[i % n];
            if(sum < 0) {
                result = i + 1;
                if(result >= n) {
                    return -1;
                }
                sum = 0;
            }
        }
        return result;
    }
};