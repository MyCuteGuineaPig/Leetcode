
/*
解释
https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/Share-my-O(log(min(mn))-solution-with-explanation?page=3


      left_part          |        right_part
A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]


If we can ensure:

1) len(left_part) == len(right_part)
2) max(left_part) <= min(right_part)
then we divide all elements in {A, B} into two parts with equal length, 
    and one part is always greater than the other. Then median = (max(left_part) + min(right_part))/2.

To ensure these two conditions, we just need to ensure:

(1) i + j == m - i + n - j (or: m - i + n - j + 1)
    if n >= m, we just need to set: i = 0 ~ m, j = (m + n + 1)/2 - i
(2) B[j-1] <= A[i] and A[i-1] <= B[j]


更新A的ilow 和ihigh, j = (m+n+1)/2-i,
if i<m && B[j-1]>A[i]: ilow=i+1(A[i]太小)
if i>0 && A[i]>B[j]：ihigh = i-1 (A[i]太大)

如果 n+m 为奇数，规定这个数在左面
i 代表 中位数以左nums1 抽取的个数
j 代表 中位数以左nums1 抽取的个数

*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return findMedianSortedArrays(nums2,nums1);
        int m = nums1.size(), n = nums2.size();
        int k = (m+n+1)/2,  ilow = 0, ihigh = m; //k代表中位数从nums1, nums2中挑的数
        while(ilow<=ihigh){
        /*
         //要有等于的情况比如
        [2]
        [1,3]
        第一次 i=0, j = 2, ilow = 0, ihigh = 1
        第二次 i=1, j = 2, ilow = 1, ihigh = 1

        */

            int i = ilow + (ihigh-ilow)/2;
            int j = k-i;
            if(i<m && nums2[j-1]>nums1[i])
                ilow = i+1;
            else if(i>0 && nums1[i-1]>nums2[j])
                ihigh = i-1;
            else{
                int maxleft = numeric_limits<int>::min(), minright=numeric_limits<int>::max();
                if(i>0) maxleft = nums1[i-1];
                if(j>0) maxleft = nums2[j-1];
                if(i>0 && j>0) maxleft = max(nums2[j-1], nums1[i-1]);
                if((m+n)&1) return maxleft;
                
                if(i<m) minright = nums1[i];
                if(j<n) minright = nums2[j];
                if(i<m && j<n) minright = min(nums1[i], nums2[j]);
                return static_cast<double>(maxleft + minright)/2;
            }
        }
        return -1;
    }
};


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if(n1 > n2) 
            return findMedianSortedArrays(nums2, nums1);
        int l = 0, r = n1;
        while(l<r){
            int m1 = (l+r)/2;
            int m2 = (n1 + n2 + 1)/2 - m1;
            if(m1 < n1 && m2 > 0 && nums1[m1] < nums2[m2-1])
                l = m1 + 1;
            else
                r = m1;
        }
        
        int m1 = l, m2 = (n1 + n2 + 1)/2 - m1;
        int lv = numeric_limits<int>::min();
        if(m1 > 0 && m1 <= n1 )
            lv = max(lv, nums1[m1-1]);
        if(m2 > 0 && m2 <= n2 )
            lv = max(lv, nums2[m2 -1]);
        if((n1 + n2)&1)
            return lv;
        int rv = numeric_limits<int>::max();
        if(m1 < n1)
            rv = min(rv, nums1[m1]);
        if(m2 < n2)
            rv = min(rv, nums2[m2]);
        return static_cast<double>(lv+rv)/2;
    }
};


//2020 
/*


      left_part          |        right_part
A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
B[0], B[1], ..., B[j]  |  B[j+1], B[j+1], ..., B[n-1]

如果 m + n 是偶数, 返回 (max(A[i-1], B[j]) + min(A[i], B[j+1) ) / 2
如果 m + n 是奇数, 返回 max(A[i-1], B[j])


 */
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);
        int m = nums1.size(), n = nums2.size();
        int l = 0, r = m;
        while(l<=r){
            int i = l + (r-l)/2, j = (m+n-1)/2-i;
            if(i < m && j > 0 && nums2[j]>nums1[i]) l = i+1;  //j 可能小于0, 比如 nums=[1,2], nums=[3,4],  i = 2, j = -1
            else if(i > 0  && nums2[j+1] <nums1[i-1] ) r = i-1; // j 一定小于 n - 1; 最大j = (m+n-1) / 2, 
            else{
                int left = numeric_limits<int>::min(), right = numeric_limits<int>::max();
                if(i>0) left = nums1[i-1];
                if(j>=0) left = max(left, nums2[j]);
                
                if(i<m) right = nums1[i];
                if(j<n-1) right = min(right, nums2[j+1]);
                
                if((m+n) & 1)
                    return left;
                else 
                    return (double)(left + right)/2.0;
                
            }
        }
        return -1;
    }
};




class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return findMedianSortedArrays(nums2,nums1);
        int m = nums1.size(), n = nums2.size();
        int k = (m+n+1)/2,  ilow = 0, ihigh = m, i = 0, j=0; //k代表中位数从nums1, nums2中挑的数
        while(true){
            i = ilow + (ihigh-ilow)/2;
            j = k-i;
            if(i<m && nums1[i]<nums2[j-1])
                ilow = i+1;
            else if(i>0 && nums1[i-1]>nums2[j])
                ihigh = i-1;
            else
                break;
        }
        int maxleft = max(i==0 ? INT_MIN : nums1[i-1], j==0 ? INT_MIN : nums2[j-1]);
        if((m+n)&1) return maxleft;
        
        int minright = min(i==m? INT_MAX : nums1[i], j==n? INT_MAX : nums2[j]);
        return static_cast<double>(maxleft + minright)/2;
    }
};



class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()>nums2.size()) return findMedianSortedArrays(nums2,nums1);
        int m = nums1.size(), n = nums2.size();
        int k = (m+n+1)/2,  ilow = 0, ihigh = m, i = 0, j=0; //k代表中位数从nums1, nums2中挑的数
        while(ilow<ihigh){
            i = ilow + (ihigh-ilow)/2;
            j = k-i;
            if(nums1[i]< nums2[j-1]) //保证 i 永远在0 到m之间,i不可能等于m因为如果等于m,ilow == ihigh 跳出循环了
                ilow = i+1;
            else ihigh = i;
        }
        i = ilow; j = k-ilow;
        int maxleft = max(i==0 ? INT_MIN : nums1[i-1], j==0 ? INT_MIN : nums2[j-1]);
        if((m+n)&1) return maxleft;
        
        int minright = min(i==m? INT_MAX : nums1[i], j==n? INT_MAX : nums2[j]);
        return static_cast<double>(maxleft + minright)/2;
    }
};

/*
do binary search. suppose the shorter list is A with length n. 
the runtime is O(log(n)) which means no matter how large B array is, 
it only depends on the size of A. It makes sense because if A has only one element 
while B has 100 elements, the median must be one of A[0], B[49], and B[50] without check everything else. 
If A[0] <= B[49], B[49] is the answer; 
if B[49] < A[0] <= B[50], A[0] is the answer; else, B[50] is the answer.



 */
class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        // the following call is to make sure len(A) <= len(B).
        // yes, it calls itself, but at most once, shouldn't be
        // consider a recursive solution
        if (n > m)
            return findMedianSortedArrays(nums2, nums1);

        // now, do binary search
        int k = (n + m - 1) / 2;
        int l = 0, r = min(k, n); // r is n, NOT n-1, this is important!!
        while (l < r) {
            int midA = (l + r) / 2;
            int midB = k - midA;
            if (nums1[midA] < nums2[midB])
                l = midA + 1;
            else
                r = midA; 
        /*
        不可以是 r = midA - 1; 
        比如     [1,2]
                [1,2,3]
            l = 0, r = 2;  midA = 1, midB  = 1
            Not nums1[1] < nums2[1] :  r = midA -1 = 1 - 1 = 0

            =》 l = 0, k -l = 2, 错误的
         */
        
        }

        // after binary search, we almost get the median because it must be between
        // these 4 numbers: A[l-1], A[l], B[k-l], and B[k-l+1] 

        // if (n+m) is odd, the median is the larger one between A[l-1] and B[k-l].
        // and there are some corner cases we need to take care of.
        int a = max(l > 0 ? nums1[l - 1] : numeric_limits<int>::min(), k - l >= 0 ? nums2[k - l] : numeric_limits<int>::min());
        if (((n + m) & 1) == 1)
            return (double) a;

        // if (n+m) is even, the median can be calculated by 
        //      median = (max(A[l-1], B[k-l]) + min(A[l], B[k-l+1]) / 2.0
        // also, there are some corner cases to take care of.
        int b = min(l < n ? nums1[l] : numeric_limits<int>::max(), k - l + 1 < m ? nums2[k - l + 1] : numeric_limits<int>::max());
        cout<<a<<" a "<<b<<endl;
        return  (double) (a + b) / 2.0;
    }
};

/*


*** For One Array Situation

L 左侧最大值, R 右侧最大值

比如, [2 3 4 5 6],we make the cut right through 4 like this:

[2 3 (4/4) 5 7], L = 4, R = 4,  (L + R)/2 = 4

We observe the index of L and R have the following relationship with the length of the array N:

N        Index of L / R
1               0 / 0
2               0 / 1
3               1 / 1  
4               1 / 2      
5               2 / 2
6               2 / 3
7               3 / 3
8               3 / 4


It is not hard to conclude that index of L = (N-1)/2, and R is at N/2. 
Thus, the median can be represented as
        (L + R)/2 = (A[(N-1)/2] + A[N/2])/2



To get ready for the two array situation, let's add a few imaginary 'positions' (represented as #'s) in between numbers, and treat numbers as 'positions' as well.

[6 9 13 18]  ->   [# 6 # 9 # 13 # 18 #]    (N = 4)
position index     0 1 2 3 4 5  6 7  8     (N_Position = 9)
		  
[6 9 11 13 18]->   [# 6 # 9 # 11 # 13 # 18 #]   (N = 5)
position index      0 1 2 3 4 5  6 7  8 9 10    (N_Position = 11)


As you can see, there are always exactly 2*N+1 'positions' regardless of length N. 
Therefore, the middle cut should always be made on the Nth position (0-based). 
Since index(L) = (N-1)/2 and index(R) = N/2 in this situation, 

we can infer that index(L) = (CutPosition-1)/2, index(R) = (CutPosition)/2.



*** Now for the two-array case:

A1: [# 1 # 2 # 3 # 4 # 5 #]    (N1 = 5, N1_positions = 11)

A2: [# 1 # 1 # 1 # 1 #]     (N2 = 4, N2_positions = 9)

We can also make the following observations：


1. There are 2N1 + 2N2 + 2 position altogether. Therefore, 
        there must be exactly N1 + N2 positions on each side of the cut, and 2 positions directly on the cut.

2. Therefore, when we cut at position C2 = K in A2, then the cut position in A1 must be C1 = N1 + N2 - k. 
    For instance, if C2 = 2, then we must have C1 = 4 + 5 - C2 = 7.

        [# 1 # 2 # 3 # (4/4) # 5 #]    

        [# 1 / 1 # 1 # 1 #]   
3. When the cuts are made, we'd have two L's and two R's. They are

        L1 = A1[(C1-1)/2]; R1 = A1[C1/2];
        L2 = A2[(C2-1)/2]; R2 = A2[C2/2];
In the above example,

    L1 = A1[(7-1)/2] = A1[3] = 4; R1 = A1[7/2] = A1[3] = 4;
    L2 = A2[(2-1)/2] = A2[0] = 1; R2 = A1[2/2] = A1[1] = 1;

Now how do we decide if this cut is the cut we want?  we only need
    
    L1 <= R1 && L1 <= R2 && L2 <= R1 && L2 <= R2
 */

class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int N1 = nums1.size();
        int N2 = nums2.size();
        if (N1 < N2) return findMedianSortedArrays(nums2, nums1);	// Make sure A2 is the shorter one.

        int lo = 0, hi = N2 * 2;
        while (lo <= hi) {
            int mid2 = (lo + hi) / 2;   // Try Cut 2 
            int mid1 = N1 + N2 - mid2;  // Calculate Cut 1 accordingly

            double L1 = (mid1 == 0) ? INT_MIN : nums1[(mid1-1)/2];	// Get L1, R1, L2, R2 respectively
            double L2 = (mid2 == 0) ? INT_MIN : nums2[(mid2-1)/2];
            double R1 = (mid1 == N1 * 2) ? INT_MAX : nums1[(mid1)/2];
            double R2 = (mid2 == N2 * 2) ? INT_MAX : nums2[(mid2)/2];

            if (L1 > R2) lo = mid2 + 1;		// A1's lower half is too big; need to move C1 left (C2 right)
            else if (L2 > R1) hi = mid2 - 1;	// A2's lower half too big; need to move C2 left.
            else return (max(L1,L2) + min(R1, R2)) / 2;	// Otherwise, that's the right cut.
        }
        return -1;
    } 
};




/*


if (mid1 < mid2) keep nums1.right + nums2
else keep nums1 + nums2.right

Complexity: O(log(m+n))
 */
class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int l = (m+n+1)/2,  r = (m+n+2)/2;
        //l,r 不是index, 是个数
        return (getKth(nums1, 0, nums2, 0, l) + getKth(nums1, 0, nums2, 0, r))/2.0;
    } 
    
    double getKth(vector<int>& nums1, int start1, vector<int>&nums2, int start2, int k){
        
         // If nums1 is exhausted, return kth number in nums2
        if(start1 >= nums1.size())
            return nums2[start2 + k -1];

        // If nums2 is exhausted, return kth number in nums1
        if(start2 >= nums2.size())
            return nums1[start1 + k -1];
        
        // Since nums1 and nums2 is sorted, the smaller one among the start point of nums1 and nums2 is the first one
        if(k == 1)
            return min(nums1[start1], nums2[start2]);
        
        int mid1 = numeric_limits<int>::max(), mid2 = numeric_limits<int>::max();
        if(start1 + k/2 - 1 < nums1.size()) mid1 = nums1[start1 + k/2 -1 ];
        if(start2 + k/2 - 1 < nums2.size()) mid2 = nums2[start2 + k/2 -1 ];
        
        // Throw away half of the array from nums1 or nums2. And cut k in half

        if(mid1 < mid2)
            return getKth(nums1, start1 + k/2, nums2, start2, k - k/2); //比如 k = 3, mid = 1, 用了1个数，所以k - k/2
        else 
            return getKth(nums1, start1, nums2, start2 + k/2 , k - k/2);
    }
};


//从后往前
class Solution {
public:
    int getkth(int s[], int m, int l[], int n, int k){
        // let m <= n
        if (m > n) 
            return getkth(l, n, s, m, k);
        if (m == 0)
            return l[k - 1];
        if (k == 1)
            return min(s[0], l[0]);

        int i = min(m, k / 2), j = min(n, k / 2);
        if (s[i - 1] > l[j - 1])
            return getkth(s, m, l + j, n - j, k - j);
        else
            return getkth(s + i, m - i, l, n, k - i);
        return 0;
    }
    
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int l = (m + n + 1) >> 1;
        int r = (m + n + 2) >> 1;
        return (getkth(A, m ,B, n, l) + getkth(A, m, B, n, r)) / 2.0;
    }
};
