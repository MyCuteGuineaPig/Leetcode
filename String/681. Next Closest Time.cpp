/*
scan from back to beginning, if found digit bigger than current digit, change it to the next larger digit 
    and change the digit after it to the lowest digit

Limit: 
 for minutes: cannot bigger than 59 
 for hourse: cannot bigger than 23
*/
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

                for(int j = i+1; j<=4; ++j){ //change the digit after it to the lowest digit
                    if(j==2) continue;
                    res[j] = low;
                }
                return res;
            }
        }
        
        return string(1,low) + string(1,low) + ":" + string(1,low) + string(1,low);
    }
};


class Solution {
public:
    string nextClosestTime(string time) {
        set<char> sorted;
        for(auto c:time){
            if(c==':') continue;
            sorted.insert(c);
        }
       
        string res = time;
        for(int i = time.size() -1; i>=0; i--){
            if(time[i] == ':' ) continue;
            auto it = sorted.find(time[i]);
             if(*it != *sorted.rbegin()){// not the largest number
                it++; // go to the next element
                res[i] = *it;
                if((i>=3 && stoi(res.substr(3,2))<60) ||(i<2&&stoi(res.substr(0,2))<24))       
                    return res;      
             } 
             res[i]=*sorted.begin(); // take the smallest number
        }
        return res;   
    }
};