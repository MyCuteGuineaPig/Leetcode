/*
         s1 s e a 
     s2  0  1 2 3 
     e   1  2 1 2
     a   2  3 2 1  
     t   3  4 3 2
 
    如果s[i]!=s[j]  dp[i][j] = 1+min(dp[i-1][j], dp[i][j-1]) =  dp[i][j-1] + 1 横向移动，代表删除的是s1
    如果s[i]!=s[j]  dp[i][j] = 1+min(dp[i-1][j], dp[i][j-1]) =  dp[i-1][j] + 1 纵向移动，代表删除的是s2

*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<vector<int>>dp(n1+1, vector<int>(n2+1));
        for(int i = 0; i<=n1; ++i)
            dp[i][0] = i;
        for(int j = 0; j<=n2; ++j)
            dp[0][j] = j;
        
        for(int i = 1; i<=n1; ++i){
            for(int j = 1; j<=n2; ++j){
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1])+1;
            }
        }
        return dp[n1][n2];
    }
};

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<vector<int>>dp(2, vector<int>(n2+1,INT_MAX));
        for(int i = 0; i<=n1; i++)
            for(int j = 0, k = i%2; j<=n2; j++)
                dp[k][j] =  i == 0 || j ==0 ? (i == 0? j: i) : word1[i-1] == word2[j-1] ? dp[k^1][j-1]: 1+min(dp[k^1][j], dp[k][j-1]); 
        return dp[n1%2][n2];
    }
};


class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>>dp(word1.size()+1, vector<int>(word2.size()+1,-1));
        return topDown(dp, word1,word2, word1.size(), word2.size());
    }
    
    int topDown(vector<vector<int>>&dp, const string& word1, const string& word2, int i , int j){
        if(dp[i][j] >= 0)
            return dp[i][j];
        if(i == 0 || j== 0)
            return i == 0 ? j: i;
        if(word1[i-1] == word2[j-1])
            dp[i][j] = topDown(dp, word1, word2, i-1, j-1);
        else
            dp[i][j] = 1 + min(topDown(dp, word1, word2, i-1,j), topDown(dp, word1, word2, i, j-1));
           
        return dp[i][j];
    }
};

//TopDown
//i == len(A) or j == len(B), one of the strings is empty, so the answer is just the sum of the remaining lengths.
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>>dp(word1.size()+1, vector<int>(word2.size()+1,-1));
        return topDown(dp, word1,word2, 0, 0);
    }
    
    int topDown(vector<vector<int>>&dp, const string& word1, const string& word2, int i , int j){
        if(dp[i][j] >= 0)
            return dp[i][j];
        if(i == word1.size() || j== word2.size())
            return word1.size() + word2.size() -i - j;
        if(word1[i] == word2[j])
            dp[i][j] = topDown(dp, word1, word2, i+1, j+1);
        else
            dp[i][j] = 1 + min(topDown(dp, word1, word2, i+1,j), topDown(dp, word1, word2, i, j+1));
        return dp[i][j];
    }
};


//(Longest Common Subsequence)
/*
To make them identical, just find the longest common subsequence. 
The rest of the characters have to be deleted from the both the strings, 
    which does not belong to longest common subsequence.

 */

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>>dp(word1.size()+1, vector<int>(word2.size()+1));
        for(int i = 1; i <= word1.size(); i++)
            for(int j = 1; j <= word2.size(); j++) 
                dp[i][j] = word1[i-1] == word2[j-1] ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);
        return word1.size() + word2.size() - 2 * dp[word1.size()][word2.size()];
    }
};