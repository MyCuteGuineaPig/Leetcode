class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        long numsOfDays = 0;
        unordered_map<long,long>t;
        for(int i = 0; i<tasks.size(); ++i){
            ++numsOfDays;
            if ( t.count(tasks[i]) && numsOfDays - t[tasks[i]] <= space) {
                numsOfDays +=  space - (numsOfDays - t[tasks[i]]) + 1;
            }
            t[tasks[i]] = numsOfDays;
        }
        return numsOfDays;
    }
};


class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int, long long> last;
        long long res = 0;
        for (int a: tasks)
            if (last.count(a))
                last[a] = res = max(res, last[a] + space) + 1;
            else
                last[a] = ++res;
        return res;
    }
};


//记录下一个开始的
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) 
    {
        unordered_map<long long ,long long> m;
        int ans=0;
        long long int  curr=0;
        for(int i=0;i<tasks.size();i++)
        {
            
            if(m.find(tasks[i])==m.end())
            {
                m[tasks[i]]=1+space+curr;
                curr++;
            }
            else
            {
                if(m[tasks[i]]>curr)
                {
                    curr=m[tasks[i]];
                }
                m[tasks[i]]=space+curr+1;  
                curr++;
            }     
        }
        return curr;
    }
};



class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int, long long> m;
        long long days = 0;
        for(auto i : tasks)
        {
            days += 1 + max(0LL, m[i] - days);
            m[i] = days + space;
        }
        return days;
    }
};