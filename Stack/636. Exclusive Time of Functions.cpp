/*
636. Exclusive Time of Functions

Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, 
find the exclusive time of these functions.

Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.

A log is a string has this format : function_id:start_or_end:timestamp.
For example, "0:start:0" means function 0 starts from the very beginning of time 0. 
"0:end:0" means function 0 ends to the very end of time 0.

Exclusive time of a function is defined as the time spent within this function, 
the time spent by calling other functions should not be considered as this function's exclusive time. 
You should return the exclusive time of each function sorted by their function id.

Example 1:
Input:
n = 2
logs = 
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.
Note:
Input logs will be sorted by timestamp, NOT log id.
Your output should be sorted by function id, 
which means the 0th element of your output corresponds to the exclusive time of function 0.
Two functions won't start or end at the same time.
Functions could be called recursively, and will always end.
1 <= n <= 100


*/

/*
一个任务可能被执行很多次

1
["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]


只能出现下面的

        |_____|  |____|
    |___________________|
|__________________________|
 
 
 不
       |___________________|
 |____________________|
 

 

*/

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int>res(n);
        stack<int>job;
        for(auto s: logs){
            int i = 0;
            while(s[i]!=':') i++;
            int id = stoi(s.substr(0,i));
            bool isStart = s[++i] == 's' ? true: false;
            while(s[i]!=':') i++;
            int j = ++i;
            int time = stoi(s.substr(j));
            if(isStart){
                if(!job.empty()) job.top() = time - job.top();
                job.push(time);
            }else{
                res[id] += time - job.top()+1; //因为一个job可能被执行很多次, +1, 结束是在那一时刻运行完，
              //job.top() assume都是上次开始
                job.pop();
                if(!job.empty()) job.top() = time + 1 - job.top();//开始是在结束后的下一秒开始， job.top() 是上次花费时间，
             // time + 1 - job.top() 是把start 平行移动,
            }
        }
        return res;
    }
};



class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> rt(n,0);
        stack<int> func;
        int prev=0;
        for(int i=0;i<logs.size();i++)
        {
            int itf = logs[i].find_first_of(':');
            int its = logs[i].find_last_of(':');
            int ifunc = stoi(logs[i].substr(0,itf));
            int time = stoi(logs[i].substr(its+1));
            if(logs[i][itf+1]=='s')
            {
                if(!func.empty()) rt[func.top()]+=time-prev;
                prev=time;
                func.push(ifunc);
            }
            else
            {
                rt[func.top()]+=time-prev+1;
                prev=time+1;
                func.pop();
            }
        }
        return rt;
    }
};

//stk push的是上个job的id
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int>res(n);
        stack<int>stk;
        int prev = 0;
        for(auto s: logs){
            vector<string>cur = split(s); 
            int id = stoi(cur[0]), time = stoi(cur[2]);
            if(cur[1][0] == 's'){
                if(!stk.empty()) {
                    res[stk.top()] += time - prev;
                }
                stk.push(id);
                prev = time;
            }else{
                res[id] += time - prev + 1;
                stk.pop();
                prev = time + 1;
            }
        }
        return res;
    }
    
    vector<string> split(const string& s){
        vector<string>res;
        string temp;
        stringstream ss(s);
        while(getline(ss, temp, ':')) res.push_back(temp);
        return res;
    }
};
