/*
564. Find the Closest Palindrome


Given an integer n, find the closest integer (not including itself), which is a palindrome.

The 'closest' is defined as absolute difference minimized between two integers.

Example 1:
Input: "123"
Output: "121"
Note:
The input n is a positive integer represented by string, whose length will not exceed 18.
If there is a tie, return the smaller one as answer.

*/

/*

If the final answer has the same number of digits as the input string S, 
then the answer must be the middle digits + (-1, 0, or 1) flipped into a palindrome. 
For example, 23456 had middle part 234, and 233, 234, 235 flipped into a palindrome yields 23332, 23432, 23532. 
Given that we know the number of digits, the prefix 235 (for example) uniquely determines the corresponding palindrome 23532, 
so all palindromes with larger prefix like 23732 are strictly farther away from S than 23532 >= S.

If the final answer has a different number of digits, it must be of the form 999....999 or 1000...0001, 
as any palindrome smaller than 99....99 or bigger than 100....001 will be farther away from S.


最接近的回文一定是前半部分 +1, +0, -1 加上前半部分的reverse(如果长度是奇数，reverse不包括前半部分最后一个，如果长度是偶数，都包括在内)
比如 23456, 最短palidrome 一定是23432, 23532, 23332 之间, 
比如 2345, 最短palidrom, 一定是2222, 2332, 2442 之间

还要考虑边界条件，因为有时可能边界，比如10, 三个pal 是11, 22, 00, 但是答案应该是9, 
同样情况也适用于 10**size + 1
*/

class Solution {
public:
    string nearestPalindromic(string n) {
        int size = n.size();
        long long prefix = stol(n.substr(0, (size+1)/2));
        unordered_set<long long>st;
        st.insert(static_cast<long long>(pow(10, size))+1);
        st.insert(static_cast<long long>(pow(10, size-1))-1);
        for(auto i: {-1, 0, 1}){
            string pre = to_string(prefix+i);
            string p = pre + string(pre.rbegin() + (size % 2), pre.rend());
            st.insert(stol(p));
        }
        long long res = numeric_limits<long long>::max() , mindiff = numeric_limits<long long>::max(), num = stol(n);
        st.erase(num);
        
        for(auto i: st){
            if(abs(i - num )<mindiff){
                mindiff = abs(i-num);
                res = i;
            }else if(abs(i - num ) == mindiff && i < res)
                res = i;
        }
        return to_string(res);
    }
};