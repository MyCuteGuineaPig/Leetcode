/*
786. K-th Smallest Prime Fraction

A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, 
we consider the fraction p/q.

What is the K-th smallest fraction considered?  Return your answer as an array of ints, 
where answer[0] = p and answer[1] = q.

Examples:
Input: A = [1, 2, 3, 5], K = 3
Output: [2, 5]
Explanation:
The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
The third fraction is 2/5.

Input: A = [1, 7], K = 1
Output: [1, 7]
Note:

A will have length between 2 and 2000.
Each A[i] will be between 1 and 30000.
K will be between 1 and A.length * (A.length - 1) / 2.



*/

/*

O(max(n, K) * logn),
space complexity O(n)
*/

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int n = A.size();
        auto comp = [&A](pair<int,int>a, pair<int,int>b){
            return A[a.first]*A[b.second] > A[b.first]*A[a.second];
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>,decltype(comp)>pq(comp);
        for(int i = 0; i<n; i++)
            pq.push({i,n-1});
        while(--K>0){
            auto top = pq.top();
            pq.pop();
            if(--top.second>=0){
                pq.push(top);
            }
        }
        //cout<<pq.top().first<<"  "<<pq.top().second<<endl;
        return {A[pq.top().first], A[pq.top().second]};
    }
};


class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int n = A.size();
        priority_queue<pair<int,int>, vector<pair<int,int>>,function<bool(pair<int,int>a, pair<int,int>b)>>pq([&](pair<int, int>a, pair<int, int>b){return A[a.first]*A[b.second] > A[b.first]*A[a.second];});
        for(int i = 0; i<n; i++)
            pq.push({i,n-1});
        while(--K>0){
            auto top = pq.top();
            pq.pop();
            if(--top.second>=0){
                pq.push(top);
            }
        }
        return {A[pq.top().first], A[pq.top().second]};
    }
};

/*

Binary Search

Remarks:

The kth smallest fraction is known to be in the range [0, 1],
 so we initialize the search space with this range (i.e., l = 0 and r = 1).

We need the pair (p, q) to record the maximum fraction in the matrix that is no greater than each candidate solution. 
This is necessary because on the one hand, 
the candidate solution itself cannot tell us what the numerator and denominator of the fraction are (remember the candidate solution is just a floating-point number); 
on the other hand, even if we can get the numerator and denominator of the candidate solution,
 these values may not be contained in the input array (remember all the fractions must be formed by pair of integers from the input array). 
 This is different from the case when the matrix elements are integers, where at the end of the binary search, 
 the candidate solution must be equal to the kth smallest element in the matrix.

The above solution only works when there are no duplicate fractions in the matrix (which is indeed the case for prime fractions). 
Otherwise, we need two counts, cnt_le and cnt_lt, to account for duplicates, 
similar to what we did in the ZigzagSearch solution below.

The time complexity is computed as follows: 
the binary search loop will terminate when the count of elements no greater than a candidate solution reaches K. 
This is guaranteed to happen when the size of the search range [l, r] becomes smaller than the smallest absolute distance between any pair of fractions in the matrix, 
which is >= 1/MAX^2. Since each iteration will reduce the search range by half, 
the binary search loop will terminate after at most log(MAX^2) steps. Each iteration is done in linear time, 
therefore the total time complexity is O(n * log(MAX^2)).

*/

/*
Time complexity: O(n * log(MAX^2)), where MAX is the maximum element in A
Space complexity: O(1)


*/

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        double l = 0, r = 1;
        int n = A.size();
        vector<int>res(2);
        while(l<r){
            double mid = (l+r)/2;
            /*
            顺序是先加j, 之后加i，加j让A[i]/A[j] 变小，知道让A[i]/A[j]小于m，
            再后加i，这样A[i]/A[j] 就变大了，然后再加j让A[i]/A[j]小于m
            比如mid = 0.5, A = [1,2,3,5]
            显示1/1, 1/2 [1/2,1/3,1/5都小于等于0.5]， 有三个
            再接着2/2, 2/3, 2/5 (2/5小于0.5) 有一个,

            同时假如 A[i]/A[j]是在i=时候 第一个小于等于mid。不可能A[i]/A[j-1] 就大于mid,
            A[i+1]/A[j-1] 更大于mid，因为A[i+1]>A[i], 所以判断到下一行时，保留上一个判断的j
            */
            int cnt = 0, p = 0, q = 1;
            for(int i = 0, j=0; i<n && j<n; i++){
                while(j<n && A[i]>mid*A[j]) j++;
                cnt += n-j;
                if(j<n && A[i]*q>A[j]*p) {
                    p = A[i]; q = A[j]; //选择大的A[i]/A[j] > p/q的，因为加入cnt == k, 答案就是cnt中最大的那个
                }
                //cout<<" mid "<<mid<<"  "<<i<<"  "<<j<<" cnt "<<cnt<<" p "<<p<<" q "<<q<<endl;
            }
            if(cnt<K) l = mid;
            else if(cnt>K) r = mid;
            else {
                //cout<<mid<<endl;
                return {p,q};
            }
        }
        return res;
    }
};





/*
Two pointer method 
Time complexity: O(n^2)
Space complexity: O(1)
*/


class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int row = 0, col = 0; //增大prime pair是row++, 减小prime pair是col ++;
        int n = A.size();
        while(true){
            int cnt_le = 0, cnt_lt = 0;
            for(int i = 0, j=0; j<n&&i<n; i++){
                while(j<n && A[i]*A[col]>A[j]*A[row]) j++; //make A[row]A[i]/A[j] less than or equal to A[row]/A[row]
                cnt_le += n-j; //不会出现两个数相等的情况
                //cout<<j<<endl;
            }
            //cout<<" cnt_le "<<cnt_le;
            if(cnt_le<K){//cnt_le 小于k,A[i]/A[j] 太小，没有足够多组成k
                row++;
            }else if(cnt_le>K){//cnt_le 大于k,A[i]/A[j] 太大，太多的可以组成小于A[i]/A[j]
                col++;
            }else{
                return {A[row],A[col]};   
            }
        }
    }
};