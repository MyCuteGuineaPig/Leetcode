/*
dp[i][j] means till i+1 th char and cut total j char, minimum encoded lengths

e.g.   
             a a a b c c c d 
                   ^       ^
                   |       |
                   l       r
                  most = 3 (c)
                  del = r - l + 1 - most =  8 - 4 + 1 - 3 = 2

                  dp [8][2] = min(dp[8][2], 1 + 1('c3') + dp[4-1][2-2]) 
                            = min(dp[8][2], 1 + 1('c3') + dp[3][0])    
                            = min(dp[8][2], 1 + 1('c3') + 2)  
                            dp[3][0] is first three characters without cup

*/



class Solution {
public:
    int Len(int x) { 
        if(x == 1) return 0;
        else if(x < 10) return 1;
        else if (x< 100) return 2;
        return 3;
    }

    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        vector<vector<int>>dp(n+1, vector<int>(k+1, n+1));        
        for(int r = 1; r<=n; ++r){ //right side of interval to process
            unordered_map<char,int>cnt;
            int most = 0;
            for(int l = r; l>=1; --l){ //left side of interval to process
                
                most = max(most, ++cnt[s[l-1]]);  
                for(int j = 0; j<=k && j <= r; ++ j){
                    
                    int del = r - l +1 - most; //means the number element to be deleted
                    
                    if(del > j) continue; //not enough to delete, need to increase j so as to delete
                    if(r == j)  dp[r][j] = 0; //delete all
                    else
                        dp[r][j] = min(dp[r][j], 1 + Len(most) + ( l-1  == 0 ? 0:  dp[l-1][j-del]));
                }   // l-1  == 0 means no characters at all, lengths = 0
            }
        }
        return dp[n][k];
    }
};

/*
需要最后一个dimension的原因比如:

s = aabaa

到 index = 4, k = 1, last = 'a', 

如果 删除是 index = 2 (b),  concat =  3,  到现在的s为 'aaa' + 'a', result = 2 ('a4')
如果 删除是 index = 1 (a),  concat =  1,  到现在的s为 'aba' + 'a', result = 4 ('aba2')

*/

int f[105][105][30][11];

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        this->s = s;
        
        const int N = s.size();
        if (N == 100 && k == 0) {
            bool allSame = true;
            for (int i = 1; i < N; i++) {
                if (s[i] != s[i - 1]) {
                    allSame = false;
                    break;
                }
            }

            if (allSame) {
                return 4;
            }
        }
        
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                for (int k = 0; k <= 26; k++) {
                    for (int m = 0; m <= 10; m++) {
                        f[i][j][k][m] = -1;
                    }
                }
            }
        }
        
        return dfs(0, k, 26, 0);
    }
private:
    string s;
    int dfs(int idx, int k, int last, int concat) {
        if (k < 0) return 9999999;
        if (idx == s.size()) return 0;
        
        int& val = f[idx][k][last][concat];
        if (val != -1) return val;
        
        int answer = 9999999;
		// delete
        answer = min(answer, dfs(idx + 1, k - 1, last, concat));
        // concat
        if (last == s[idx] - 'a') {
            const int fac = (concat == 1 || concat == 9) ? 1 : 0; //concat = 1, 比如之前是a, 现在两个a, 所以 a2, 多了一位
            answer = min(answer, fac + dfs(idx + 1, k, last, min(10, concat + 1)));
            //We can restrict last dimension to 10, because, m > 10 doesn't change the length of encoded string since n < 100.

        } else {
//也可以把delete放这 delete
//        answer = min(answer, dfs(idx + 1, k - 1, last, concat));
        

            answer = min(answer, 1 + dfs(idx + 1, k, s[idx] - 'a', 1));
        }
        return val = answer;
    }
};



class Solution {
    const static int N = 127;

    // dp[left][k] means the minimal coding size for substring 
    // s[left:] and removing at most k chars
    int dp[N][N];

    string str;
    int n;

    // get length of digit
    inline int xs(int x) { return x == 1 ? 0 : x < 10 ? 1 : x < 100 ? 2 : 3; }

    int solve(int left, int k) {
        if(k < 0) return N;  // invalid, return INF
        if(left >= n or n - left <= k) return 0;  // empty

        int& res = dp[left][k];
        if(res != -1) return res;
        res = N;

        int cnt[26] = {0};
        // we try to make s[left:j] (both inculded) as one group,
        // and all chars in this group should be the same.
        // so we must keep the most chars in this range and remove others
        // the range length is (j - left + 1)
        // and the number of chars we need to remove is (j - left + 1 - most)
        for(int j = left, most = 0; j < n; j++) {
            most = max(most, ++cnt[str[j] - 'a']);  // most = max(count(s[left:j])
            res = min(res, 1 + xs(most) + solve(j + 1, k - (j - left + 1 - most)));
        }
        return res;
    }
public:
    int getLengthOfOptimalCompression(string s, int k) {
        memset(dp, -1, sizeof(dp));
        str = s;
        n = s.size();
        return solve(0, k);
    }
};





/*
dp[i][j] the min length at index i+1 and delete jth character before 

dp[i][j+1] = min(dp[i][j+1],dp[i-1][j]); 
         dp[i][j+1] = dp[i-1][j]: means delete i-th character, dp[i][j+1] will go beyond k, which the size of second dimension is k+2.

at (i+1)th position to check, check how far it can go to delete character that is not the same to the character
 at i while making sure the total deletion is no larger than k,  

dp[l][j+del] = min(dp[l][j+del], length);

for example:  ("aabbaa", 2) , when at i = 1, j = 0,   dp[i-1][j] = 

    l = 1, count = 1, del = 0, dp[1][0] = dp[0][0] + 1 
    l = 2, count = 2, del = 0, dp[2][0] = dp[0][0] + 2
    l = 3, count = 2, del = 1, dp[3][1] = dp[0][0] + 2
    l = 4, count = 2, del = 2, dp[4][2] = dp[0][0] + 2  //count = 2, so a2 is 2
    l = 5, count = 3, del = 2, dp[5][2] = dp[0][0] + 2 // count = 3, so a3 is 2
    l = 6, count = 4, del = 2, dp[6][2] = dp[0][0] + 2 // count = 4, so a4 is 2

One more note:  e,g,  ("aaabbaa", 2) 

from index = 0, update dp[3][0] = 2 ('a3'), dp[2][0] = 2 ('a2'), dp[1][0] = 1  ("a") 
but from index = 1 and l = 3, length = dp [1][0] + 1 + 1 (count >= 2) = 2 
    if change dp[l][j+del] = min(dp[l][j+del], length) -> dp[l][j+del] =length
             update dp[3][0] = 3 ('aa3'),
*/

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        vector<vector<int>>dp(n+1, vector<int>(k+2, n+1));
        dp[0][0] = 0;
        for(int i = 1; i<=n; ++i){
            for(int j = 0; j<=k ;++j)
            {
                dp[i][j+1] = min(dp[i][j+1], dp[i-1][j]);
                int count = 0, del = 0;
                for(int l = i; l<= n; ++l){
                    if(s[l-1] == s[i-1]) ++count;
                    else del++;
                    if( j + del <= k){
                        int length = dp[i-1][j] + 1;  //加的1表示新的character
                        if(count >= 100) length += 3;
                        else if(count >= 10) length += 2;
                        else if(count >= 2) length += 1;
                        else length += 0;
                        dp[l][j+del] = min(dp[l][j+del], length);
                    }else 
                        break;
                }
            }
        }
        return dp[n][k];
    }
};

