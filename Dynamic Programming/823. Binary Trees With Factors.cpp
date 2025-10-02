/*
[2,3,6,18] 

[2], [3], [6], [18],
[6, 2, 3], [6,3,2]
[18,6,3], [18,3,6]
[18,6,3,2,3], [18,6,2,3,3],
[18,3,6,2,3], [18,3,6,3,2]

[2] = 1 
[3] = 1
[6] = 1 + 2*1*1 = 3
[18] = 1+3*1*2
*/

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        long res = 0, mod = pow(10, 9) + 7;
        sort(A.begin(), A.end());
        unordered_map<int, long> dp;
        for (int i = 0; i < A.size(); ++i) {
            dp[A[i]] = 1; // single node tree
            for (int j = 0; j < i; ++j)
                if (A[i] % A[j] == 0)
                    dp[A[i]] = (dp[A[i]] + dp[A[j]] * dp[A[i] / A[j]]) % mod;
            res = (res + dp[A[i]]) % mod;
        }
        return res;
    }
};


//top-down
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        unordered_map<int, long>mp;
        unordered_map<int, int> index_mp;
        for(int i = 0; i < arr.size(); ++i)
            index_mp[arr[i]] = i;
        long mod = 1e9 + 7;
        long res  = 0;
        auto f = [&](this auto && f, int i) -> long {
            if (mp.count(arr[i])) {
                return mp[arr[i]];
            }
            mp[arr[i]] = 1;
            for(int j = 0; j < i; ++j){
                if (arr[i] % arr[j] == 0 && index_mp.count(arr[i] / arr[j]))
                    mp[arr[i]] = (mp[arr[i]] + f(index_mp[arr[i] / arr[j]])*f(j)) % mod;
            }
            res = (res + mp[arr[i]]) % mod;
            return mp[arr[i]];
        };
        for(int i = 0; i < arr.size(); ++i){
            f(i);
        }
        return res;
    }
};


class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        const long M = 1e9 + 7; long res = 0;
        sort(A.begin(),A.end());
        unordered_map<int,long>map;
        
        for(int i = 0; i<A.size(); i++){
            map[A[i]] = 1;
            for(int j = 0; j<i && A[j]<=sqrt(A[i]);j++){
                if(A[i]%A[j] == 0 && map.count(A[i]/A[j])){
                    if(A[i] == A[j]*A[j]){
                        map[A[i]]  = (map[A[i]] + map[A[j]]*map[A[j]]);
                    }
                    else{
                        map[A[i]] = (map[A[i]] + 2*map[A[j]]*map[A[i] / A[j]]); //比如 [2，5，10], dp[2] = dp[5] = 1,  dp[10] = 1 + 2 * 1 * 1 = 3
                    }
                    
                }
            }
            res = (res+map[A[i]])%M;
        }
        return res;
    }
};


// Two Pointer
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        long mod = 1000000007;
        sort(A.begin(), A.end());
        vector<long> dp(A.size());
        
        int result = 0;
        for (int i = 0; i < dp.size(); ++i) {
            dp[i] = 1;
            int begin = 0;
            int end = i-1;
            while (begin <= end) {
                if (A[begin]*A[end] > A[i]) {
                    end--;
                } else if (A[begin]*A[end] < A[i]) {
                    begin++;
                } else {
                    dp[i] = (dp[i] + (dp[begin]*dp[end])*(begin == end ? 1 : 2)) % mod;
                    begin++;
                }
            }
            result  = (result + dp[i]) % mod;
        }
        return result;
    }
};



class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        S.insert(A.begin(),A.end());
        long long ans=0; for (auto x: S) ans+=go(x);
        return int(ans % 1000000007);
    }
private:
    unordered_set<int> S;
    unordered_map<int,long long> M;
    long long go(int x){
        if (M.count(x)) return M[x];
        long long cnt=1; for (int i: S) if (x%i==0 && S.count(x/i)) cnt+=go(i)*go(x/i);
        return M[x]=cnt;
    }
};