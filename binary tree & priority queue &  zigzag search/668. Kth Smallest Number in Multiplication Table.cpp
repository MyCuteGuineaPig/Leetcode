/*
668. Kth Smallest Number in Multiplication Table

Nearly every one have used the Multiplication Table. But could you find out the k-th smallest number quickly from the multiplication table?

Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.

Example 1:
Input: m = 3, n = 3, k = 5
Output: 
Explanation: 
The Multiplication Table:
1	2	3
2	4	6
3	6	9

The 5-th smallest number is 3 (1, 2, 2, 3, 3).
Example 2:
Input: m = 2, n = 3, k = 6
Output: 
Explanation: 
The Multiplication Table:
1	2	3
2	4	6

The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
Note:
The m and n will be in the range [1, 30000].
The k will be in the range [1, m * n]


*/

/*
complexity O(log(mn)*min(n,n)), space O(1)
*/

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        if(m>n) swap(m,n);
        int l = 1, r = m*n;
        while(l<r){
            int mid = (l+r)>>1;
            if(isEnough(m,n,k,mid)) r = mid;
            else l = mid+1;
        }
        return l;
    }
    
    bool isEnough(int m,int n, int k, int target){
        int cnt = 0;
        for(int i = 1; i<=m; i++){
            cnt += min(target/i, n);
            if(cnt>=k) return true;
        }
        return false;
    }
};



class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int l = 1, r = m*n, min_ = min(m,n), max_ = max(m,n);
        while(l<r){
            int mid = l + (r-l)/2;
            //cout<<mid<<" l "<<l<<"  r "<<r<<endl;
            if(isEnough(min_,max_,mid,k)) r = mid;
            else l = mid+1;
            //cout<<mid<<" afterl "<<l<<"  r "<<r<<endl;
        }
        return l;
    }

    bool isEnough(int min_, int max_, int target, int k){
        int count = 0;
        for(int i = 1;i<=min_; i++){
            count += min(target/i,max_);
            if(count>=k) return true;
        }
        //cout<<" count "<<count<<endl;
        return false;
    }
};



/*
Priority QUEUE
get TLE
Complexity O(k*logN)  k次insert & extract 如果k很大，接近m*n就容易timeout, 跟binary search O(log(mn)*min(m,n)) solution 比慢

Space complexity: O(n)
*/
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        auto comp = [](const pair<int,int>&a, const pair<int,int>&b){ return a.first*a.second>b.first*b.second;};
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)>pq(comp);
        for(int i = 1; i<=n && i<=k; i++){
            pq.push({1,i});
        }
        while(--k>0){
            auto it = pq.top();
            //cout<<it.first<<" "<<it.second<<endl;;
            pq.pop();
            if(++it.first<=m) pq.push(it);
        }
        return pq.top().first*pq.top().second;
    }
};


/*
Two pointer
Also Get TLE Complexity O(m*n*m) O(m*n)是pointer移动的距离，O(m)是count 小于等于还是小于count的数
*/
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        if(m>n) swap(m,n); //keep m is small
        int row = 0, col = n-1;
        while(row<=m && n>=1){
            int cnt_le = 0, cnt_lt = 0; //cnt_le is less or equal to, cnt_lt strickly less than row*col
            for(int i = 1; i<=m; i++){
                cnt_le += min(row*col/i,n);
                cnt_lt += min((row*col-1)/i,n);
            }
            cout<<" row "<<row<<" col "<<col<<" cnt_le "<<cnt_le<<" cnt_lt "<<cnt_lt<<endl;
            if(cnt_le < k) row++;
            else if(cnt_lt>=k) col--;
            else break;
        }
        return row*col;
    }
};