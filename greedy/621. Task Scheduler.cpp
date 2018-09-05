/*
621. Task Scheduler
https://leetcode.com/problems/task-scheduler/description/

Given a char array representing tasks CPU need to do. 
It contains capital letters A to Z where different letters represent different tasks.
Tasks could be done without original order. 
Each task could be done in one interval. 
For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, 
there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1: 
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
Note:
The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].


*/


/*
可以建一个框架，用最多的字母，和cooling interval, 比如最多字母是A, cooling interval n = 3
A * * *  A * * * A * * * A, 每个A之间都隔了三个数，那么一个区间是 n + 1 (算上A)
把剩下的字母填进空，

比如AAABBCC， cooling interval n = 3, 因为A是最多的，既然A可以之间保证n个，其他的字母也可以保证也都隔了n个再重复
A B C * A B C* A ， 

(n + 1)*(max - 1);  n+1是每个区间长度， max - 1时除了最后一个外的，因为最后一个区间不用填满所有
最后loop map如果map value == max, ans ++, 因为ans加的是最后结尾加的字母
比如 AAABBBCC, A B C * A B C* A B， 结尾需要加两个： 1个A, 1个B 

最后需要跟task size比谁大, 这是因为可能既定的框架放不下, 给的cooling interval 小，字母足够大， 不需要idle补
比如 AACCCBEE 2， 框架  C * * C * * C, 
    先放A，= >  C A * C A * C
    再放E = >  C A E C A E C,
    B就没地方了，随便再一个interval即可 =》 C A E B C A E C

*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
         unordered_map<char,int>m;
         int maxN = -1;
         for(auto i: tasks)
        {
            m[i]++;
            maxN = max(maxN,m[i]);
        }
        int ans = (n+1)*(maxN-1);
        for(auto itr: m) if(itr.second == maxN) ans++;  //or use count_if
        //size_t num_max = count_if(counts.begin(), counts.end(), [max_count](int i){return i == max_count;});
        return max(ans,(int)tasks.size());
    }
};


//one pass
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int len = tasks.size();
        vector<int>count(26,0);
        int maxN = 0, maxNum = 0;
        for (char c : tasks) {
            count[c - 'A']++;
            if (count[c - 'A'] > maxN) {
                maxN = count[c - 'A'];
                maxNum = 1;
            } else if (count[c - 'A'] == maxN) {
                maxNum++;
            }
        }
        return max(len, (maxN - 1) * (n + 1) + maxNum);
    }
};

/*
Priority Queue的解： 
把每个字母的frequency push 进pq

需要一个map key是时间，value是下次开始时对应字母记得数
map作用是作为缓存，假如time = 0, 现在字母是'A', 下次出现是time = 5,
time 从2 到4， pq中不会在出现A，不能query A，避免不到n个间隔，做重复劳动，当time = 5时，发现map有记录，get cur = 4, push 进pq，就可以继续用A

当还有还没用完的task taskremaining  > 0，但是可能因为没有结束cooling period, pq.size() == 0
不减少taskremaining, 只增加一个time

*/
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int>frequencies(26,0);
        for (char c : tasks) frequencies[c - 'A']++;

        priority_queue<int>pq;
        for (int i : frequencies) if (i != 0) pq.push(i);
        unordered_map<int,int>map;
        int time = 0, tasksRemaining = tasks.size(), preCount = 0, cur = -1;
        while (tasksRemaining > 0) {
            if(map.count(time)) preCount=map[time]; //到下一个区间开始
            else preCount = 0;
            if (preCount != 0) pq.push(preCount); 
            
            if(!pq.empty()) {cur = pq.top(); pq.pop();} //现在pq 没有数，pop出来空的，在cooling period
            else cur = -1;
            if (cur != -1) tasksRemaining--;
            if (cur != -1 && --cur > 0) map[time + n + 1] = cur; //比如现在是0，n+1 = 4, 到4的时候才把'A'的个数拿出来，放进pq
            time++;
        }
        return time;

    }
};


/**
priority_queue<task, count>
*/
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> counts;
        for (char t : tasks) {
            counts[t]++;
        }
        priority_queue<pair<int, char>> pq;
        for (pair<char, int> count : counts) {
            pq.push(make_pair(count.second, count.first)); //把次数最多的数先pop
        }
        int alltime = 0;
        int cycle = n + 1;
        while (!pq.empty()) {
            int time = 0;
            vector<pair<int, char>> tmp;
            for (int i = 0; i < cycle; i++) {
                if (!pq.empty()) {
                    tmp.push_back(pq.top());
                    pq.pop();
                    time++;
                }
            }
            for (auto t : tmp) {
                if (--t.first) {
                    pq.push(t);
                }
            }
            alltime += !pq.empty() ? cycle : time;
        }
        return alltime;
    }
};

