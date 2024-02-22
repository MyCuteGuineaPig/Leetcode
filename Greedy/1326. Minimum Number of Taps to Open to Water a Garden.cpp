class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int>dist(n+1);
        for(int i = 0; i<ranges.size(); ++i){
            int left = max(0, i - ranges[i]);
            dist[left] = max(dist[left], i + ranges[i]);
        }
        int end = 0, next = 0,  count = 0;
        for(int i = 0; i<=n && next <n; end = next){
            ++count;
            while(i <= end){
                next = max(next, dist[i++]);
            }
            if (end == next) return -1; 
            /*
            比如 [2      6]
                   [3  5]    => 这时候 end = 6, next = 6, 没有cover比6大的点
                            [7, 8]
            */
        }
        return next >= n? count: -1;
    }
};


class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int>dist(n+1);
        for(int i = 0; i<ranges.size(); ++i){
            int left = max(0, i - ranges[i]);
            dist[left] = max(dist[left], i + ranges[i]);
        }
        int end = 0, count = 0, next = 0;
        for(int i = 0; i<=n && end < n; i++){
            if ( i > end){
                if ( i > next) return -1; 
                //or if (end == next) return -1;
                ++count;
                end = next;
            }
            next = max(next, dist[i]);
        }
        return end >=n ? count: -1;
    }
};



class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int>dist(n+1);
        for(int i = 0; i<ranges.size(); ++i){
            int left = max(0, i - ranges[i]);
            dist[left] = max(dist[left], i + ranges[i]);
        }
        int end = 0, count = 0, next = 0;
        for(int i = 0; i<=n && end < n; i++){
            next = max(next, dist[i]); //如果用 i == end 必须把next = max(next, dist[i]) 放前面
            /*
            否则 
            比如 n = 5, [3,4,1,1,0,0]
                 i = 0, end = 0, 进来, update end = next = 0; 在if statement 外面, assign next = 5;
            then i = 1, end = 0, 进不来了, 因为 end 还等于0
            
            */
            if ( i == end){
                cout<<i<<" end "<<end<<endl;
                //or if (end == next) return -1;
                ++count;
                end = next;
            }
        }
        return end >=n ? count: -1;
    }
};


class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int>dp(n+1, n+2);
        dp[0] = 0;
        for(int i = 0; i<=n; ++i){
            for(int j = max(0, i-ranges[i] + 1); j<=min(n, i+ranges[i]); ++j){
                /*
                也可以是
                 max(0, i-ranges[i]）
                如果 j = max(0, i-ranges[i]), the first iteration will be 
                    dp[j] = min(dp[j], dp[j] + 1);, which is redundant.
                */
                dp[j] = min(dp[j], dp[max(0, i-ranges[i])]+1);
            }
        }
        return dp.back() < n+2 ? dp.back(): -1;
    }
};

class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<pair<int,int>>bound;
        for (int i = 0; i<=n; ++i){
            if (ranges[i]){
                bound.push_back({i-ranges[i], i+ranges[i]});
            }
        }
        if (bound.empty()) return -1;
        sort(bound.begin(), bound.end(), [](const pair<int,int>&a, const pair<int,int>&b){
            return a.first < b.first;});
        if (bound[0].first > 0) return -1;//if not cover 0

        int preright = -1; //preright 表示上个用的tap的右侧值
        int i = 0; 
        for(; i<bound.size() && bound[i].first <= 0; ++i) //skip less than zero, 
            preright = max(preright, bound[i].second);
        if (i == 0) return -1;

        int count = 1,  nextright = preright;//nextright 表示下个用的tap的最右侧值

        for(int i = 1; i<bound.size() && nextright < n; ++i){
            /*
            比如 [0, 8], [2,10], [9, 10] 到了9， 10， 更新preright同时还要++count
            */
            if(bound[i].first > preright){
                if (bound[i].first > nextright) return -1; //比如[0,10], [12,13] 没有cover 10-12
                preright = nextright;
            }

            //当preright == nextright 表示下个tab 还没有，此时设置下个tab
            if (preright==nextright && bound[i].second > preright){
                ++count;
            }
            nextright = max(nextright, bound[i].second);
        }
        return nextright < n ? -1 : count;
    }
};