//sort
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        sort(clips.begin(), clips.end());
        if(clips.front()[0]!=0) return -1;
        int end = 0, next = 0, count = 0; 
        for(int i = 0; i<clips.size() && next < time; ++i){
            if(clips[i][0] > end){
                if (clips[i][0] > next) return -1;
                end = next;
            }

            if (end == next && clips[i][1] > end) {
                ++count;
            }

            next = max(next, clips[i][1]);
        }
        return next<time ? -1: count;
    }
};

//Greedy,  while
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int n = clips.size(); 
        vector<int>dp(time, 0);
        for(auto c: clips){
            if (c[0] >= time) continue;
            dp[c[0]] = max(dp[c[0]], min(time, c[1]));
        }
        int count = 0, next = 0, end = 0;
        for(int i = 0; i<time && end < time; end = next){
            ++count;
            while(i <= end){
                next = max(next, dp[i++]);
            }
            if (end == next) return -1;
        }
        return end < time ? -1: count;
    }
};


//Greedy,  i == end
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int n = clips.size(); 
        vector<int>dp(time, 0);
        for(auto c: clips){
            if (c[0] >= time) continue;
            dp[c[0]] = max(dp[c[0]], min(time, c[1]));
        }
        int count = 0, next = 0, end = 0;
        for(int i = 0; i<time && end < time; ++i){
            next = max(next, dp[i]);
            if ( i == end){
                ++count; 
                end = next;
            }
        }
        return end < time ? -1: count;
    }
};

//Greedy,  i > end
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int n = clips.size(); 
        vector<int>dp(time+1, 0);
        for(auto c: clips){
            if (c[0] >= time) continue;
            dp[c[0]] = max(dp[c[0]], min(time, c[1]));
        }
        int count = 0, next = 0, end = 0;
        for(int i = 0; i<=time && end < time; ++i){//不像上个需要 i<=time, 而不是i<time 
        //比如当 [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 9
        // i = 10的时候, 才会更新count, 更新end 为10

            //cout<<i<<" end "<<end<<" next "<<next<<endl;
            if ( i > end){
                if (i > next) return -1;
                ++count; 
                end = next;
            }
            next = max(next, dp[i]);
        }
        return end < time ? -1: count;
    }
};

//DP
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int n = clips.size(); 
        vector<int>right(time+1, 0);
        for(auto c: clips){
            if (c[0] >= time) continue;
            right[c[0]] = max(right[c[0]], min(time, c[1]));
        }
        vector<int>cnt(time+1, time+2);
        cnt[0] = 0;
        for(int i = 0; i<time; ++i){
            for(int j = i; j <= right[i] && j <= time; ++j){
                cnt[j] = min(cnt[j], cnt[i]+1);
            }
        }
        return cnt.back() > time ? -1: cnt.back();
    }
};