/*
88. Merge Sorted Array

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:

The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
Example:

Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]

1 2 4 7 0 0 0 
2 5 6 

1 2 4 7 2  i=0,1 j = 0

1 2 2 7 4 5 6 
1 2 2 4 5 6




*/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n-1, k = m+n-1;
        while(i>=0 && j>=0){
            if(nums1[i]>=nums2[j]) nums1[k--] = nums1[i--];
            else nums1[k--] = nums2[j--];
        }
        while(j>=0) nums1[k--] = nums2[j--];
    }
};

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i = 0, j = m; j<m+n;){
            if(i< m && nums1[i]<=nums2[j-m]){
                nums1[j] = nums2[j-m];
                i++;
            }
            else if (i<m){
                nums1[j] = nums1[i];
                nums1[i] = nums2[j-m];
                i++;
            }else{
                nums1[j] = nums2[j-m];
                j++;
            }
        }
    }
};



//2020
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i = m+n-1, i1 = m-1, i2 = n -1; i2>=0 ; --i){
            if(i1 >= 0 && nums1[i1] > nums2[i2])
                nums1[i] = nums1[i1--];
            else 
                nums1[i] = nums2[i2--];
        }
    }
};
