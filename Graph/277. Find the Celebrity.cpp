/* The knows API is defined for you.
      bool knows(int a, int b); */
//Brute Force
class Solution {
public:
    int findCelebrity(int n) {
        vector<int>outdegree(n);
        vector<int>indegree(n);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(i == j) continue;
                //cout<<i<<" j "<<j<<endl;
                if(knows(i, j)){
                    outdegree[i]++;
                    indegree[j]++;
                }
            }
        }
        int res = -1;
        for(int i = 0; i < n; ++i){
            if(outdegree[i] == 0 && indegree[i] == n-1){
                if(res != -1){
                    return -1;
                }
                res = i;
            }
        }
        return res;
    }
};


/*
On the graph representation, a celebrity is a person who has exactly n - 1 directed edges going in 
(everybody knows them) and 0 edges going out (they know nobody).

Prove: 

Assume there is a celebrity, then they must have 0 outdegree

假设 0 不是celebrity, 0 知道i, 两种情况
- i 是celebrity, 则i 不知道任何其他的人
- i 不是celebrity, j 是celebrity, 则i 一定知道j, 
    那么进入下iteration 找到j



*/


class Solution {
public:
    int findCelebrity(int n) {
        int candidate = 0;
        for(int i = 0; i < n; ++i){
            if (knows(candidate, i))
                candidate = i;
        }
        for(int i = 0; i < n; ++i){
            if (candidate == i) continue;
            if(knows(candidate,i) || !knows(i, candidate)){
                return -1;
            }
        }
        return candidate;
    }
};