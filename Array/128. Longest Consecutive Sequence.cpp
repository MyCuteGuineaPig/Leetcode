/*
128. Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

Your algorithm should run in O(n) complexity.

Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.



*/

/*
先把所有数放进hash set 然后每次pop 一个数，设lower = n-1, upper = n+1, 持续pop lower--, upper++, 结果是max(res, upper-lower-1)

*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int>st;
        for(auto i: nums) st.insert(i);
        int maxbound = 0;
        while(!st.empty()){
            int num = *st.begin(); st.erase(st.begin());
            int lowerbound = num - 1;
            while(st.find(lowerbound)!=st.end()){
                st.erase(lowerbound--);
            }
            int upperbound = num + 1;
            while(st.find(upperbound)!=st.end()){
                st.erase(upperbound++);
            }
            maxbound = max(maxbound, upperbound-lowerbound-1);
        }
        return maxbound;
    }
};



class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> allNums;
        for(auto n : nums) 
            allNums.insert(n);
        
        int longestRun = 0;
        int currentRun = 1;
        for(auto n : allNums){
            if(allNums.count(n-1)) continue;
            while(allNums.count(n+1)){
                currentRun++;
                n++;
            }
            longestRun = max(longestRun, currentRun);
            currentRun = 1;
        }
        
        return longestRun;
    }
};



/*
update 现在bound两侧的值

hashmap 表示以现在点为边界点，最长的连续数列长 

比如 1-5 是连续的, 只用保证hashmap[1] = hashmap[5] = 5 即可

因为每次update 看是不是已经有这个数，如果有的话，不update，没有的话，比如现在hashmap[1] = hashmap[5] = 5, 没有的话肯定不在[1,5]之间, 
1 - leftbound 是最左面边界，  1 + rightbound 最右侧边界

We will use HashMap. The key thing is to keep track of the sequence length 
and store that in the boundary points of the sequence. 
For example, as a result, for sequence {1, 2, 3, 4, 5}, map.get(1) and map.get(5) should both return 5.

Whenever a new element n is inserted into the map, do two things:

See if n - 1 and n + 1 exist in the map, and if so, 
it means there is an existing sequence next to n. 

Variables left and right will be the length of those two sequences, 
while 0 means there is no sequence and n will be the boundary point later. 

Store (left + right + 1) as the associated value to key n into the map.

Use left and right to locate the other end of the sequences to the left and right of n respectively, 
and replace the value with the new length.
Everything inside the for loop is O(1) so the total time is O(n). 

*/

class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        unordered_map<int, int> hash;
        int ans{1};
        for (const auto& i : nums) {
            if (!hash[i]) {
                hash[i] = 1;
                int leftbound{hash[i - 1]}, rightbound{hash[i + 1]}; // Get neighbor info.
                //cout<<i<<" leftbound "<<leftbound<<" rightbound "<<rightbound<<endl;
                hash[i - leftbound] = hash[i + rightbound] = 1 + leftbound + rightbound; // Update left and right bound info.
                ans = max(ans, 1 + leftbound + rightbound);
            }
        }
        return ans;
    }
};

class Solution {
public:
    int longestConsecutive(vector &num) {
        unordered_map<int, int> m;
        int r = 0;
        for (int i : num) {
            if (m[i]) continue;
            r = max(r, m[i] = m[i + m[i + 1]] = m[i - m[i - 1]] = m[i + 1] + m[i - 1] + 1);
        }
        return r;
    }
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> allNums;
        for(auto n : nums) 
            allNums.insert(n);
        
        int longestRun = 0;
        int currentRun = 1;
        for(auto n : allNums){
            if(allNums.count(n-1)) continue;
            while(allNums.count(n+1)){
                currentRun++;
                n++;
            }
            longestRun = max(longestRun, currentRun);
            currentRun = 1;
        }
        
        return longestRun;
    }
};