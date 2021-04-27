class Solution {
public:
    string nextClosestTime(string time) {
        set<int>st; 
        for(int i = 0; i<5; ++i){
            if(i == 2) continue;
            st.insert(time[i]-'0');
        }
        string res = time;
        char low = *st.begin() + '0';
        for(int i = 4; i>=0; --i){
            if(i == 2) continue;
            auto it = st.upper_bound(time[i] - '0');
            
            if(it != st.end() && (i == 4 || i == 3 && *it < 6 || i==1 && ( res[0] != '2' || *it < 4 ) || i == 0 && *it < 3)){
                
                res[i] = '0' + *it;
                for(int j = i+1; j<=4; ++j){
                    if(j==2) continue;
                    res[j] = low;
                }
                return res;
            }
        }
        
        return string(1,low) + string(1,low) + ":" + string(1,low) + string(1,low);
    }
};