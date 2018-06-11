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
            if(isValid(matrix, k, mid)) r = mid;
            else l = mid+1;
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


/*
priority queue
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        auto cmp = [&](const pair<int,int>&a, const pair<int,int>&b){
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)>pq(cmp);
/*
or use 
priority_queue<pair<int,int>, vector<pair<int,int>>, function<bool(const pair<int,int>&a,const pair<int,int>&b)>>pq([&](const pair<int,int>&a, const pair<int,int>&b){return matrix[a.first][a.second] > matrix[b.first][b.second];});
*/

        //第一个存row index, 第二个存column index
        for(int i = 0; i<n && i<k; i++) pq.push({0,i});
        while(--k>0){
            auto it = pq.top();
            pq.pop();
            if(++it.first<n){
                pq.push(it);
            }
        }
        return matrix[pq.top().first][pq.top().second];
    }
};



/*
Two pointer method 
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
    
        int row = 0;          // we start from the upper-right corner
        int col = n - 1;      

        for (int cnt_le = 0, cnt_lt = 0; true; cnt_le = 0, cnt_lt = 0) {
            //cout<<" compare number "<<matrix[row][col]<<endl;
            for (int i = 0, j = n - 1, p = n - 1; i < n; i++) {
                //cout<<i<<" row "<<row<<" col "<<col;
                while (j >= 0 && matrix[i][j] > matrix[row][col]) j--;  // pointer j for counting cnt_le
                cnt_le += (j + 1);
                //cout<<" cntle "<<cnt_le;
                while (p >= 0 && matrix[i][p] >= matrix[row][col]) p--;   // pointer p for counting cnt_lt
                cnt_lt += (p + 1);
                //cout<<" cntlt "<<cnt_lt<<endl;
            }

            if (cnt_le < k) {         // candidate solution too small so increase it
                row++; 
            } else if (cnt_lt >= k) { // candidate solution too large so decrease it
                col--;
            } else {                  // candidate solution equal to the kth smallest element so return
                return matrix[row][col];
            }
            //cout<<" after i row "<<row<<" col "<<col<<endl;
        }
    }
};


class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int row = 0, col = n-1;
        while(row<n && col >=0){
            int cnt = 0, equal = 0;
            for(int i = 0, j=n-1; j>=0 && i<n; i++){
                while(j>=0 && matrix[i][j]>matrix[row][col]) j--;//j包括了等于的
                cnt += j+1;
                if(j>=0 && matrix[i][j] == matrix[row][col]){
                    int m = j; 
                    while(m>=0 && matrix[i][m]==matrix[row][col]) m--;
                    equal += j-m;
                }
            }
            if(cnt<k) row++;  //to much element less than or equal to A[r][c], need to increase A[r][c]
            else if(cnt-equal>=k) col--; ////to much element bigger than  A[r][c], need to decrease A[r][c]
            else break;
        }
        return matrix[row][col];
    }
};
