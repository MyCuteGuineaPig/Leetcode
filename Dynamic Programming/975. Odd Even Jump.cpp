/*
Explanation
We need to jump higher and lower alternately to the end.

Take [5,1,3,4,2] as example.

If we start at 2,
we can jump either higher first or lower first to the end,
because we are already at the end.
higher(2) = true
lower(2) = true

If we start at 4,
we can't jump higher, higher(4) = false
we can jump lower to 2, lower(4) = higher(2) = true

If we start at 3,
we can jump higher to 4, higher(3) = lower(4) = true
we can jump lower to 2, lower(3) = higher(2) = true

If we start at 1,
we can jump higher to 2, higher(1) = lower(2) = true
we can't jump lower, lower(1) = false

If we start at 5,
we can't jump higher, higher(5) = false
we can jump lower to 4, lower(5) = higher(4) = false
*/
class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        int n = A.size(), res = 1;
        vector<int>high(n), low(n);
        map<int,int>mp; //keep record the index
        high[n-1] = low[n-1] =1;
        mp[A[n-1]] = n-1;
    
        for(int i = A.size()-2; i>=0; --i){
            auto hi = mp.lower_bound(A[i]), lo = mp.upper_bound(A[i]);
            if(hi!=mp.end())
                high[i] = low[hi->second];
            if(lo!=mp.begin())
                low[i] = high[(--lo)->second];
            if(high[i])//因为第一步都是High
                ++res;
            mp[A[i]] = i;
        }
        return res;
    }
};




class Solution {
public:
    int oddEvenJumps(vector<int>& A, int res = 1) {
      vector<pair<bool, bool>> dp(A.size());
      map<int, int> m;
      dp[A.size() - 1] = { true, true };
      for (int i = A.size() - 1; i >= 0; --i) {
        auto it = m.lower_bound(A[i]);
        if (it != end(m)) {
            res += dp[i].first = dp[it->second].second;
            if (it->first == A[i]) ++it;
        }
        if (it != begin(m)) dp[i].second = dp[prev(it)->second].first;
        m[A[i]] = i;
      }
      return res;
    }
};



//stack
class Solution {
public:
    int oddEvenJumps(vector<int>& A, int res = 1) {
const int n = A.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++) index[i] = i; 
        
        auto cmp_odd = [&A](const int x, const int y){
            return A[x] < A[y] || (A[x] == A[y] && x < y); 
        };
        auto cmp_even = [&A](const int x, const int y){
            return A[x] > A[y] || (A[x] == A[y] && x < y); 
        };        
        auto find_next = [](vector<int>& index) -> vector<int> {
            vector<int> next(index.size());
            stack<int> stk; 
            for (auto i: index) { 
                while (!stk.empty() && stk.top() < i) {
                    next[stk.top()] = i; 
                    stk.pop(); 
                }
                stk.push(i); 
            }            
            return next; 
        };
        
        sort(index.begin(), index.end(), cmp_odd); 
        vector<int> odd_next = find_next(index); 
        sort(index.begin(), index.end(), cmp_even); 
        vector<int> even_next = find_next(index);        
    
        vector<bool>even(n), odd(n);
        even[n-1] = odd[n-1] = true; 
        for (int i = n - 2; i >= 0; i--) {
            if (odd_next[i]) odd[i] = even[odd_next[i]]; 
            if (even_next[i]) even[i] = odd[even_next[i]]; 
        }
        int ans = 0; 
        for (auto a : odd) {
            ans += a; 
        } 
        return ans;
    }
};