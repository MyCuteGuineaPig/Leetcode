/*
275. H-Index II

Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?


H-Index Question: 

Given an array of citations (each citation is a non-negative integer) of a researcher, 
write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each,
 and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], 
which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. 
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each,
his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.



*/


/*
citations[mid] 小于h 不满足至少有h个数大于等于h，像右移，增大citations[mid]，减小h，
*/

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int l = 0, r = citations.size()-1;
        while(l<=r){
            int mid = l + (r-l)/2;
            if(citations[mid]<citations.size()-mid) //citations[mid] 是 至少大于hcitation的起点，citations.size()-mid是h，
            /*
            如果起点小于h, 那么更小的N-h点，都会小于h，
            证明左面的情况符合，向右移动
            其次，
            如果citations[mid]（右侧起始点）<citations.size()-mid = h,证明右侧的点有小于h的，不符，像右侧动让N-h 变大，h变小，

            */
                l = mid+1;
            else r = mid-1; 
            /*
            citations[mid]>=citations.size()-mid, citation[mid]>=h, mid和mid 右侧至少h个点大于等于h
            citations[mid]>=h， 左侧起点大于等于h，左侧可能相符，也可能不符,所以像左移动一点
            比如：
            [1,2,6,8,10,11,13],  size = 7 mid是3，h = 4, c[mid] = 8 >= 4： 右侧满足，但是左侧[1,2,6] 不满足因为6小于等于4

            */
        }
        return citations.size()-l;
    }
};


/*
       [ 1 2 3 4 5 6]
    
    1. l = 0, r = 5, mid = 2, h=4, nums[mid] = 3 ----> left = mid + 1 = 3

    2. l = 3, r = 5, mid = 4, h = 2, nums[mid] = 5 ----> right = mid -1 = 3

    3. l = 3, r = 3,  mid = 3, h = 3, nums[mid] = 4 ----> r = mid - 1 = 2;

       [0]  => 0
    1. l = 0, r = 0, mid = 0, h = 1, nums[mid] = 0 < h, left = mid +1 = 1

       [1]  = > 1, 
    1. l = 0, r = 0, mid = 0, h = 1, nums[mid] = 0 >= h, right = mid - 1 = 0


    nums[a] 

       1 5 6 7 8 9  5  

       1 2 6 7 8 9  4

*/



/*
Just binary search, each time check citations[mid]
case 1: citations[mid] == len-mid, then it means there are citations[mid] papers that have at least citations[mid] citations.
case 2: citations[mid] > len-mid, then it means there are citations[mid] papers that have moret than citations[mid] citations, 
    so we should continue searching in the left half
case 3: citations[mid] < len-mid, we should continue searching in the right side
After iteration, it is guaranteed that right+1 is the one we need to find (i.e. len-(right+1) papars have at least len-(righ+1) citations)
*/



class Solution {
public:
    int hIndex(vector<int>& citations) {
        int left=0, len = citations.size(), right= len-1,  mid;
        while(left<=right)
        {
            mid=(left+right)>>1;
            if(citations[mid]== (len-mid)) return citations[mid];
            else if(citations[mid] > (len-mid)) right = mid - 1;
            else left = mid + 1;
        }
        return len - (right+1);
    }
};
or simplified version

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int left=0, len = citations.size(), right= len-1,  mid;
        while(left<=right)
        {
            mid=left+ (right-left)/2;
            if(citations[mid] >= (len-mid)) right = mid - 1;
            else left = mid + 1;
        }
        return len - left;
    }
};

/*
The basic idea of this solution is to use binary search to find the minimum index such that

citations[index] >= length(citations) - index
After finding this index, the answer is length(citations) - index. 最小的index，最大的h

This logic is very similar to the C++ function lower_bound or upper_bound.

*/


class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        for (int i = 0; i < n; i++)
            citations[i] -= (n - i); 
        for(auto j: citations):
            cout<<j<<endl;
        auto lb = lower_bound(citations.begin(), citations.end(), 0);
        return n - (lb - citations.begin());
    }
}; 