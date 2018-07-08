/*
421. Maximum XOR of Two Numbers in an Array

Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.

*/


/*
This algorithm's idea is:
to iteratively determine what would be each bit of the final result from left to right. 
And it narrows down the candidate group iteration by iteration. 
e.g. assume input are a,b,c,d,...z, 26 integers in total. 
In first iteration, if you found that a, d, e, h, u differs on the MSB(most significant bit), 
so you are sure your final result's MSB is set. 
Now in second iteration, you try to see if among a, d, e, h, u there are at least two numbers make the 2nd MSB differs, 
if yes, then definitely, the 2nd MSB will be set in the final result. 
And maybe at this point the candidate group shinks from a,d,e,h,u to a, e, h. 
Implicitly, every iteration, you are narrowing down the candidate group, 
but you don't need to track how the group is shrinking, you only cares about the final result.


example: Given [14, 11, 7, 2], which in binary are [1110, 1011, 0111, 0010].
Since the MSB is 3, I'll start from i = 3 to make it simplify.

i = 3, set = {1000, 0000}, max = 1000
i = 2, set = {1100, 1000, 0100, 0000}, max = 1100
i = 1, set = {1110, 1010, 0110, 0010}, max = 1100
i = 0, set = {1110, 1011, 0111, 0010}, max = 1100


set.contains(tmp ^ prefix)
//This is the most tricky part, coming from a fact that if a ^ b = c, then a ^ c = b;
// now we have the 'c', which is greedyTry, and we have the 'a', which is leftPartOfNum
// If we hope the formula a ^ b = c to be valid, then we need the b, 
// and to get b, we need a ^ c, if a ^ c exisited in our set, then we're good to go

从第32位开始到第0位逐渐缩小范围, 利用性质 a ^ b = c,  a ^ c = b, c是我们需要找的数，
每到一位就试下这位可不可以是1, temp = maxnum  | (1<<i)，如果可以是1，  temp ^ set[i] 也在set里面, 就update max number  maxnum = temp;

这样做，可以保证最高位的先被catch到，比如第五位，10000(25), 00000(2,3,5,8,10)，第五个1被catch到，or,

因为n ^ temp in set， 才更新max，所以最后的max 一定是来自两个数的xor（最后更新的那两个数的），而不是多个数构成的，
因为比如最后一次max 更新111000(temp) ^ 11000 = 1000 在set里，更新max，max = 11000 ^ 1000 



[3, 10, 5, 25, 2, 8] in binary [0b11 0b1010 0b101 0b11001 0b10 0b1000] 

第五位, set = [10000(25), 00000(2,3,5,8,10)], temp = 10000,  10000^10000 in map => max = 10000,  保证结果第五位必须一个是1，一个是0，不能同时为0 
第四位, set = [11000(25), 01000(10,8), 00000(2,3,5)], temp = 11000, 11000 ^ 11000 = 0 in map =>  max = 11000, 保证结果第五位 和第四位不能同时一样，而且两个数的第四位，第五位有且仅有一个1
第三位, set = [11000(25), 01000(10,8), 00100(5), 00000(2,3)], temp = 11100, 11100 ^ 11000 = 00100 in map => max = 11100
第二位  set = [11000(25),  01010(10),  01000(8), 00100(5),00010(2,3) ], temp = 11110, 没有满足的条件, max = 11100
第一位，set =  [11001(25), 001010(10), 01000(8), 00101(5), 00011(3), 00010(2)  ],temp = 11101, 没有满足的条件, max = 11100


since result has log(n) bits, the time complexity is nlogn

*/

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int maxnum = 0, mask = 0;
        for(int i = 31; i>=0; i--){
            mask = mask | (1<<i);
            unordered_set<int>prefix;
            for(auto n: nums)
                prefix.insert(n & mask);
            if(prefix.size() == 1) continue;
            int temp = maxnum | (1<<i);
            
            for(auto n: prefix){
                if(prefix.find(n ^ temp) != prefix.end()){
                    maxnum = temp;
                    break;
                }
            }
        }
        return maxnum;
    }
};


class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        
        for (int i = 31; i >= 0; --i) {
            result <<= 1;
            unordered_set<int> prefixes;
            for (const auto& n : nums) {
                prefixes.emplace(n >> i);
            }
            for (const auto& p : prefixes) {
                if (prefixes.count((result | 1) ^ p)) {
                    ++result; //也可以写成 result |= 1;  因为result <<=1 ，所以 result |= 1;等于++result;
                    break;
                }
            }
        }

        return result;
    }
};



/*

Trie
*/

class Solution {
private:
    class Trie{
    public:
        Trie *child[2]; 
        Trie(): child{nullptr, nullptr} {};
        
        void insert(int num){
            Trie* trie = this;
            for(int i = 31; i>=0; i--){
                int cur = num >> i & 1;
                if(trie->child[cur] == nullptr)
                    trie->child[cur] = new Trie(); 
                trie = trie->child[cur];
            }
        }
        
        int get(int num){
            Trie* trie = this;
            int res = 0;
            for(int i = 31; i>=0; i--){
                int curbit = num>>i & 1;
                if(trie->child[curbit ^ 1]){//当前位的结果是1
                    res |= 1<<i;
                    trie = trie->child[curbit ^ 1];
                }else{
                    trie = trie->child[curbit];
                }
            }
            return res;
        }
    };
    
    
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        Trie trie;
        for(auto i: nums) trie.insert(i);
        for(auto i: nums)
            result = max(result, trie.get(i));
        return result;
    }
};



class Solution {
public:
    class TreeNode {
    public:
        TreeNode* next[2];
        TreeNode () {next[0] = NULL; next[1] = NULL;};
    };
    TreeNode* buildTree(vector<int>& nums) {
        TreeNode* root = new TreeNode(), *cur;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            cur = root;
            for (int j = 31; j >= 0; j--) {
                int index = ((num >> j) & 1);
                if (cur->next[index] ==  NULL)
                    cur->next[index] = new TreeNode();
                cur = cur->next[index];
            }
        }
        return root;
    }
    
    int helper(TreeNode* cur, int num) {
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int index = ((num >> i) & 1) ? 0 : 1;
            if (cur->next[index]) {
                res <<= 1;
                res |= 1;
                cur = cur->next[index];
            } else {
                res <<= 1;
                res |= 0;
                cur = cur->next[index ? 0 : 1];
            }
        }
        return res;
    }
    
    int findMaximumXOR(vector<int>& nums) {
        int res = 0;
        TreeNode* root = buildTree(nums);
        
        for (auto i : nums) {
            res = max(res, helper(root, i));
        }
        
        return res;
    }
};