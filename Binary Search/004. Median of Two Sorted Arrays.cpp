/*
4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5


*/

/*
解释
https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/Share-my-O(log(min(mn))-solution-with-explanation?page=3


更新A的ilow 和ihigh, j = (m+n+1)/2-1,
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
                if(i>0) maxleft = max(maxleft,nums1[i-1]);
                if(j>0) maxleft = max(maxleft,nums2[j-1]);
                if(i>0 && j>0) maxleft = max(nums2[j-1], nums1[i-1]);
                if((m+n)&1) return maxleft;
                
                if(i<m) minright = min(minright, nums1[i]);
                if(j<n) minright = min(minright, nums2[j]);
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