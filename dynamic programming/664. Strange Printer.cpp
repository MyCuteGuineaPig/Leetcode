/*
664. Strange Printer
There is a strange printer with the following two special requirements:

The printer can only print a sequence of the same character each time.
At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.
Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

Example 1:
Input: "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
Example 2:
Input: "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
Hint: Length of the given string will not exceed 100.

*/

/*

        a  b  c  a  b  c

    a   1  2  3  3  4  5
    b      1  2  3  3  4 
    c         1  2  3  3 
    a            1  2  3 
    b               1  2
    c                  1

        a  a  a  b  b  b

    a   1  1  1  2     
    a      1  1  2      
    a         1  2     1 
    b            1  1  1 
    b               1  1
    b                  1




*/

class Solution {
public:
    int strangePrinter(string s) {
        if(s.size()==0) return 0;
        int size = s.size();
        vector<vector<int>>dp(size, vector<int>(size, INT_MAX)); dp[0][0] = 1;
        for(int k = 1; k<size; k++){
           for(int i = k; i<size; i++){
               dp[i][i] = 1;
               if(s[i] == s[i-k])
                   dp[i-k][i] = dp[i-k][i-1];
               else{
                   for(int j = i-k; j<i; j++){
                        dp[i-k][i] = min(dp[i-k][i], dp[i-k][j]+dp[j+1][i]);
                   }   
               }
           }
        }/*
        for(auto i: dp){
            for(auto j: i)
                cout<<j<<"  ";
            cout<<endl;
        }*/
        return dp[0][size-1];
    }
};


class Solution {
public:
    int strangePrinter(string s) {
        if(s.size()==0) return 0;
        int size = s.size();
        vector<vector<int>>dp(size, vector<int>(size, 1)); 
        for(int k = 1; k<size; k++){
           for(int i = k; i<size; i++){
               if(s[i] == s[i-k])
                   dp[i-k][i] = dp[i-k][i-1];
               else{
                   dp[i-k][i] = INT_MAX;
                   for(int j = i-k; j<i; j++){
                        dp[i-k][i] = min(dp[i-k][i], dp[i-k][j]+dp[j+1][i]);
                   }   
               }
           }
        }
        return dp[0][size-1];
    }
};


/*


        a  b  c  a  b  c

    a   1  2  3  3  4  5
    b      1  2  3  3  4 
    c         1  2  3  3 
    a            1  2  3 
    b               1  2
    c                  1


        a  a  a  b  b  b

    a   1  1  1  2     
    a      1  1  2      
    a         1  2     1 
    b            1  1  1 
    b               1  1
    b                  1

*/


class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        if(n==0) return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int i=n-1;i>=0;i--){
            for(int j=i;j<n;j++){
                dp[i][j]=(i==j)?1:(1+dp[i+1][j]);
                for(int k=i+1;k<=j;k++){
                    if(s[i]==s[k])dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j]);
                }
            }
                
        }
        return dp[0][n-1];
    }
};