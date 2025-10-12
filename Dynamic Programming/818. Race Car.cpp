/*

if i=2^n-1, dp[i]=n, 

else 2^(n-1)-1<i<2^n-1, 两种方法到达i,
   - 先用n 步到 2^n-1 first, change direction + 1(R), total = n + 1 steps
     剩下的步数等于 dp[2^n-1-i]

   -  先用 n-1 A 到 2^(n-1)-1 first, then R to change the direction,
      再用 m 个 A go backward (m 个A,走了2^(n-1)-1), 再用 R change direction again to move forward, 
      by here there are n-1+2+m=n+m+1 operations (n-1 A, two R, m A) , 
      current position is 2^(n-1)-1-(2^m-1)=2^(n-1)-2^m, 
      剩下的步数等于 dp[i-(2^(n-1)-1)+(2^m-1)]=dp[i-2^(n-1)+2^m)].



dp[i] = min(n + 1 + dp[(1 << n)-1 - i], n-1+2+k+dp[i-((1 << (n-1)) - (1 << k))] for j in [0,n] ), 
   -  n + 1 + dp[(1 << n)-1 - i]是先到2^n-1的用n步, +1是做reverse(停)
   -  n-1+2+k+dp\[i-((1 << (n-1)) - (1 << k))] 是先到之前2^(n-1)-1的点, 接着+1做reverse(停),然后往回走(2^k-1)点，+1做reverse(停)，再从那个点到点i


         0     1  2  3  4  5  6  7  8  9  10  11  12   13  14   15
         0     1  4 |2| 5  7  5 |3| 6  8                9   6  |4|
speeed         2  1  4    -2 -1  6     
  
       0  1  3   3   3   4
speed  1  2  4  -1   1   2
          A  A  R    R   A

    9从6过来

*/

/*
Bottom-up DP:
*/

class Solution {
public:
    int racecar(int target) {
    vector<int>dp(target + 1);
    
    for (int i = 1; i <= target; i++) {
        dp[i] = numeric_limits<int>::max();
        
        int j = 1, j_pos = 1;  //前进m个A 到 j_pos, 再后退 q 个 A 到 q_pos
        
        for (; j_pos < i; j_pos = (1 << ++j) - 1) {
            for (int q = 0, q_pos = 0; q_pos < j_pos; q_pos = (1 << ++q) - 1) {
                /*
                需要q = 0 开始, 比如 到4, 需要5步 
                先走1步，  j = 1, j_pos = 1,   +1
                停1步, speed = -1             +1  
                再停1步, speed = 1,            +1  -> q = 0
                再走3pos, 需要2 steps         +2
                                    total = 5 steps
                 */
                dp[i] = min(dp[i], j + 1 + q + 1 + dp[i - (j_pos - q_pos)]);
            }
        }
        
        dp[i] = min(dp[i], j + (i == j_pos ? 0 : 1 + dp[j_pos - i]));
    }
    
    return dp[target];
    }
};


class Solution {
public:
    int racecar(int target) {
        vector<int>dp(target+1, INT_MAX);
        dp[1] = 1;
        for(int i = 2; i<=target;i++){
            int n = log2(i)+1;
            if((1<<n)-1 == i){
                dp[i] = n;
                continue;
            }
            dp[i] = n + 1 + dp[(1<<n)-1 - i];
            for(int k = 0; k<n; k++)
                dp[i] = min(dp[i], n-1+2+k+dp[i-((1<<(n-1)) - (1<<k))]);
        }
        return dp[target];
    }
};


class Solution {
public:
    int racecar(int target) {
        if(target == 1)
            return 1;

        vector<int>dp(target+1,target+1);
        for(int i = 1, n = 1; i<=target;++i){
            if( i == (1 << n) - 1){
                dp[i] = n++;
                
            }
            else{
                dp[i] = n + 1 + dp[(1<<n)- 1 - i];
                for(int j = 0; j <= n-1 ; ++j){
                    dp[i] = min(dp[i], n-1  +  j + 2 + dp[ i-(1<<n-1)+ (1<<j) ]); //(1<<n-1) 先算 n-1 再算 << 
                }
            }
        }
        return dp[target];
    }
};


//topDown
class Solution {
public:
    int racecar(int target) {
        vector<int>dp(target+1, 0);
        return topDown(dp, target);
    }
    
    int topDown(vector<int>&dp, int i){
        if(i == 1)
            return 1;
        if(dp[i] > 0)
            return dp[i];
        
        int N = log2(i) + 1;
        if (i == (1 <<N) -1 )
            return dp[i] = N;
        
        dp[i] = N+1 + topDown(dp, (1<<N)-1-i);
        for(int j = 0; j<N; ++j)
            dp[i] = min(dp[i], N-1 + j + 2 + topDown(dp, i - (1<<(N-1)) + (1 << j)));
        return dp[i];
    }
};


/*
Top-down DP:
*/

class Solution {
public:
    int dp[10001];
    int racecar(int target) {
        if (dp[target]==0){
            int n = log2(target)+1;
            if((1<<n)-1 == target)
                dp[target] = n;
            else{
                dp[target] = n + 1 + racecar((1 << n)-1 - target);
                for(int k = 0; k<n; k++){
                    dp[target] = min(dp[target], n-1+2+k+racecar(target- ((1 << (n-1)) - (1 << k ) )));
                }
            }
        }
        //cout<<" target "<<target<<" dp "<<dp[target]<<endl;
        return dp[target];
    }
};

class Solution {
public:
    int racecar(int target) {
        vector<int> dp(target + 1);
        for (int i = 1; i <= target; ++i) {
            int k = bitLength(i);
            if (i == (1 << k) - 1) {
                dp[i] = k;
                continue;
            }
            dp[i] = dp[(1 << k) - 1 - i] + k + 1;
            for (int j = 0; j < k; ++j) {
                dp[i] = min(dp[i], dp[i - (1 << (k - 1)) + (1 << j)] + k + j + 1);
            }
        }
        return dp.back();
    }

private:
    uint32_t bitLength(uint32_t n) {
        uint32_t left = 1, right = 32;
        while (left <= right) {
            auto mid = left + (right - left) / 2;
            if ((1 << mid) > n) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};





class Solution {
public:
    int racecar(int target) {
        if(target == 1)
            return 1;
        int step = 0;
        queue<vector<int >>q; //0 is position, 1 is speed
        q.push({0,1});
        unordered_map<int,unordered_map<int,int>>visited;//0 is position, 1 is speed
        
        while(!q.empty())
        {
            ++step;
            int size = q.size();
            for(int z = 0; z<size; ++z){
                vector<int >cur = q.front(); q.pop();
                int point = cur[0], speed = cur[1];
                
                if(point + speed == target)
                    return step;
                
                if(point + speed > 0 && point + speed < (target << 1) && visited[point+speed][speed*2] == 0){
                    q.push({point+speed, speed*2});
                    visited[point+speed][speed*2] = 1;
                }
                
                if(speed > 0 && visited[point][-1] == 0){
                    q.push({point, -1});
                    visited[point][-1] = 1;
                }
                else if(speed < 0 && visited[point][1] == 0){
                    q.push({point, 1});
                    visited[point][1] = 1;
                }
            }
        }
        return -1;
    }
};


