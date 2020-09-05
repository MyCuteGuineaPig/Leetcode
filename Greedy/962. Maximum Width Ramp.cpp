
/*
Solution 1: 
Descending stack: 存的是依次 由大到小的数 第一次出现的位置:

stack pop: 保证是stack 中数作为i，最远的j 的 pair(i, j)
stack willl only be pop if last element 小于等于 A[j], which guarantee to be the max-width ramp
      若


*/
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        stack<int>stk;
        for(int i = 0; i<A.size(); ++i)
            if(stk.empty() || A[i] < A[stk.top()])
                stk.push(i);
        
        int res = 0;
        for(int j = A.size()-1; j>=0 && stk.size(); --j){
            while(stk.size() && A[stk.top()]<=A[j]){
                res = max(res, j - stk.top());
                stk.pop();
            }
        }
        return res;
    }
};

/**
 Solution 2: Two pointer/Sliding Window
 */

class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        int n = A.size();
        vector<int>rMax(n, A.back());
        for(int i = n-2; i>=0; --i)
            rMax[i] = max(rMax[i+1], A[i]);
        
        int res = 0, left = 0, right = 0;
        while(right < n){
            while(left < n && A[left] > rMax[right])
                ++left;
            res = max(res, right-left);
            ++right;
        }
        return res;
    }
};


/*

The idea of this solution is: Suppose (i, j) is the answer, then A[i] must be the smallest element among the first i + 1 elements of A
 and A[j] must be the largeset element among the last len(A) - j elements of A. 
 Otherwise, we can always find an element smaller than A[i] or larger than A[j], 
 so that (i, j) is not the maximum width ramp.



For example, the input is [6, 0, 8, 2, 1, 5]. 

Then min_arr=[6, 0, 0, 0, 0, 0] and max_arr=[8, 8, 8, 5, 5, 5].


 */

class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        int n = A.size();
        int i, j , res = 0;
        vector<int> maxR(n), minL(n);
        minL[0] = A[0];
        for (i = 1; i < n; i++){
            minL[i] = min(A[i], minL[i - 1]);
        }
        maxR[n - 1] = A[n - 1];
        for (j = n - 2; j >= 0; j--){
            maxR[j] = max(A[j], maxR[j + 1]);
        }
        i = 0; j = 0;
        while (i < n && j < n){
            if (minL[i] <= maxR[j]){
                res = max(res, j - i);
                j++;
            }else{
                i++;
            }
        }
        return res;
    }
};



/*
Solution 3: Sort 
O(NlogN)
*/
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        vector<vector<int>>B;
        for(int i = 0; i<A.size(); ++i)
            B.push_back({A[i], i});
        sort(B.begin(), B.end(), [](vector<int>&a, vector<int>&b){
            if(a[0]!=b[0])
                return a[0] < b[0];
            return a[1] < b[1];
        });
        int res = 0, leftmost = B[0][1];
        for(int i = 0; i<B.size(); ++i){
            res = max(res, B[i][1] - leftmost);
            leftmost = min(leftmost, B[i][1]);
        }
        return res;
    }
};


class Solution {
public:
    int maxWidthRamp(vector<int>& A, int res = 0) {
      vector<pair<int, int>> v;
      for (auto i = 0; i < A.size(); ++i) {
        if (v.empty() || v.back().first > A[i]) v.push_back({ A[i], i });
        else res = max(res, i - lower_bound(v.begin(), v.end(), make_pair( A[i], INT_MAX ), 
            greater<pair<int, int>>())->second);
      }
      return res;
    }
};