/*
239. Sliding Window Maximum

Given an array nums, there is a sliding window of size k
 which is moving from the very left of the array to the very right. 
 You can only see the k numbers in the window. 
 Each time the sliding window moves right by one position. 
 Return the max sliding window.

Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Note: 
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?



*/



/*
Multiset solution
Complexity: O(nlogn)
Space O(n)

*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(k>nums.size() || k == 0) return {};
        auto cmp = [](int a, int b){return a>b;};
        multiset<int,decltype(cmp)>s(cmp);
        for(int i = 0; i<k; i++){
            s.insert(nums[i]);
        }
        vector<int>res;
        res.push_back(*s.begin());
        for(int i = k; i<nums.size();i++){
            int start = i-k;
            s.erase(s.find(nums[start]));
            s.insert(nums[i]);
            res.push_back(*s.begin());
        }
        return res;
    }
};


/*
Sliding window minimum/maximum = monotonic queue. I smelled the solution just when I read the title.
This is essentially same idea as others' deque solution, 
but this is much more standardized and modulized. 
If you ever need to use it in your real product, 
this code is definitely more preferable.

What does Monoqueue do here:

It has three basic options:

push: push an element into the queue; O (1) (amortized)

pop: pop an element out of the queue; O(1) (pop = remove, it can't report this element)

max: report the max element in queue;O(1)

It takes only O(n) time to process a N-size sliding window minimum/maximum problem.

Note: different from a priority queue (which takes O(nlogk) to solve this problem), 
it doesn't pop the max element: It pops the first element (in original order) in queue.



*/



class Monoqueue
{
    deque<pair<int, int>> m_deque; //pair.first: the actual value, 
                                   //pair.second: how many elements were deleted between it and the one before it.
    public:
        void push(int val)
        {
            int count = 0;
            while(!m_deque.empty() && m_deque.back().first < val)
            {
                count += m_deque.back().second + 1;
                m_deque.pop_back();
            }
            m_deque.emplace_back(val, count);//val代表他之前有多少个元素
        };
        int max()
        {
            return m_deque.front().first;
        }
        void pop ()
        {
            if (m_deque.front().second > 0)
            {
                m_deque.front().second --;
                return;
            }
            m_deque.pop_front();
        }
};
struct Solution {
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> results;
        Monoqueue mq;
        k = min(k, (int)nums.size());
        int i = 0;
        for (;i < k - 1; ++i) //push first k - 1 numbers;
        {
            mq.push(nums[i]);
        }
        for (; i < nums.size(); ++i)
        {
            mq.push(nums[i]);            // push a new element to queue;
            results.push_back(mq.max()); // report the current max in queue;
            mq.pop();                    // pop first element in queue;
        }
        return results;
    }
};

/*
[1,3,-1,-3,5,3,6,7]
3


nums[i] 1 push ( 1, 0 ), 
 nums[i] 3 push ( 3, 1 ), 
 nums[i] -1 push ( 3, 1 ), ( -1, 0 ), 
 pop ( 3, 0 ), ( -1, 0 ), 
 nums[i] -3 push ( 3, 0 ), ( -1, 0 ), ( -3, 0 ), 
 pop ( -1, 0 ), ( -3, 0 ), 
 nums[i] 5 push ( 5, 2 ), 
 pop ( 5, 1 ), 
 nums[i] 3 push ( 5, 1 ), ( 3, 0 ), 
 pop ( 5, 0 ), ( 3, 0 ), 
 nums[i] 6 push ( 6, 2 ), 
 pop ( 6, 1 ), 
 nums[i] 7 push ( 7, 2 ), 
 pop ( 7, 1 ), 

*/


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<pair<int,int>>mq;
        /*
        first代表这个数，
        second 代表在windows中, windows开始位置到这个数之前，多少个比现在这个数小
        就是这个windows之前删除的数
        
        */
        vector<int>res;
        for(int i = 0; i<nums.size();i++){
            int count = 0;
            while(!mq.empty() && nums[i]>mq.back().first){
                count+=mq.back().second+1; 
                //加1是加上mq.back().first这个数，因为second算的是，在这个数之前比这个数小的，没算first这个数
                mq.pop_back();
            }
            mq.push_back({nums[i],count});
            if(i>=k-1){
                res.push_back(mq.front().first);
                if(mq.front().second>0)
                    mq.front().second--;
                else mq.pop_front();
            }
        }
        return res;
    }
};


/*
存单个index, deque中最大数的index存前面（deque是按大小排序的，并且按照出现的前后顺序排序)，
且front的index比backindex小，所以pop时候对比front是不是当前windows的


10,9,8,7,6,5,4  
3
O(n) 不需要进行while砍掉，
为了方便deque用数表示，实际上应用index表示
i = 0, deque = 10
i = 1, deque = 10, 9
i = 2, deque = 10, 9, 8 
i = 3, deque = 9,8,7


4，5，6，7，8，9，10
3
O(n) 每次砍掉前面小的
i = 0, deque = 4
i = 1, deque = 5
i = 2, deque = 6
i = 3, deque = 7
i = 3, deque = 8

*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int>q;
        vector<int>res;
        for(int i = 0; i<nums.size();i++){
            while(!q.empty() && nums[i]> nums[q.back()]){
                q.pop_back();
            }
            q.push_back(i);
            if(i>=k-1){
                res.push_back(nums[q.front()]);
                if(q.front()==i-k+1) //i-k+1 windows stat
                    q.pop_front();
            }
        }
        return res;
    }
};



/*

Brute Force
windowMax， maxIdx,  表示在i-1时最大的数和 最大数的位置

如果当前i小于等于maxIdx, 而windowMax， maxIdx,  表示在i-1时前最大的数 and最大数的位置
i比i-1相当于windows前进一位，所以只需对比windows此时最后一位nums[i+k-1] 和 maxIdx的大小

有可能是O(nk) k = 3
比如
10,9,8,7,6,5,4  
3
第一次loop 3个 10-8 最大是10，maxindex = 0,
第二次 i= 1 > maxIndex, loop3个 最大是9， maxindex = 1
第二次 i= 2 > maxIndex, loop3个 最大8， maxindex = 2


*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if (!n)
            return {};
        int maxIdx = -1, windowMax = INT_MIN;
        vector<int> res;
        for (int i = 0; i < n - k + 1; i++) {
            if (i <= maxIdx) {
                if (windowMax < nums[i + k - 1]) {
                    windowMax = nums[i + k - 1];
                    maxIdx = i + k - 1;
                }
                res.push_back(windowMax);
                continue;
            }
            windowMax = INT_MIN;
            for (int j = i; j < i + k; j++)
                if (windowMax < nums[j]) {
                    windowMax = nums[j];
                    maxIdx = j;
                }
            res.push_back(windowMax);
        }
        return res;
    }
};