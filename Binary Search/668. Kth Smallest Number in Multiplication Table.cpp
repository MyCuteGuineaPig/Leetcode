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
        int l = 1, r = m*n, min_ = min(m,n), max_ = max(m,n);
        while(l<r){
            int mid = l + (r-l)/2;
            if(isNotEnough(min_,max_,mid,k)) l = mid+1;
            else r = mid;
        }
        return l;
    }

    bool isNotEnough(int min_, int max_, int target, int k){
        int count = 0;
        for(int i = 1;i<=min_; i++){
            count += min(target/i,max_);
            if(count>=k) return false;
        }
        return true;
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


class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m * n;
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int i = 1; i <= m; ++i) {
                cnt += (mid / i <= n) ? (mid / i) : n;
            }
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};


class Solution {
public:
    int findKthNumber(int m, int n, int k) {

        int lo = 1, hi = n*m;

        while(lo < hi){
            int mid = (lo+hi)/2; //still less than INT_MAX
            int totleq = 0;
            for(int i = 1, j = m, v = i*j; i<=n; i++, v+=j){
                while(v > mid) j--, v-=i;
                totleq += j;
            }
            if(totleq >= k) hi = mid;
            else lo = mid+1; 
        }
        return lo;
    }
};