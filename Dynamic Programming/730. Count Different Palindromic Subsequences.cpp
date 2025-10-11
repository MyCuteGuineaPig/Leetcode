

/**
Method 2:

当 s[i] != s[j]: 
    dp[i][j] = dp[i][j] = dp[i][j-1 ] + dp[i+1][j]  - dp[i+1][j-1]

当 s[i] == s[j]: get complext
    



 */




class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int len = S.size();
        vector<vector<int>>dp(len, vector<int>(len));
        
        for(int i = 0; i < len; i++){
            dp[i][i] = 1;   // Consider the test case "a", "b" "c"...
        }

        for(int distance = 1; distance < len; distance++){
            for(int i = 0; i < len - distance; i++){
                int j = i + distance;
                if(S[i] == S[j]){
                    int low = i + 1;
                    int high = j - 1;

              /* Variable low and high here are used to get rid of the duplicate*/

                    while(low <= high && S[low] != S[j]){
                        low++;
                    }
                    while(low <= high && S[high] != S[j]){
                        high--;
                    }
                    if(low > high){
                        // consider the string from i to j is "a...a" "a...a"... 区间内没有多余的'a', 只有左右两侧有a
                       /* eg:  "aba" while i = 0 and j = 2:  dp[1][1] = 1 {"b"}, 
                         why dp[i + 1][j  - 1] * 2 counted is that we count dp[i + 1][j - 1] one time as {"b"}, 
                         and additional time as {"aba"}. The reason why 2 counted is that we also count {"a", "aa"}. 
                         So totally dp[i][j] record the palindrome: {"a", "b", "aa", "aba"}. 
                         */ 

                        dp[i][j] = dp[i + 1][j - 1] * 2 + 2;  
                    } 
                    else if(low == high){
                        // consider the string from i to j is "a...a...a" where there is only one character 'a' inside the leftmost and rightmost 'a'
                       /* eg:  "aaa" while i = 0 and j = 2: the dp[i + 1][j - 1] records the palindrome {"a"}.  
                         the reason why dp[i + 1][j  - 1] * 2 counted is that we count dp[i + 1][j - 1] one time as {"a"}, 
                         and additional time as {"aaa"}. the reason why 1 counted is that 
                         we also count {"aa"} that the first 'a' come from index i and the second come from index j. So totally dp[i][j] records {"a", "aa", "aaa"}
                         dp[i][low] 已经记录了 {"a", "aa"}
                        */
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 1;  
                    }
                    else{
                        // consider the string from i to j is "a...a...a... a" where there are at least two character 'a' close to leftmost and rightmost 'a'
                       /* eg: "aacaa" while i = 0 and j = 4: the dp[i + 1][j - 1] records the palindrome {"a",  "c", "aa", "aca"}. 
                          the reason why dp[i + 1][j  - 1] * 2 counted is that we count dp[i + 1][j - 1] one time as {"a",  "c", "aa", "aca"}, 
                          and additional time as {"aaa",  "aca", "aaaa", "aacaa"}.  Now there is duplicate :  {"aca"}, 
                          which is removed by deduce dp[low + 1][high - 1]. So totally dp[i][j] record {"a",  "c", "aa", "aca", "aaa", "aaaa", "aacaa"}
                          */
                        dp[i][j] = dp[i + 1][j - 1] * 2 - dp[low + 1][high - 1]; 
                    }
                }
                else{
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];  //s.charAt(i) != s.charAt(j)
                }
                dp[i][j] = dp[i][j] < 0 ? dp[i][j] + 1000000007 : dp[i][j] % 1000000007;
            }
        }

        return dp[0][len - 1];
    }
};


/*
难点: deal with duplicate

dp[len][i][x] 存的是在index i 往后, 头尾都是x, 长度为len的Palindromic 
不会有重复因为:  
    For each window, this method count palindromes of the form a...a, b...b, c...c, d...d, and 
    the strings in different groups are distinct. 
    The strings within each group are guaranteed to be distinct by recursing into the inside subwindows.

比如 bccb， 不会算两次bcb,

dp[4][0]['b'] = 2 + dp[2][1]['c'] + dp[2][1]['b'] = 2 + 2 + 0 = 4 
dp[2][1]['c']组成的是 c, cc
dp[4][0]['b']组成的是 bcb, bccb 


比如 bccb：
    dp[4][0]['b'] 表示的palindromes 是 bxxb:  b,  bb, bcb, bccb
       

Let dp[len][i][x] be the number of distinct palindromes of the subtring starting at i of length len, 
where the first (and last) character is x. 
The DP formula is simple :

- If s[i] != x,  
    then dp[len][i][x] = dp[len-1][i+1][x] (ignoring the first character in this window)
    比如  a bc
        s[0] = a != 'b',  那么dp[2][0]['b'] = dp[1][1]['b']

- If s[i+len-1] != x 
    then dp[len][i][x] = dp[len-1][i][x] (ignoring the last character in this window)
    比如 bbc:
        s[2] = 'c' != 'b',  dp[2][0]['b'] = dp[1][0]['b']

-  If both the first and last characters are x, then we need to count the number of distinct palindromes 
    in the sub-window from i+1 to i + len -2.
        dp[len][i][x] = 2;
        for(int y = 0; y<4; y++)
            dp[len][i][x] += dp[len-2][i+1][y])   


    e.g. 'bccb'
len 1    dp[0][0]['b'] = 1, dp[0][1]['c'] = 1, dp[0][2]['c'] = 1, dp[0][3]['b'] = 1

len 2    dp[1][0]['b'] = dp[0][0]['b'] = 1 (因为 s[1] != 'b')    dp[1][0]['c'] =  dp[0][1]['c'] = 1 (因为s[0] != 'c')
         dp[1][1]['b'] = 0                                     dp[1][1]['c'] = 2,                     
         dp[1][2]['b'] = dp[0][3]['b'] = 1,                    dp[1][2]['c'] = dp[0][2]['c'] = 1 
         
len 3:  dp[2][0]['b'] = dp[1][0]['b'] = 1 (s[2] != 'b')      dp[2][0]['c'] = dp[1][1]['c'] = 2 (s[0] != 'c')
        dp[2][1]['b'] = dp[1][2]['b'] = 1 (S[1] != 'b')      dp[2][1]['c'] = dp[1][1]['c'] = 2 

len 4:  dp[3][0]['b'] = 2 + dp[1][1]['b'] + dp[1][1]['c'] = 4 
        dp[3][0]['c'] = dp[2][1]['c'] = 2 

*/

class Solution {
public:
    int countPalindromicSubsequences(string S) {
        const long long M = 1e9 + 7;
        int n = S.size();
        long long dp[3][n][4];
        for(int len = 0; len<n; len++){
            for(int i = 0; i+len<n;i++){
                for(int x = 0; x<4; x++){
                    int j = i+len;
                    dp[2][i][x] = 0;
                    char c = 'a'+x;
                    if(len == 0) dp[2][i][x] = S[i] == c;
                    else{
                        if(S[i]!=c) dp[2][i][x] = dp[1][i+1][x]; //len>=1 i+1<n
                        else if(S[j]!=c) dp[2][i][x] = dp[1][i][x];
                        else{
                            dp[2][i][x] = 2; // 如果 [i+1, j-1]不是回形字, 比如bcab, bb是2个Palindromic，bcb && bab
                                            //如果 [i+1, j-1]是回形字, 比如bccb 外层两个b 组成新的 bccb, bb
                            if(len>=2) for(int y = 0; y<4; y++)
                                dp[2][i][x] = (dp[2][i][x]+dp[0][i+1][y])%M;
                        }
                    } 
                }   
            }
            for(int i = 0; i<2;i++) for(int j = 0; j<n; j++) for(int x = 0; x<4; x++)
                dp[i][j][x] = dp[i+1][j][x];
            
        }
        return accumulate(dp[2][0],dp[2][0]+4,0,[&](auto a, auto b){return (a+b)%M;});
    }
};


//Method 3
/*

Complexity Analysis

Time Complexity: O(N^2*alphabet), where N is length of S and alphabet is 4 (a,b,c,d).

Space Complexity:O(N^2*alphabet)

不会有重复：
比如abaaba,   it will count a, aa first and then any inner a's would be a part of the envelope outside 
Take another example aabaa, it will get a, aa, 
then the "aba" it gets next time would be from the two a's outside and not the ones inside , 
the ones inside will only contribute to the bigger palindrome, aabaa or aaaa

比如 abaaba,
    外层b 返回4,  b, bb, bab, baab 
    外层a, 返回8

    遇到S[start] == S[end], dp(start+1, end-1), 所以不会出现start = 0, end = 2 =, aba 的情况

aba xxx aba, 外层a收尾一样, 到 ba xxx ab, 外层 b收尾一样, a xxx a, 所以不会出现 aba xxx 的情况

 */

//Top-Down
int memo[1001][1001][4];
class Solution {
public:
	string S;
	int MOD = 1000000007;

	int dp(int start,int end,int alpha){
		//base case
		if(start>end)return 0;
		if(start==end){
			if(S[start] == (alpha+'a') )return 1;
			return 0;
		}
		
		if(memo[start][end][alpha]!=-1)return memo[start][end][alpha];
		
		int dev=0;
		if(S[start]==S[end] && S[start]==(alpha+'a')){
			dev=2;
			for(int i=0;i<4;i++)
				dev=(dev + dp(start+1,end-1,i) )%MOD;
		}else{
			dev= (dev + dp(start,end-1,alpha))%MOD;
			dev= (dev + dp(start+1,end,alpha))%MOD;
			dev= (dev - dp(start+1,end-1,alpha))%MOD;
			if(dev<0)dev+=MOD;
		}
		
		memo[start][end][alpha]=dev;
		return dev;
	}
	
	int countPalindromicSubsequences(string _S) {
		S=_S;
		memset(memo,-1,sizeof(memo));
		int ans=0;
		
		for(int i=0;i<4;i++)
			ans= (ans + dp(0, S.size()-1, i))%MOD;
		
		return ans;        
	}
};


// Bottom-up 
class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int M = 1000000007;
        int n = S.size();
        
        vector<vector<int>>dp(n, vector<int>(n));
        for (int len = 1; len <= n; len++) {
            for (int start = 0; start + len - 1 < n; start++) {
                int end = start + len - 1;
                int res = 0;
                for (int i = 0; i < 4; i++) {
                    int first = start,  last = end;
                    while(first <= last && S[first] != 'a' + i)
                        ++first;
                    while(first <= last && S[last] != 'a' + i)
                        --last;

                    if(first == last)
                        res += 1;
                    else if(first < last) {
                        res +=2;
                        if (first + 1 < last) { // 比如 bcb,  +dp[1][1]
                            res = (res + dp[first+1][last-1]) % M;
                        }
                    }
                }
                dp[start][end] = res;
            }
        }
        
        return dp[0][n-1];
    }
};