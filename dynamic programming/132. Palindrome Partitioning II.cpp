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
        vector<int>d(s.size(),0);
        vector<vector<bool>>ispal(s.size(),vector<bool>(s.size(),false));
        for(int i = s.size()-1;i>=0; i--){
            d[i] = s.size()-i-1;
            cout<<"i "<<i<<endl;
            for(int j = i; j<s.size();j++){
                cout<<"substr "<<s.substr(i,j-i+1)<<"  d[i] "<<d[i];
                if(s[i] == s[j] && (j-i<2 || ispal[i+1][j-1])){
                    if (i+1<s.size() && j-1>=0)
                        cout<<" ispal["<<i+1<<"]["<<j-1<<"] "<<ispal[i+1][j-1]<<endl;
                    else cout <<endl;
                    ispal[i][j] = true;
                    if(j == s.size()-1){
                        d[i] = 0; 
                        cout<<" d[i] "<<d[i]<<endl;
                    }
                    else if(d[j+1]+1<d[i]){
                         d[i]=d[j+1]+1;
                         cout<<" d[j+1] "<<d[j+1]<<endl;
                    }
                       
                }
            }
            
        }
        return d[0];
    }
};


