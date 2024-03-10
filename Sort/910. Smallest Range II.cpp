class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int res = A[A.size() - 1] - A[0]; //
        /*
        如果 K >A[A.size() - 1] - A[0] 
        最优的解 就是把所有数都加上k 或者所有数都减去k
        
        如果A[0] +k, A[A.size() - 1] -k 
        diff 就是 
        A[0] +k - (A[A.size() - 1] -k )
        = A[0] - A[A.size() - 1] + 2k 
        > A[0] - A[A.size() - 1] + 2*( A[A.size() - 1] - A[0])
         = A[A.size() - 1] - A[0]
        */

        int left = A[0] + K, right = A[A.size() - 1] - K;
        for (int i = 0; i < A.size() - 1; i++) {
            int maxi = max(A[i] + K, right), mini = min(left, A[i + 1] - K);
            /*
            如果 maxi > right, 保证A[i] + k是最大的情况下 可以让 A[i+1... n-1] 全部都减去k, 因为A[n-1]-k = right     array是sort的, 所以A[i+1,... n-1] - k 都小于right
            同理 mini < left, 保证 A[i + 1] - K最小的情况是 以让 A[i+1... n-1] 全部都加上k, 因为A[0]+k = left     array是sort的, 所以A[0,.. i+1] + k  都大于right
            */
            res = min(res, maxi - mini);
            //cout<<i<<" i  A[i] = "<<A[i]<<" A[i+1] = "<<A[i+1]<<" maxi "<<maxi<<" mini "<<mini<<endl;
        }
        return res;
    }
};


class Solution {
public:
  int smallestRangeII(vector<int>& A, int K) {
    std::sort(A.begin(), A.end());
    int ret = A.back() - A.front();
    for (auto first = A.begin(), first2 = first + 1; first2 != A.end(); ++first, ++first2) {
      ret = std::min(ret, std::max(A.back() - K, *first + K) - std::min(A.front() + K, *first2 - K));
    }
    return ret;
  }
};