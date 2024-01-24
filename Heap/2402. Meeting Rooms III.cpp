class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        auto cmp = [](const vector<long>&a, const vector<long>&b){
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] > b[0];
        };
        priority_queue<vector<long>, vector<vector<long>>, decltype(cmp)>pq;
        //[0] is the room [1] end time
        priority_queue<int, vector<int>, greater<int>> avail_room; 
        for(int i = 0; i<n; ++i) avail_room.push(i);
        sort(meetings.begin(), meetings.end());
        vector<long>cnt(n, 0);
        for(int i = 0; i<meetings.size(); ++i){
            while(pq.size() && pq.top()[0] <= meetings[i][0]) {
                auto top = pq.top(); pq.pop();
                avail_room.push(top[1]);
            }
            int room;
            long next_end;
            if(avail_room.empty()){
                auto top = pq.top(); pq.pop();
                long end = top[0];
                room = top[1];
                next_end = end + (meetings[i][1] -  meetings[i][0]);
            }
            else {
                room = avail_room.top(); avail_room.pop();
                next_end = meetings[i][1];
            }
            ++cnt[room]; 
            pq.push({next_end, room});
        }
        int max_used = 0;
        int room_number = 0;
        for(int i = 0; i<n; ++i){
            if (cnt[i] > max_used){
                max_used = cnt[i];
                room_number = i;
            }
        }
        return room_number;
    }
};



class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        auto cmp = [](const pair<long, int>&a, const pair<long, int>&b){
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first > b.first;
        };
        priority_queue<pair<long, int>, vector<pair<long, int>>, decltype(cmp)>pq;
        sort(meetings.begin(), meetings.end());
        for(int i = 0; i<n; ++i) pq.push({meetings[0][0], i});
        
        vector<long>cnt(n, 0);

        for(int i = 0; i<meetings.size(); ++i){
            while(pq.top().first < meetings[i][0]){
                pq.push({meetings[i][0], pq.top().second});
                pq.pop();
            }
            
            auto [start, room] = pq.top(); pq.pop();
            ++cnt[room]; 
            pq.push({start + meetings[i][1] - meetings[i][0], room});
        }
        return max_element(cnt.begin(), cnt.end()) - cnt.begin();
    }
};