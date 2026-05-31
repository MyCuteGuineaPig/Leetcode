

/*

This problem is based on line sweep algorithm if you feel difficult go through these quesiton.
Maximum Population Year -> 1854
Points That Intersect With Cars -> 2848
Car Pooling -> 1094
My Calendar II -> 731
Shifting Letters II -> 2381
Perfect Rectangle -> 391
Rectangle Area II -> 850
Number of Flowers in Full Bloom -> 2251
*/


// 注意： 只能choose at most two non-overlapping events to attend such that the sum of their values is maximized.
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

        int pre_max = 0, res = 0; 
        for(auto event: events) {
            while(!pq.empty() && pq.top().first < event[0]) {
                pre_max = max(pre_max, pq.top().second);
                pq.pop();
            }
            //cout<<" event "<<event[0] <<" pre_max "<<pre_max<<" event[2] + pre_max " <<event[2] + pre_max <<endl;
            res = max(res, event[2] + pre_max);
            pq.push({event[1],event[2]});
        }
        return res;
    }
};



class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        vector<vector<int>> times;
        for(auto& event: events){
            times.push_back({event[0], 1, event[2]});
            times.push_back({event[1] + 1, -1, event[2]}); //pay attention here is event[1] + 1
        }
        sort(times.begin(), times.end());
        int pre_max = 0; 
        int res = 0;
        for(auto time: times) {
            if(time[1] == 1) {
                res = max(res, time[2] + pre_max);
            } else {
                pre_max = max(pre_max, time[2]);
            }
        }
        return res;
    }
};


class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());
        vector<vector<int>> dp(events.size(), vector<int>(3, -1));
        return findEvents(events, 0, 0, dp);
    }
    // Recursive function to find the greatest sum for the pairs.
    int findEvents(vector<vector<int>>& events, int idx, int cnt,
                   vector<vector<int>>& dp) {
        if (cnt == 2 || idx >= events.size()) return 0;
        if (dp[idx][cnt] == -1) {
            int end = events[idx][1];
            int lo = idx + 1, hi = events.size() - 1;
            while (lo < hi) {
                int mid = lo + ((hi - lo) >> 1);
                if (events[mid][0] > end)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            int include =
                events[idx][2] + (lo < events.size() && events[lo][0] > end
                                      ? findEvents(events, lo, cnt + 1, dp)
                                      : 0);
            int exclude = findEvents(events, idx + 1, cnt, dp);
            dp[idx][cnt] = max(include, exclude);
        }
        return dp[idx][cnt];
    }
};