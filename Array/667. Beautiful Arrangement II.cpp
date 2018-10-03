/*
667. Beautiful Arrangement II

Given two integers n and k, you need to construct a list which contains n different positive integers ranging from 1 to n and obeys the following requirement: 
Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.

If there are multiple answers, print any of them.

Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.
Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.
Note:
The n and k are in the range 1 <= k < n <= 104.

*/

/*
思路: 
如果有n个数, 最大的k可以是 n-1;
if n is 9, max k is 8.

This can be done by picking numbers interleavingly from head and tail,

// start from i = 1, j = n;
// i++, j--, i++, j--, i++, j--

i: 1   2   3   4   5
j:   9   8   7   6
out: 1 9 2 8 3 7 4 6 5
dif:  8 7 6 5 4 3 2 1

Above is a case where k is exactly n - 1
When k is less than that, simply lay out the rest (i, j) in incremental
order(all diff is 1). Say if k is 5:

     i++ j-- i++ j--  i++ i++ i++ ...
out: 1   9   2   8    3   4   5   6   7
dif:   8   7   6   5    1   1   1   1 

*/


class Solution {
public:
vector<int> constructArray(int n, int k) {
	vector<int>table;
	for (int i = 1, j = n; i <= j; i) {
		if (k > 0)
		{
			table.push_back(k-- % 2 ? i++ : j--); //要保证当k--(K=1)之后, k为0时, 操作的是 i++
		}
		else table.push_back(i++);
	}
	return table;
}
};

/*

This leads to the following idea: we will put [1, 2, ...., n-k-1] first, 
and then we have N = k+1 adjacent numbers left, of which we want k different differences. 

This is just the answer above translated by n-k-1: we'll put [n-k, n, n-k+1, n-1, ....] after.

需要k+1个因为第一个是 n-k-1 (之前的) 和 (n-k) 差1, 最后的也是差1, 比如 n = 9, k = 4: 1,2,3,4,5,9,6,8,7  
*/

class Solution {
public:
vector<int> constructArray(int n, int k) {
        vector<int>table(n-k-1);
        iota(table.begin(), table.end(), 1);
        for (int i = 0; i < k + 1; i++) {
            if(i%2 == 0) table.push_back(n-k + i/2);
            else table.push_back(n- i/2);
        }
        return table;
    }
};


class Solution {
public:
    vector<int> constructArray(int n, int k) 
    {
        
        //example 
        // n = 6 k = 1 -> 1 2 3 4 5 6
        // n = 6 k = 5 -> 1 6 2 5 3 4
        
        // n = 6 k = 3 -> 1 2 3 6 4 5
        // n = 6 k = 4 -> 1 2 6 3 5 4
        
        vector<int> res(n, 0);
        
        for(int i = 0 ; i < (n-k) ; i++ )
        {
            res[i] = i+1;
        }
        
        int lhs = n-k;
        int rhs = n;
        bool r = true;
        
        for(int i = n-k; i < n; i++)
        {
            int val = 0;
            
            if(r)
            {
                val = rhs;
                rhs--;
            }
            else
            {
                val = lhs +1;
                lhs++;
            }           
            r=!r;
            res[i] = val;
        }
        return res;
    }
};



/*
The requirement of k distinct distance can be achieved from 1, 2, ..., k+1 (<= n), by the following strategy:

1, k+1, 2, k, 3, k-1 ...;
The distance of this sequence is k, k-1, k-2, ..., 2, 1
Then append the remaining numbers to the list.
*/
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        int l = 1, r = k+1;
        vector<int> ans;
        while (l <= r) {
            ans.push_back(l++);
            if (l <= r) ans.push_back(r--);
        }
        for (int i = k+2; i <= n; i++)
            ans.push_back(i);
        return ans;
    }
};