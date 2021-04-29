class Solution {
public:
    int kEmptySlots(vector<int>& bulbs, int k) {
        vector<int>arr(bulbs.size());
        for(int i=0; i< bulbs.size();++i){
            arr[bulbs[i]-1] = i + 1; //i + 1 is day
        }

        int res = arr.size()+2;
        int start = 0, right = k + 1;
        for(int i = 1; right < arr.size(); ++i){
            if(arr[i] > arr[start] && arr[i] > arr[right]){
                continue;
            }
            if(i == right){
                res = min(res, max(arr[start], arr[right]));
            }
            start = i;
            right = start + k + 1;
        }
        return res > arr.size() ? -1: res;
    }
};



/*
MinQueue: 

比如: [6,5,8,9,7,1,10,2,3,4] 
      2
ans = 8

windows 是不包括左右点的windows, 保证中间点是最小的

days:  [6, 8, 9, 10, 2, 1, 5, 3, 4, 7]
              [9, 10]
            8 < 9  && 9 > 2 
        
*/
class MinQueue{
    private: 
        deque<int>minq;
        queue<int>q;
    
    public:
        void push(int val){
            while(minq.size() && minq.back() > val){
                minq.pop_back();
            }
            minq.push_back(val);
            q.push(val);
        }
    
        void pop(){
            if(q.front() == minq.front())
                minq.pop_front();
            q.pop();
        }
    
        int getMin(){
            return minq.front();
        }
    
};

class Solution {
public:
    int kEmptySlots(vector<int>& bulbs, int k) {
        vector<int>days(bulbs.size());
        for(int i=0; i< bulbs.size();++i){
            days[bulbs[i]-1] = i + 1; //i + 1 is day
        }

        int res = days.size()+2;
        MinQueue q;

        for(int i = 0; i < days.size()-1; ++i){
            q.push(days[i]);
            if(i >= k){
                q.pop();
                 if(k ==0 || days[i-k] < q.getMin() && q.getMin() > days[i+1])
                    res = min(res, max(days[i-k], days[i+1]));
            }
        }
        return res > days.size() ? -1: res;
    }
};


/*
O(NLogN)
*/
class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        set<int> bloom;
        for (int i = 0; i < flowers.size(); i++) {
            int p = flowers[i];
            auto it = bloom.insert(p).first;
            if (it != bloom.begin()) {
                if (p-*(--it) == k+1) return i+1;
                it++;
            }
            if (++it != bloom.end() && *it-p == k+1) return i+1; 
        }
        return -1;
    }
};