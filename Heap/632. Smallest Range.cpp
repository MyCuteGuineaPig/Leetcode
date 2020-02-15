/*
632. Smallest Range

You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
Note:
The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.
For Java users, please note that the input type has been changed to List<List<Integer>>. 
And after you reset the code template, you'll see this point.

*/


/*

A Better efficient approach is to use min heap. Below are the steps –

Create a min heap of size k and insert first elements of all k lists into the heap.

Maintain two variables min and max to store minimum and maximum values present in the heap at any point. 
Note min will always contain value of the root of the heap.

Repeat following steps

Get minimum element from heap (minimum is always at root) and compute the range.
Replace heap root with next element of the list from which the min element is extracted. 
After replacing the root, heapify the tree. Update max if next element is greater. 
If the list doesn’t have any more elements, break the loop.

data structure: minHeap;
思路：
1. 开始时候先把每个vector的最左面[0]的数push 进heap, 并记录最大值和最小值，
2. 每次heap top 返回当前的最小值， 
    - 如果返回的最小值是某个vector最后一位数， return
    - 把这个数的所在vector的当前index +1，index+1后的数 push 进heap，最大值 = max(最大值，新加的数)
    - 现在heap top是新的最小数，  如果最大值-最小值小于 < interval, 更新interval
    

*/


//Self
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        if(nums.empty()) 
            return {};
        using IT = vector<int>::const_iterator;
        auto cmp = [](const pair<IT,IT>&a, const pair<IT,IT>&b){return *(a.first)>*(b.first); };
        priority_queue<pair<IT,IT>, vector<pair<IT,IT>>, decltype(cmp)>pq(cmp);
        int curmax = 0;
        for(auto& num: nums){//必须用reference, 否则报错,因为auto num是copy, 没有reference,
            //在for loop 在这个for loop后destroy
            curmax = max(curmax,num.front());
            pq.push({num.begin(), num.end()});
        }
        int range = curmax - *(pq.top().first);
        vector<int>res = {*(pq.top().first),curmax };
        while(true){
            IT begin, end; 
            tie(begin,end) = pq.top(); pq.pop();
            if(curmax - *begin < range)
            {
                range = curmax - *begin;
                res = {*begin, curmax};
            }
            
            if(begin+1 == end)
                break;
            curmax = max(curmax, *next(begin));
            pq.push({begin+1, end});
        }
        /*
        //while 也可以这么写
        while(true){
            IT begin, end; 
            tie(begin,end) = pq.top(); pq.pop();
            if(++begin == end)
                break;
            pq.push({begin, end});
            curmax = max(curmax, *begin);
            if(curmax - *(pq.top().first) < range)
            {
                range = curmax - *(pq.top().first);
                res = {*(pq.top().first), curmax};
            }
        */
        return res;
    }
};



class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        using VIT = vector<int>::iterator;
        
        const auto comp = [](const pair<VIT, VIT>& p1, const pair<VIT, VIT>& p2) {
                              return *p1.first > *p2.first;
                          };
        
        int left = numeric_limits<int>::max(), right = numeric_limits<int>::min();
        priority_queue<pair<VIT, VIT>, vector<pair<VIT, VIT>>, decltype(comp)> min_heap(comp);
        for (auto &row : nums) {
            left = min(left, row[0]);
            right = max(right, row[0]);
            min_heap.emplace(row.begin(), row.end());
        }
        
        vector<int> result = {left, right};
        while (!min_heap.empty()) {
            auto p = min_heap.top();
            min_heap.pop();
            ++p.first;
            if (p.first == p.second) {
                break;
            }
            min_heap.emplace(p);
            
            left = *min_heap.top().first;
            right = max(right, *p.first);
            if (right - left < result[1] - result[0]) {
                result = {left, right};
            }
        }
        return result;
    }
};




class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>minheap; 
        //vector[0] = value, vector[1] = 所属的vector，vector[2] = 现在value的index
        int minval = numeric_limits<int>::max(), maxval = numeric_limits<int>::min();
        for(int k = 0; k<nums.size();k++){
            maxval = max(maxval,nums[k][0]);
            minval = min(minval,nums[k][0]);
            minheap.push({nums[k][0],k,0});
        }
        vector<int>range = {minval, maxval};
        while(true){
            vector<int>cur = minheap.top();
            minheap.pop();
            if(cur[2] == nums[cur[1]].size()-1) 
                break;//last one
            cur[0] = nums[cur[1]][++cur[2]];
            minheap.push(cur);
            minval = minheap.top()[0];
            maxval = max(maxval,cur[0]);
            if(maxval-minval<range[1]-range[0])
                range = {minval, maxval};
        }
        return range;
    }
};

class Solution {
public:  //maxheap 从后往前弄
    vector<int> smallestRange(vector<vector<int>>& nums) {
        auto cmp = [](pair<int, int> a, pair<int, int> b) {
            return a.first < b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
        vector<int> r(2);
        int m2=INT_MAX;
        
        for (int i=0; i < nums.size(); ++i) {
            if (nums.empty()) break;
            m2=min(m2, nums[i].back());
            q.push(make_pair(nums[i].back(), i));
            nums[i].pop_back();
        }
        
        int len=INT_MAX, m1;
        
        while (q.size() == nums.size()) {
            auto n =q.top();
            m1 = n.first;
            //cout << " m1: " << m1 << " m2:" << m2 << endl;
            if (len >= m1-m2) {
                r[0]=m2;
                r[1]=m1; 
                len = m1-m2;
            }
            
            q.pop();
            
            if (!nums[n.second].empty()) {
                q.push(make_pair(nums[n.second].back(), n.second));
                m2= min(nums[n.second].back(), m2);
                nums[n.second].pop_back();
            }            
        }
        
        return r;
    }
};
