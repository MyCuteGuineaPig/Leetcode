/*

77. Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int>cur;
        vector<vector<int>>ans;
        if(n<1 || n<k)
			return ans;
        backtracking(ans,cur,n,k,1);
        return ans;
    }
    
    
    void backtracking(vector<vector<int>>& ans, vector<int>& cur, int n, int k,int begin){
        if(n - begin + 1 < k)
            return;
        if(k == 0) {
            ans.push_back(cur);
            return;
        }
        
        for(int i = begin; i<=n; i++){
            cur.push_back(i);
            backtracking(ans,cur,n,k-1,i+1);
            cur.pop_back();
        }
    }
};


/*
Iterative solution
*/
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
		vector<vector<int>>ans;
        vector<int>p(k,0);
        int i = 0;
        while(i>=0){
            p[i]++;
            if(p[i]>n){
                i--;
            }else if(i==k-1) ans.push_back(p);
            else{
                i++;
                p[i] = p[i-1];
            }
        }
        return ans;
	}
};