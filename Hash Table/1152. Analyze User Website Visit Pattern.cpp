class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        unordered_map<string, map<int, string>>mp;
        unordered_map<string, int>cnt_mp;
        for(int i = 0; i < username.size(); ++i){
            mp[username[i]][timestamp[i]] = website[i];
        }
        for(auto user: mp){
            unordered_set<string>st;
            for(auto nxt0 =  user.second.begin(); nxt0 != user.second.end(); ++nxt0){
                for(auto nxt1 = next(nxt0); nxt1 != user.second.end(); ++nxt1){
                    for(auto nxt2 = next(nxt1); nxt2 != user.second.end(); ++nxt2){
                        //cout<<" nxt0->second= "<<nxt0->second<<" nxt1->second "
                        //    << (nxt1->second) << " nxt2->second "<< (nxt2->second)<<endl;
                        string cur = nxt0->second + "#"+ nxt1->second + "#"+ nxt2->second;
                        st.insert(cur);
                    }
                }
            }
            for(auto i: st){
                ++cnt_mp[i];
            }
        }
        int max_cnt = -1;
        string candidate = ""; 
        for(auto c: cnt_mp){   
            //cout<<c.first<<" c.second "<<c.second<<endl;
            if (c.second >max_cnt || c.second == max_cnt &&  c.first < candidate  ){
                max_cnt = c.second;
                candidate = c.first;
            }
        }
        int pos = candidate.find("#");
        int pos2 = candidate.find("#", pos + 1);
        return {candidate.substr(0, pos), candidate.substr(pos+1, pos2-pos-1), candidate.substr(pos2+1, candidate.size()-pos2-1)};
    }
};



Code Sample (Runtime: 19ms)

class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        typedef pair<int, string> PIS;
        unordered_map<string, vector<PIS>> ms;
        for (int i = 0; i < username.size(); i ++) 
            ms[username[i]].push_back({timestamp[i], website[i]});

        unordered_map<string, int> cnt;
        for (auto& [k, v] : ms) {
            unordered_set<string> ts;
            sort(v.begin(), v.end());
            for (int i = 0; i < v.size(); i ++)
                for (int j = i + 1; j < v.size(); j ++)
                    for (int u = j + 1; u < v.size(); u ++) 
                        ts.insert(v[i].second + '$' + v[j].second + '#' + v[u].second);
            for (auto& t : ts) cnt[t] ++;
        }

        string ans;
        int max_cnt = 0;
        for (auto& [k, v] : cnt) {
            if (v >= max_cnt) {
                if (ans == "" || v > max_cnt) ans = k;
                else ans = min(ans, k);
                max_cnt = v;
            }
        }

        auto p = ans.find('$'), q = ans.find('#');
        return {ans.substr(0, p), ans.substr(p + 1, q - p - 1), ans.substr(q + 1)};
    }
};