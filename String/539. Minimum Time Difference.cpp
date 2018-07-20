/*
539. Minimum Time Difference

Given a list of 24-hour clock time points in "Hour:Minutes" format, 
find the minimum minutes difference between any two time points in the list.
Example 1:
Input: ["23:59","00:00"]
Output: 1
Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.


*/




class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        auto pred = [](const string& t){
            return 60*stoi(t.substr(0,2)) + stoi(t.substr(3));
        };
        vector<int>hrs;
        transform(timePoints.begin(), timePoints.end(), back_inserter(hrs), pred);
        sort(hrs.begin(), hrs.end());
        int res = 1440 + hrs[0] - hrs.back();
        for(int i = 0; i<hrs.size()-1; i++){
            res = min(hrs[i+1] - hrs[i], res); 
        }
        return res;
    }
};

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        static const int N = 60 * 24;
        vector<int> minutes;
        for (const auto& t : timePoints) {
            minutes.emplace_back(stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3)));
        }
        sort(minutes.begin(), minutes.end());
        int result = numeric_limits<int>::max();
        for (int i = 0; i < timePoints.size(); ++i) {
            result = min(result, (N + minutes[(i + 1) % timePoints.size()] - minutes[i]) % N);
        }
        return result;
    }
};


class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        auto pred = [](const string& t){
            return 60*stoi(t.substr(0,2)) + stoi(t.substr(3));
        };
        vector<int>hrs;
        transform(timePoints.begin(), timePoints.end(), back_inserter(hrs), pred);
        int res = 3600;
        for(int i = 0; i<hrs.size(); i++){
            for(int j = 0; j<hrs.size(); j++){
                if(i!=j){
                    int temp = hrs[i] >= hrs[j] ? hrs[i] - hrs[j] : hrs[i]+1440 - hrs[j];
                    res = min(temp, res);
                }
            }   
        }
        return res;
    }
};


