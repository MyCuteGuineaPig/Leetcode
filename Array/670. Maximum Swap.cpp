/*
670. Maximum Swap

Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
Note:
The given number is in the range [0, 108]


*/

/*
Solution1: use bucket
思路: 尽可能让大的数在右面, 小的数在左面; 
比如 1991, 换的是第二个9 而不是第一个9, 变成9911 (9191 < 9911)
bucket 记录每个字母最后一次出现的位置

Limit to O(1) using curmax
比如With '8745' as an example, when we first consider 8, 我们发现后面没有比8的大的数字, 所以下次开始就不用从9开始，从8开始

*/

class Solution {
public:
    int maximumSwap(int num) {
        string n = to_string(num);
        vector<int>bucket(10, -1);
        for(int i = 0; i<n.size(); i++)
            bucket[n[i]-'0'] = i;

        int curmax = 9;
        for(int i = 0; i<n.size();i++){
            for(int j = curmax; j>n[i]-'0'; j--){
                if(bucket[j]>i){
                    swap(n[i], n[bucket[j]]);
                    return stoi(n);
                }
            }
            curmax = n[i]- '0';
        }   
        return num;
    }
};



/*
43456  ->   63454
109090901 -> 909090101
98368 -> 98863

Solution2: One pass from back to begin
从往后前, 一边记录当前最大数的index, 当 当前数<最大数: 
    需要swap的两个数为 i, 和 maxdigit(最大数的index)
*/
class Solution {
public:
    int maximumSwap(int num) {
        string n = to_string(num);
        int first = n.size()-1, last = n.size()-1;
        int maxdigit = n.size()-1;
        for(int i = n.size()-1; i>=0; i--){
            if(n[i]>n[maxdigit]){
                maxdigit = i;
            }
            else if(n[i]<n[maxdigit]){
                first = i;
                last = maxdigit;
            }
        }
        if(first == n.size()-1) return num;
        swap(n[last], n[first]);
        return stoi(n);
    }
};

/*
Like 31题: next permutation

1. 从左向右找reversed list第一个数变大的 (比如: 54367, cut 成543 | 67), 第一个部分是sort的, 不用cut, 只需要从第二部分找数跟第一部分换

2. 找到第二部分最大的数和相应的index( example, digit 7 in 54367)

3. 交换最大的数跟第一部分第一个小于它的数  (Example, swap 7 with 5 in 54367)
Time Complexity is O(n)

*/
class Solution {
public:
    int maximumSwap(int num) {
        string n = to_string(num);
        int break_pt = n.size();
        for(int i = 0; i+1<n.size(); i++){
            if(n[i]<n[i+1]){
                break_pt = i;
                break;
            }
        }

        if(break_pt == n.size()) return num; //all number has sorted already
        int second_max = n[break_pt+1], second_maxid = break_pt+1;
        for(int i = break_pt+1; i<n.size(); i++){
            if(n[i]>=second_max){
                second_max = n[i];
                second_maxid = i;
            }
        }
        for(int i = 0; i<=break_pt; i++){
            if(n[i]<second_max){
                swap(n[i], n[second_maxid]);
                return stoi(n);
            }
        }
        return num;
    }
};

/*
尝试所有的置换的方法：比如个位换十位, 十位换百位
*/
class Solution {
public:
    int maximumSwap(int num) {
        int maxi = 0;
        for (int p=1; p<=num; p*=10)
            for (int q=p; q<=num; q*=10)
                maxi = max(maxi, num + num/p%10*(q-p) + num/q%10*(p-q)); //num/p%10*(q-p) + num/q%10*(p-q)) 加上在p位上差的, 减去q位上多的
        return maxi;
    }
};