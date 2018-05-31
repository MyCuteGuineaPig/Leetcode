"""
88. Merge Sorted Array

Example:

Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
"""

class Solution:
    def merge(self, nums1, m, nums2, n):
        """
        :type nums1: List[int]
        :type m: int
        :type nums2: List[int]
        :type n: int
        :rtype: void Do not return anything, modify nums1 in-place instead.
        """
        i = m+n-1
        m -= 1
        n -= 1
        while n>=0:
            if m<0 or nums1[m]< nums2[n]:
                nums1[i] = nums2[n]
                n-=1
            else:
                nums1[i] = nums1[m]
                m-=1
            i-=1 

class Solution:
    def merge(self, nums1, m, nums2, n):
        while m > 0 and n > 0:
            if nums1[m-1] >= nums2[n-1]:
                nums1[m+n-1] = nums1[m-1]
                m -= 1
            else:
                nums1[m+n-1] = nums2[n-1]
                n -= 1
        if n > 0:
            nums1[:n] = nums2[:n]



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
            print(nums1);
        }
    }

    void print(vector<int>vec){
        for(auto i: vec)
            cout<<i<<", ";
        cout<<endl;
    }
};