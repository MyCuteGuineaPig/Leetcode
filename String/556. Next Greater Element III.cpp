/*
556. Next Greater Element III

Given a positive 32-bit integer n, you need to find the smallest 32-bit integer 
which has exactly the same digits existing in the integer n and is greater in value than n. 
If no such positive 32-bit integer exists, you need to return -1.

Example 1:

Input: 12
Output: 21
 

Example 2:

Input: 21
Output: -1

*/

//15432 -> 25431 -> 21345
// 432141 -> 432411

/*
用ascending stack(越晚push的数越大) 寻找比现在数i 最后一个大的数(和现在数越接近的)，比如4316511, 第三个1往后最后一个比1大的是5，

找到最后一个比现在数大的，两个数互换位置, 再reverese i往后倒结尾的所有数(因为现在i后面的数是从大到小 从左到右排序，我们要找后面最小的，reverse即可)

比如
Input:
2302541
Expected:
2304125

stack 存的是[4(5),5(4), 6(1)]
当到 i = 3, 2 < 4, pop stack 最后一个比2大的是4， 4和2换位置 变成 2304521, 再reverse 4后面的521变成2304125

*/

class Solution {
public:
    int nextGreaterElement(int n) {
        string temp = to_string(n);
        stack<int>stk;
        for(int i = temp.size() - 1; n; i--, n/=10){
            if(stk.empty() || temp[stk.top()] - '0' <= n%10){
               stk.push(i);
            }
            else{
                int last;
                while(!stk.empty() && temp[stk.top()] - '0' > n%10){
                    last = stk.top();
                    stk.pop();
                }
                swap(temp[i], temp[last]);
                reverse(temp.begin()+i+1, temp.end());
                if (temp.size()>=10 && temp > "2147483647") return -1; //只允许是integer, 避免overflow
                return stoi(temp);
            }
        }
        return -1;
    }
};


class Solution {
public:
    int nextGreaterElement(int n) {
        string str = to_string(n);
	    int N= str.size();
	    int i = N-2;
	    while(i >= 0 && str[i+1] <= str[i])
		    i--;
	    if(i < 0) return -1;
	    int j = N-1;
	    while(j > i && str[i] >= str[j]) //找到最后一个比s[i] 大的
		    j--;
	    swap(str[i], str[j]);
	    //cout << i << " " << j << endl;
	    reverse(str.begin()+i+1, str.end()); // swap str[i] and str[j] won't affect the decreasing order from i+1, reverse to increasing order.
	    long long ret = stol(str);
	    if(ret > INT_MAX)
		    return -1;
	    return ret;
    }
};


/**
 * 1. a max number has the property of decreasing in every digit: 9876
 * 2. find the first non-max substring from the right; ex. in 1234(59876), 59876 is the first non-max substring from the right
 * 3. sort the max part of 5(9876), by reverse, becames 5(6789);
 * 4. flip 5,6, becames 65789; because 6 is the next smallest digit than 5, in 56789;
 * 5. incase of 66789, you got flip 6 with 7 to make it 76689, to make it bigger.
 */
class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        if (s.length() == 1) {
            return -1;
        }
        /* find the first decreasing digit from the right, eg: 59876, 5 is the first decreasing digit */
        int i = s.length() - 2; // 21 -> i = 0; 59876 -> i = 3
        for (; i >= 0 && s[i] >= s[i + 1]; i--) { }
        if (i == -1) {  // if a decreasing digit cannot be find, the number cannot be larger.
            return -1;
        }
        reverse(s.begin() + i + 1, s.end());
        for (int j = i + 1; j < s.length(); j++) {
            if (s[j] > s[i]) {
                swap(s[i], s[j]);
                break;
            }
        }
        long next = stol(s);
        return next == n || next > INT_MAX ? -1 : next;
    }
};


class Solution{
public:
    int nextGreaterElement(int n) {
        auto digits = to_string(n);
        next_permutation(begin(digits), end(digits));
        auto res = stoll(digits);
        return (res > INT_MAX || res <= n) ? -1 : res;
    }
};

class Solution {
public:
    int nextGreaterElement(int n) {
        string nums = to_string(n);
        if(!nextPermutation(nums)) return -1; 
        long long result=stoll(nums);
        return (result>INT_MAX || result<=n)? -1:result;
    }
private:
    bool nextPermutation(string& nums) {
        if(nums.empty()) return false;
        int i=nums.size()-1;
        while(i>=1 && nums[i]<=nums[i-1]) i--;
        if(i==0) return false; // no next permutation, i.e. already largest
        
        int j=nums.size()-1;
        while(nums[j]<=nums[i-1]) j--;
        swap(nums[i-1],nums[j]);
        
        reverse(nums.begin()+i,nums.end());
        return true;
    }
};



// Time:  O(logn) = O(1)
// Space: O(logn) = O(1)

class Solution {
public:
    int nextGreaterElement(int n) {
        auto digits = to_string(n);
        nextPermutation(begin(digits), end(digits));  // self-implemented next_permutattion()
        auto result = stoll(digits);
        return (result > numeric_limits<int>::max() || result <= n) ? -1 : result;
    }

private:
    template<typename BidiIt>
    bool nextPermutation(BidiIt begin, BidiIt end) {
        const auto rbegin = reverse_iterator<BidiIt>(end);
        const auto rend = reverse_iterator<BidiIt>(begin);
        
        // Find the first element (pivot) which is less than its successor.
        auto pivot = next(rbegin);
        while (pivot != rend && *pivot >= *prev(pivot)) {
            ++pivot;
        }

        bool is_greater = true;
        if (pivot != rend) {
            // Find the number which is greater than pivot, and swap it with pivot
            auto change = find_if(rbegin, pivot, bind1st(less<int>(), *pivot));
            swap(*change, *pivot);
        } else {
            is_greater = false;
        }
        
        // Make the sequence after pivot non-descending
        reverse(rbegin, pivot);
        
        return is_greater;
    }
};