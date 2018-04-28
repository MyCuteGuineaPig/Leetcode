/*
823. Binary Trees With Factors
Given an array of unique integers, each integer is strictly greater than 1.

We make a binary tree using these integers and each number may be used for any number of times.

Each non-leaf node's value should be equal to the product of the values of it's children.

How many binary trees can we make?  Return the answer modulo 10 ** 9 + 7.

Example 1:

Input: A = [2, 4]
Output: 3
Explanation: We can make these trees: [2], [4], [4, 2, 2]
Example 2:

Input: A = [2, 4, 5, 10]
Output: 7
Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
 

Note:

1 <= A.length <= 1000.
2 <= A[i] <= 10 ^ 9.


*/

/*
[2,3,6,18] 

[2], [3], [6], [18],
[6, 2, 3], [6,3,2]
[18,6,3], [18,3,6]
[18,6,3,2,3], [18,6,2,3,3],
[18,3,6,2,3], [18,3,6,3,2]

[2] = 1 
[3] = 1
[6] = 1 + 2*1*1 = 3
[18] = 1+3*1*2
*/



class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        const long M = 1e9 + 7; long res = 0;
        sort(A.begin(),A.end());
        unordered_map<int,long>map;
        
        for(int i = 0; i<A.size(); i++){
            map[A[i]] = 1;
            for(int j = 0; j<i && A[j]<=sqrt(A[i]);j++){
                if(A[i]%A[j] == 0 && map.count(A[i]/A[j])){
                    if(A[i] == A[j]*A[j]){
                        map[A[i]]  = (map[A[i]] + map[A[j]]*map[A[j]]);
                    }
                    else{
                        map[A[i]] = (map[A[i]] + 2*map[A[j]]*map[A[i] / A[j]]);
                    }
                    
                }
            }
            res = (res+map[A[i]])%M;
        }
        return res;
    }
};