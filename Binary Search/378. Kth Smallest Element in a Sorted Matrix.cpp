/*
378. Kth Smallest Element in a Sorted Matrix


Given a n x n matrix where each of the rows and columns are sorted in ascending order, 
find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note: 
You may assume k is always valid, 1 ≤ k ≤ n2.

*/

/*
O(log(max-min)*n)

因为每一个row 和column 都是sort的，所以最后一个column 从上到下肯定也是sorted
  比如  1  5  9
       10 11 13
       12 13 15
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int l = matrix[0][0], r = matrix[n-1][n-1];
        while(l<r){
            int mid = (l+r)>>1;
            //cout<<l<<"  r "<<r<<"  mid "<<mid<<endl;
            if(isValid(matrix, k, mid)) r = mid;
            else l = mid+1;
            //cout<<" after "<<l<<"  r "<<r<<"  mid "<<mid<<endl;
        }
        return l;
    }
    
    bool isValid(vector<vector<int>>& matrix, int k, int target){
        int n = matrix.size();
        int cnt = 0;
        for(int i = 0, j = n-1; j>=0 && i<n; i++){
            while(j>=0 && matrix[i][j]>target) j--;
            cnt += j+1;
            if(cnt>=k) return true;
        }
        //cout<<cnt<<endl;;
        return false;
    }
};



/*
O(log(max-min)*n*log(m))

这个答案每一列可以不是sorted的
  比如  1  5  9
       10 11 13
       12 13 15
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int i = 0; i < matrix.size(); ++i) {
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            }
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};