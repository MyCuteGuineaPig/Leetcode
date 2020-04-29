/*
132. Palindrome Partitioning II
https://leetcode.com/problems/palindrome-partitioning-ii/description/

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.


*/


/*
Calculate and maintain 2 DP states:

pal[i][j] , which is whether s[i..j] forms a pal
d[i], which is the minCut for s[i..n-1]

Once we comes to a pal[i][j]==true:

    if j==n-1, the string s[i..n-1] is a Pal, minCut is 0, d[i]=0;
    else: the current cut num (first cut s[i..j] and then cut the rest
        s[j+1...n-1]) is 1+d[j+1], compare it to the exisiting minCut num
    d[i], repalce if smaller.
d[0] is the answer.

*/

class Solution {
public:
    int minCut(string s) {
        int n = s.size()-1;
        vector<int>dp(n+1,0);
        vector<vector<bool>>ispal(n+1,vector<bool>(n+1,false));
        for(int i = 0; i<=n; i++){
            dp[i] = i; //初始化dp[i] 从i 到 n 把每一个char，单独拿出来，肯定都是pal
            for(int j = 0; j<=i; j++){
                if(s[i] == s[j] && (i-j<2 || ispal[j+1][i-1]))
                {
                    
                    ispal[j][i] = true;
                    if(j == 0){ //从开始到尾都是pal{
                        dp[i] = 0;
                    }  
                    else if(dp[j-1] + 1 < dp[i]){
                         dp[i] = dp[j-1]+1;
                    }
                       
                }
            }
         }
        return dp[n];
    }
};


class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int>dp(n+1,0);
        vector<vector<int>>ispal(n,vector<int>(n,0)); // represent substring is Palindrome from i to j 
        dp[0] = -1;
        for(int i = 0; i<n; i++){
            dp[i+1] = i;
            for(int j = 0; j<=i;j++){
                if(s[i] == s[j] && (i-j<=1 || ispal[i-1][j+1])){
                    ispal[i][j] = 1;
                    dp[i+1] = min(dp[i+1],dp[j]+1);
                }
            }
        }
        return dp[n];
    }
};


/*
The Manancher-like solution scan the array from left to right (for i loop) and only check those sub-strings centered at s[i]; 
once a non-palindrome string is found, it will stop and move to i+1. 
Same as the DP solution, minCUTS[i] is used to save the minimum cuts for s[0:i-1].
 For each i, we do two for loops (for j loop) to check if the substrings s[i-j … i+j] (odd-length substring) 
 and s[i-j-1… i+j] (even-length substring) are palindrome. 
 By increasing j from 0, we can find all the palindrome sub-strings centered at i and update minCUTS accordingly.
  Once we meet one non-palindrome sub-string, we stop for-j loop since we know there no further palindrome substring centered at i. 
  This helps us avoid unnecessary palindrome substring checks, as we did in the DP algorithm. Therefore, this version is faster.

*/

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int>dp(n+1,0); //dp[i] 表示 s[0:i-1] 组要几个cut 
        for(int i = 0; i<=n; i++)
            dp[i] = i-1;  //重点是 dp[0] = -1 所以遇到Palindrome, 来一刀就是0
        for(int i = 0; i<n; i++){
            for(int j = 0; i-j>=0 && i+j<n && s[i-j] == s[i+j];j++)
                dp[i+j+1] = min(dp[i+j+1],dp[i-j]+1);
                
            for(int j = 0; i-j-1>=0 && i+j<n && s[i-j-1] == s[i+j];j++)
                dp[i+j+1] = min(dp[i+j+1],dp[i-j-1]+1);

            cout<<"dp[i+1] "<<dp[i+1]<<endl;
        }
        return dp[n];
    }
};




#BFS, 从一个
class Solution {
public:
	int minCut(string s) {
		queue<int> node;
		node.push(0);
		int cuts = 0;
		//bfs
		vector<bool> visited(s.size(), false);
		while (true){
			queue<int> tmp;
			while (!node.empty()){
				int cur = node.front();
				node.pop();
				for (int i = s.size() - 1; i >= cur; i--){
					if (visited[i]==false&&ispal(s, cur, i)){
						if (i == s.size() - 1)
							return cuts;
						tmp.push(i+1); // cur:i form a Palindrome, so push i+1, 
					}
				}
				visited[cur] = true;
			}
			cuts++;
			node = tmp;
		}
	}

	bool ispal(string& s, int pre, int post){
		while (pre < post){
			if (s[pre++] != s[post--])
				return false;
		}
		return true;
	}
};