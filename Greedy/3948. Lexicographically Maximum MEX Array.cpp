/*

Phase 1: Finding the Maximum Target (max_possible)

while cnt[max_possible] > 0:
    max_possible += 1 

Before we pick any elements, we look at our remaining pool of numbers (cnt). 

This while loop starts checking from 0. If 0 is in our pool, it checks 1.
If 1 is there, it checks 2, and so on. The loop stops at the first non-negative integer that is completely missing from the remaining pool.


Phase 2: The "Worst Case" Escape Hatch


if max_possible == 0:
    res.append(0)
    cnt[nums[i]] -= 1 
    i += 1 
    continue 

If max_possible == 0, it means the number 0 is completely missing from the remaining pool of numbers.

If 0 is missing, then no matter how many elements we take (whether we take 1 element or 50 elements), 
the MEX of that chunk will always be 0.

Because a longer array is lexicographically greater than a shorter one, we want to stretch out our results as much as possible. 
Since we can't get a MEX higher than 0, we greedily take just one single element, append 0 to our results, remove that element from our pool, and skip the rest of the logic for this turn.



Phase 3: Collecting the Chunk

seen = set() 
while i < n and len(seen) < max_possible:
    if nums[i] < max_possible:
        seen.add(nums[i])
    cnt[nums[i]] -= 1 
    i += 1


If max_possible is greater than 0 (say, it equals 3), it means the numbers 0, 1, and 2 are all available 
somewhere down the line. To get a MEX of 3, our subarray must contain at least one copy of 0, 1, and 2.

This while loop acts like a net moving left-to-right:

1. It looks at the current number nums[i].
2. If that number is useful to us (i.e., it's strictly less than max_possible), we throw it into our seen set.
3. We permanently remove nums[i] from our global pool (cnt[nums[i]] -= 1) because we are consuming it.
4. We move our pointer forward (i += 1).

When does it stop?
The moment len(seen) == max_possible. 

In our example, the exact moment our set contains 0, 1, and 2 (a size of 3), the loop breaks. 
We have successfully found the shortest possible prefix that guarantees our maximum MEX target!



A Visual Example Imagine nums = [0, 1, 0].

Phase 1: cnt has {0: 2, 1: 1}. The loop checks 0 -> checks 1 -> checks 2. max_possible becomes 2.
Phase 2: max_possible is not 0, so we skip this.
Phase 3: We loop through nums.
 - i = 0: nums[0] is 0. It's < 2, so seen = {0}. cnt[0] becomes 1.
 - i = 1: nums[1] is 1. It's < 2, so seen = {0, 1}. cnt[1] becomes 0.
 - Loop condition len(seen) < max_possible becomes False. Loop stops!

We successfully consumed exactly [0, 1] to get our maximum MEX of 2.

*/

/*
input = [3, 0, 4, ,0 ,1] 
return = [2] 

need unordered_set to capture the unique elements in the current chunk, 
because we only care about whether we have seen 0, 1, and 2 at least once.

*/


class Solution {
public:
    vector<int> maximumMEX(vector<int>& nums) {
        unordered_map<int, int>cnt;
        for(auto i: nums) 
            cnt[i]++;

        int max_possible = 0;
        int i = 0, n = nums.size();
        vector<int>res;
        while(i < n ) {
            while(cnt[max_possible] > 0)
                max_possible += 1;

            if (max_possible == 0) {
                res.push_back(0);
                --cnt[nums[i++]];
                continue;
            }

            unordered_set<int>seen;
            while(i< n && seen.size() < max_possible) {
                if (nums[i] < max_possible){
                    seen.insert(nums[i]);
                }
                --cnt[nums[i++]];
            }

            res.push_back(max_possible);
            max_possible = 0;
        }
        return res;
    }
};