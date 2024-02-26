/*

需要first index: 因为想要尽早的set nums = 0 


a. Why backwards? 
Because after zeroing out a number you have to make sure that there is enough time to mark it as well. 
By going backwards we can keep track of the available time in the future.

当time_available==0 时候, 必须要drop 一个, time_available == 0 表示后面没有时间来heap中的点

最后heap 保留的是，最大number可以被zero out的
*/

class Solution {
public:
    bool isPossible(vector<int>& nums, vector<int>& changeIndices, unordered_map<int,int>& first_index_to_value_mp, int bound){
        int time_available = 0;
        vector<long>heap;
        for(int i = min(bound, (int)changeIndices.size()) - 1; i >= 0; --i){
            if (first_index_to_value_mp.count(i)) {
                heap.push_back(-nums[first_index_to_value_mp[i]-1]);
                //cout<<" [i push] "<<i<<" val "<<nums[first_index_to_value_mp[i]-1]<<" time_available "<<time_available<<endl;
                push_heap(heap.begin(), heap.end());

                if (time_available > 0) {
                    --time_available ;
                } else {
                    time_available += 1;
                    //cout<<" i pop "<<i<<" val "<<nums[first_index_to_value_mp[i]-1]<<endl;
                    pop_heap(heap.begin(), heap.end());
                    heap.pop_back();
                    //pop_heap does not remove elements from the container. It can't, since it doesn't even have access to the container
                }
            } else {
                ++time_available;
            }
        }
        long nums_total = accumulate(nums.begin(), nums.end(), 0L);
        long q_total = -accumulate(heap.begin(), heap.end(), 0L);
        long decrement_total = nums_total - q_total + nums.size() - heap.size();
        long mark_zero = heap.size() * 2;
        //cout<<" decrement_total "<<decrement_total <<" nums_total "<< nums_total <<" q_total "<<q_total<<" heap.size() " << heap.size()<<" mark_zero "<<mark_zero<<endl;
        return decrement_total + mark_zero <= bound;
    }


    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        unordered_map<int, int>first_index, first_index_to_value_mp;
        int m = changeIndices.size();
        for(int i = 0; i <m; ++i){
            if (first_index.count(changeIndices[i]) == 0 && nums[changeIndices[i]-1]!=0){
                first_index[changeIndices[i]] = i;
            }
        }
        for(auto it: first_index){
            first_index_to_value_mp[it.second] = it.first;
        }
        int low =0 , high = m + 1;
        while (low < high){
            int mid = (low + high)/2;
            if (isPossible(nums, changeIndices, first_index_to_value_mp, mid)){
                high = mid;
                //cout<<" low "<<low <<" high "<<high << " mid "<<mid<<" possible "<<endl;
            } else {
                //cout<<" low "<<low <<" high "<<high << " mid "<<mid<<" not possible "<<endl;
                low = mid + 1;
            }
        }
        return low > m? -1: low;

    }
};