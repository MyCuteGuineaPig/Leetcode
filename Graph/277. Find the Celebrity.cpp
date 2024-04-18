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