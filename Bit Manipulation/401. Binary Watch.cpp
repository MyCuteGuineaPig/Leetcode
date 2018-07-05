/*
401. Binary Watch


A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, 
return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".

*/


class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string>res;
        for(int h = 0; h<=11; h++){
            int hb = countbit(h);
            if(hb == num) res.push_back(to_string(h)+":00");
            if(hb>num) continue;
            for(int m = 1; m<=59; m++){
                int mb = countbit(m);
                if(mb + hb == num) res.push_back(to_string(h)+":"+(m>=10 ? "": "0")+to_string(m));
            }
        }
        return res;
    }
    
    int countbit(int n){
        int res = 0;
        while(n){
            res +=1;
            n = n & (n-1);
        }
        return res;
    }
};


class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> result;
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (bit_count((h<<6) + m) == num) { // = bit_count(m) + bit_count(h)
                    const auto hour = to_string(h);
                    const auto minute = m < 10 ? "0" + to_string(m) : to_string(m);
                    result.emplace_back(hour + ":" + minute);
                }
            }
        }
        return result;
    }

private:
    int bit_count(int bits) {
        int count = 0;
        for (; bits; bits &= bits - 1) {
            ++count;
        }
        return count;
    }
};


//backtrack
class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> res;
        backtrack(res, make_pair(0, 0), num, 0);
        return res;
    }
    
    vector<int> hour = {1, 2, 4, 8}; vector<int> minute = {1, 2, 4, 8, 16, 32};
    
    void backtrack(vector<string>& res, pair<int, int> time, int num, int cur){
        if(num == 0){
            res.push_back(to_string(time.first) + ":" + (time.second < 10 ? "0" : "") + to_string(time.second));
            return;
        }
        for(int i = cur; i < hour.size() + minute.size(); i++){
            if(i < hour.size()){
                time.first += hour[i];
                if(time.first < 12){
                    backtrack(res, time, num - 1, i + 1);
                }
                time.first -= hour[i];
            }
            else{
                time.second += minute[i - hour.size()];
                if(time.second < 60){
                    backtrack(res, time, num - 1, i + 1);
                }
                time.second -= minute[i - hour.size()];
            }
        }
    }
};
