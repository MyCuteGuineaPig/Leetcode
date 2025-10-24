/*

要保证q是递减的，

因为如果q.back() > q.front(), 就不需要q.front(), 因为q.back()更大且更新更晚，q.front()永远不会被用到。



 */

 class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        deque<int>q;//monotinic decreasing queue
        int res = numeric_limits<int>::min();
        for(int i = 0; i < nums.size(); ++i){
            nums[i] += q.size() ? nums[q.front()] : 0;
            res = max(res, nums[i]);

            while (q.size() && nums[i] > nums[q.back()]) {
                //cout<<"pop "<<q.back()<<endl;
                q.pop_back();
            }
            if (nums[i] > 0) //必须在while 后，如果先插入，没办法pop 之前的数
                q.push_back(i);
            if (q.size() && q.front()== i - k){
                q.pop_front();
            }
        }
        return res;
    }
};