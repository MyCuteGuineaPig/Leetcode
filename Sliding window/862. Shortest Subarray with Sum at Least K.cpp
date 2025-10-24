/*

看queue 是increasing 还是decreasing 
关键看 given windows, 
        如果前面的值更大好 -> decreasing queue ,  如果后面出现更大值，前面的更小值就没用了
            while (q.size() && nums[i] >= nums[q.back()]){   => 前面的值不能比它小
                q.pop_back();
            }

        如果前面的值更小好 -> increasing queue， 同理 如果后面出现更小值，前面的更大值就没用了
        while (q.size() && presum[i] <= presum[q.back()]) => 前面的值不能比它大
                q.pop_back();

Queue 是monotonic increasing queue
比如 index1 < index2 
    Queue[nums[index1]] < Queue[nums[index2]]
那么到 i点 
    nums[i] - nums[index1] >=  nums[i] - nums[index2]

    移动左侧index, sum越小，范围也在缩小    


第二个while loop 不可以是if 

比如  
          [-34,37,-12,-50,51,100]
presum = [ -34, 3, -9, -59, -8, 92]
                        ^
                        |
                        需要清空所有的 queue, 之前的 -9, -34都要清空

    
需要第二个while loop 来保持 queue的increasing property, 
   如果presum[i] <= presum[queue.back()],  因为i点的presum更小， index更大
    queue.back()有小的负数存在， 以后也不会被用到， 因为presum[] - presum[i] 已经更大了，表示可以用i点之后来计算subarray sum

 */
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        deque <int> q; //increasing queue q.push_back(0);
        int n = nums.size();
        vector<long>presum(n);
        int res = n + 1;
        for(int i = 0; i < n; ++i){
            presum[i] = ( i ? presum[i-1]: 0) + nums[i];
            if (presum[i] >= k)
                res = min(res, i+1);
            /** 两个while order 可以互换 */
            while (q.size() && presum[i] - presum[q.front()] >= k) {
                res = min (res, i - q.front() );
                q.pop_front();
            } 
            while (q.size() && presum[i] <= presum[q.back()])
                q.pop_back();
            q.push_back(i);
        }
        return res == n + 1 ? -1 : res;
    }
};


class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        deque <int> q; //increasing queue q.push_back(0);
        int n = nums.size();
        vector<long>presum(n);
        int res = n + 1;
        for(int i = 0; i < n; ++i){
            presum[i] = ( i ? presum[i-1]: 0) + nums[i];
            if (presum[i] >= k)
                res = min(res, i+1);
            while (q.size() && presum[i] <= presum[q.back()])
                q.pop_back();
            while (q.size() && presum[i] - presum[q.front()] >= k) {
                res = min (res, i - q.front() );
                q.pop_front();
            } 
            q.push_back(i);
        }
        return res == n + 1 ? -1 : res;
    }
};