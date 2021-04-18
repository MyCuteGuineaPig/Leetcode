class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<int>res, idx(tasks.size());
        priority_queue<pair<int,int>>pq;
        iota(idx.begin(), idx.end(),0);
        sort(idx.begin(), idx.end(), [&](int i, int j){return tasks[i][0] < tasks[j][0];});
        long time = 0; //需要long 否则overflow 
        for(int i = 0; i < idx.size() || !pq.empty(); ){
            while(i < idx.size() && tasks[idx[i]][0] <= time){
                pq.push({-tasks[idx[i]][1], -idx[i]});
                ++i;
            }
            if(!pq.empty()){
                auto [process, cur] = pq.top(); pq.pop();
                time -= process;
                res.push_back(-cur);
            }
            else
                time = tasks[idx[i]][0];
        }
        return res;
    }
};


class Solution {
    typedef pair<int, int> T; // processing time, index
public:
    vector<int> getOrder(vector<vector<int>>& A) {
        priority_queue<T, vector<T>, greater<>> pq; // min heap of tasks, sorted first by processing time then by index.
        long N = A.size(), time = 0, i = 0; // `time` is the current time, `i` is the read pointer
        for (int i = 0; i < N; ++i) A[i].push_back(i); // append the index to each task
        sort(begin(A), end(A)); // sort the input array so that we can take the tasks of small enqueueTime first
        vector<int> ans;
        while (i < N || pq.size()) { // stop the loop when we exhausted the input array and the tasks in the heap.
            if (pq.empty()) {
                time = max(time, (long)A[i][0]); // nothing in the heap? try updating the current time using the processing time of the next task in array
            }
            while (i < N && time >= A[i][0]) { // push all the tasks in the array whose enqueueTime <= currentTime into the heap
                pq.emplace(A[i][1], A[i][2]);
                ++i;
            }
            auto [pro, index] = pq.top();
            pq.pop();
            time += pro; // handle this task and increase the current time by the processingTime
            ans.push_back(index);
        }
        return ans;
    }
};