/*
526. Beautiful Arrangement

Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array
 that is constructed by these N numbers successfully 
 if one of the following is true for the ith position (1 <= i <= N) 
 in this array:

The number at the ith position is divisible by i.
i is divisible by the number at the ith position.
Now given N, how many beautiful arrangements can you construct?

Example 1:
Input: 2
Output: 2
Explanation: 

The first beautiful arrangement is [1, 2]:

Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

The second beautiful arrangement is [2, 1]:

Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
Note:
N is a positive integer and will not exceed 15.

*/

/*
faster on for swap
*/
class Solution {
public:
    int countArrangement(int N) {
        vector<int> A;
        for(int i = 1; i<=N; i++)
            A.push_back(i);
        return count(N,A);
    }
    
    int count(int n, vector<int>& A){
        if(n<=0) return 1;
        int cnt = 0;
        for(int i = 0; i<n;i++){
            if(A[i]%n == 0 || n%A[i] == 0){ //把A[i] 换到n的位置是beautiful arrangment 先换过去
                swap(A[i],A[n-1]);
                cnt += count(n-1, A);
                swap(A[n-1],A[i]);
            }
        }
        return cnt;
    }
};


class Solution {
public:
    int countArrangement(int N) {
        vector<int> A(N);
        int i = 1;
        for_each(A.begin(),A.end(),[&](int &a){ a = i++;});
        return backtrack(N,1,A);
    }

    int backtrack(int N, int pos, vector<int>&A){
        if(pos>N) return 1;
        int cnt = 0;
        for(int i = 0; i<N; i++){
            if(A[i]>0 && (A[i]%pos == 0  || pos%A[i] == 0 )){
                A[i] *= -1;
                cnt += backtrack(N, pos+1, A);
                A[i] *= -1;
            }
        }
        return cnt;
    }
};