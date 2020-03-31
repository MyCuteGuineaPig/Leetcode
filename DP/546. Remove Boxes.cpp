/*
546. Remove Boxes

Given several boxes with different colors represented by different positive numbers. 
You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.

Example 1:
Input:

[1, 3, 2, 2, 2, 3, 4, 3, 1]
Output:
23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
----> [1, 3, 3, 3, 1] (1*1=1 points) 
----> [1, 1] (3*3=9 points) 
----> [] (2*2=4 points)
Note: The number of boxes n would not exceed 100.
*/


/*
dp[i][j][k] 代表从boxes[i:j] 之后k个与boxes[j] 一样color ball，所得最大的count数



the memoization matrix to be memo[l][r][k], the largest number we can get using lth to rth (inclusive) 
boxes with k same colored boxes as rth box appended at the end. Example, 
memo[l][r][3] represents the solution for this setting: [b_l, ..., b_r, A,A,A] with b_r==A.

The transition function is to find the maximum among all b_i==b_r for i=l,...,r-1:
memo[l][r][k] = max(memo[l][r][k], memo[l][i][k+1] + memo[i+1][r-1][0])

[1, 3, 2, 2, 2, 3, 4, 3, 1] 
比如当j = 7, 与pos = 1, 5 都是3, call recursion, 
call dfs(i=0, j = 1, k = 1)
call dfs(i=0, j= 5, k = 1) 但是这里面还有recusion，因为j=5 和pos = 1 又相同， call dfs(i=0, j= 1, k = 2)  


*/

int dp[102][102][102];
class Solutiaon {
public:
    int c[102], len[102];
    int removeBoxes(vector<int>& boxes) {
        memset(c,0,sizeof(c));
        memset(len,0,sizeof(len));
        memset(dp,-1,sizeof(dp));
        int n = 0;
        for(int i = 0; i<boxes.size(); i++){
            if(i!=0 && boxes[i]==c[n]){
                len[n]++;
            }
            else{
                c[++n] = boxes[i];
                len[n] = 1;
            }
        }
 
        return dfs(1,n, 0);
    }
    
    int dfs(int i, int j, int k){
        if(dp[i][j][k]!=-1)
            return dp[i][j][k];
        if(i>j)
            return 0;
        dp[i][j][k] = dfs(i, j-1, 0) + (len[j]+k)*(len[j]+k);
        for(int pos = i; pos<j; pos++){
            if(c[j] == c[pos])
                dp[i][j][k] = max(dp[i][j][k], dfs(i,pos,k+len[j])+dfs(pos+1, j-1, 0));
        }
        return dp[i][j][k];
    }
};


const int maxn = 105;
int d[maxn][maxn][maxn];

class Solution {
private:
    int c[maxn], len[maxn];
public:
    int dfs(int i, int j, int k) {
        if (d[i][j][k] != -1) {
            cout<<"-1r "<<i<<" j "<<j<<" k "<<k<<" d "<<d[i][j][k]<<endl;
        
            return d[i][j][k];
        }
        if (i > j) {
            cout<<"i>j "<<i<<" j "<<j<<" k "<<k<<endl;
        
            return 0;
        }
        cout<<"in "<<i<<" j "<<j<<" k "<<k<<endl;
        
        d[i][j][k] = dfs(i, j - 1, 0) + (len[j] + k) * (len[j] + k);
        cout<<" afdfs "<<"i  "<<i<<" j "<<j<<" k "<<k<<" lenj "<<len[j]<<" l+k "<<len[j] + k<<" dp "<<d[i][j][k] <<endl;
        for (int pos = i; pos < j; pos++) {
            if (c[pos] == c[j]) {
                cout<<" equal "<<" i "<<i<<" j "<<j<<" k "<<k<<" pos "<<pos<<endl;
                int before = dfs(i, pos, len[j] + k);
                int after = dfs(pos + 1, j - 1, 0);
                d[i][j][k] = max(d[i][j][k], before + after);
                cout<<" before "<<before<<" aftter "<<after<<" i "<<" i "<<i<<" j "<<j<<" k "<<k<<" dp "<<d[i][j][k] <<endl;
        
            }
        }
        return d[i][j][k];
    }

    int removeBoxes(vector<int>& boxes) {
        int n = 0;
        memset(c, 0, sizeof(c));
        memset(len, 0, sizeof(len));
        memset(d, -1, sizeof(d));
        for (int i = 0; i < boxes.size(); i++) {
            if (i == 0 || boxes[i] != boxes[i - 1]) c[++n] = boxes[i], len[n] = 1;
            else len[n]++;
        }
        for(int i =0 ;i<=n; i++){
            cout<<c[i]<<"  ";
        }
        cout<<endl;
        for(int i =0 ;i<=n; i++){
            cout<<len[i]<<"  ";
        }
        cout<<endl;
        return dfs(1, n, 0);
    }
};



class Solution {
public:
    int n;
    vector<vector<vector<int>>>dp;
    int removeBoxes(vector<int>& boxes) {
        n = boxes.size();
        dp.resize(n, vector<vector<int>>(n, vector<int>(n)));
        return helper(boxes, 0, n-1, 0);
    }
    
    int helper(const vector<int>& boxes, int i, int j, int k){
        if(i>j) return 0;
        if(dp[i][j][k]>0)
            return dp[i][j][k];
        while(i<j && boxes[j-1] == boxes[j]){ k++; j--;}
        dp[i][j][k] = helper(boxes, i, j-1, 0)+(k+1)*(k+1);
        for(int x = i; x<j; x++){
            if(boxes[j] == boxes[x]){
                dp[i][j][k] = max(dp[i][j][k],helper(boxes, i, x, k+1)+helper(boxes, x+1, j-1, 0));
            }
        }
        return dp[i][j][k];
    }
    
};