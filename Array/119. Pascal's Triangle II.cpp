/*
119. Pascal's Triangle II


Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.

Note that the row index starts from 0.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 3
Output: [1,3,3,1]
Follow up:

Could you optimize your algorithm to use only O(k) extra space?


*/

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int>res(rowIndex+1, 1);
        for(int i = 2; i<=rowIndex; i++){
            for(auto j = i-1; j>=1; j--){
                res[j] = res[j] + res[j-1];
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex + 1);
        for (int i = 0; i < result.size(); ++i) {
            int prev_result = result[0] = 1;
            for (int j = 1; j <= i; ++j) {
                const int tmp = result[j];
                result[j] += prev_result;
                prev_result = tmp;
            }
        }
        return result;
    }
};

/*
Two considerations:

At Nth row, each k-th element is determined by a well-known formula: C(n, k) = n! / (k!*(n-k)!). Obviously, we don't want to calculate factorial each time since we need to fill in the whole row, so we can just multiply both the numerator and denominator sequentially

A row in Pascal triangle is always symmetric, so we fill up two elements at each loop iteration

A drawback: In order to avoid overflows, we need to employ ugly casts to unsigned long
*/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> r;
        r.resize(rowIndex + 1);
        r[0] = r[rowIndex] = 1;
        for(auto i = 1; i < (r.size() + 1)/2; ++i)
        {
            r[i] = r[rowIndex - i] = (unsigned long)r[i - 1]*(unsigned long)(rowIndex - i + 1)/i;
        }
        return r;
    }
};