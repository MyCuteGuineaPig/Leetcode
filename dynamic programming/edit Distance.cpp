/*

10 Edit Distance

https://leetcode.com/problems/edit-distance/description/

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character


*/


class Solution {
public:
	int minn(int x, int y, int z){
		return min(min(x,y),z);
	}


    int minDistance(string word1, string word2) {
        vector<vector<int>>dp(word1.length()+1,vector<int>(word2.length()+1,0));
		for(int i = 1; i<=word1.length();i++){
			dp[i][0] = i;
		}
		for(int j = 1; j<=word2.length();j++){
			dp[0][j] = j;
		}
		for(int i = 1; i<=word1.length(); i++){
			for(int j = 1; j<=word2.length();j++){
				if(word1[i-1] == word2[j-1]){
					dp[i][j] = dp[i-1][j-1];
				}
				else{
                    //cout<<"i "<<i<<" j "<<j << " word1[i-1] "<<word1[i-1]<< " word2[j-1] "<<word2[j-1]<<endl;
                    //cout<<"replace substr word1 "<<word1.substr(0,i-1)<<" word2 "<<word2.substr(0,j-1)<<" move dp["<<i-1<<"]["<<j-1<<"] "<<dp[i-1][j-1]<<endl;
                    //cout<<" insert substr word1 "<<word1.substr(0,i-1)<<" word2 "<<word2.substr(0,j)<<" move  dp["<<i-1<<"]["<<j<<"] "<<dp[i-1][j]<<endl;
                    //cout<<" delete  substr word1 "<<word1.substr(0,i)<<" word2 "<<word2.substr(0,j-1)<<" move dp["<<i<<"]["<<j-1<<"] "<<dp[i][j-1] << endl;
					dp[i][j] = 1 + min(dp[i-1][j-1],dp[i][j-1],dp[i-1][j]);
				}
			}
		}
        return dp[word1.length()][word2.length()];
    }
};