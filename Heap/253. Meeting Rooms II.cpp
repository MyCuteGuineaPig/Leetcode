class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int res = 0;
        priorty_queue<int, vector<int>, greater<int>>pq;
        for(auto &i: intervals){
            while (!pq.empty() && pq.top() <= i[0]) pq.pop();
            pq.push(i[1]);
            res = max(res, pq.size());
        }
        return res;
    }
};
//可以用map 来控制区间，区间开始+1, 结束-1， 看哪里最多
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> m;
        for (auto &t : intervals)
            m[t[0]]++, m[t[1]]--;
        int cur = 0, res = 0;
        for (auto &it : m){
            res = max(res, cur += it.second);
            cout<<" it "<<it.first <<" second "<<it.second<<endl;
        }
        return res;
    }
};


//可以decouple 一个meeting room的 start end
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> starts, ends;
        for (auto i : intervals) {
            starts.push_back(i[0]);
            ends.push_back(i[1]);
        }
        sort(begin(starts), end(starts));
        sort(begin(ends), end(ends));
        int e = 0, rooms = 0, available = 0;
        for (int start : starts) {
            while (ends[e] <= start) {
                ++e;
                ++available;
            }
            available ? --available : ++rooms;
        }
        return rooms;
    }
};

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int res = 0;
        priority_queue<int,vector<int>,greater<int>>pq;
        sort(intervals.begin(),intervals.end());
        for(auto i: intervals){
            if(pq.size() && pq.top() <= i[0]) pq.pop(); //因为每次只需要占一个room, pop 一个
            pq.push(i[1]);
            res = max(res, (int)pq.size());
        }
        return res;
    }
};

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int res = 0; 
        sort(intervals.begin(), intervals.end());
        multiset<int>pq;
        for(int i = 0; i<intervals.size(); ++i){
            while(pq.size() && *pq.begin() <= intervals[i][0])
                pq.erase(pq.begin());
            pq.insert(intervals[i][1]);
            res = max(res, (int)pq.size());
        }
        return res;
    }
};