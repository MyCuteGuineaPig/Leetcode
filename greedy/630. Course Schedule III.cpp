/*
630. Course Schedule III
https://leetcode.com/problems/course-schedule-iii/description/

There are n different online courses numbered from 1 to n. 
Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days 
and must be finished before or on the dth day. You will start at the 1st day.

Given n online courses represented by pairs (t,d), 
your task is to find the maximal number of courses that can be taken.

Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, 
and ready to take the next course on the 101st day.

Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, 
and ready to take the next course on the 1101st day. 

Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
Note:
The integer 1 <= d, t, n <= 10,000.
You can't take two courses simultaneously.

*/


class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(),courses.end(), [](const vector<int> a, const vector<int> &b){
            if (a[1]==b[1]) return a[0]<b[0]; else return a[1]<b[1];
        });

        int count = 1, cur = courses[0][0];
        multiset<int>s;
        s.insert(courses[0][0]);
        for(int i = 1; i<courses.size();i++){
           if(cur+courses[i][0]<=courses[i][1]){
                count++;
                cur += courses[i][0];
                s.insert(courses[i][0]);
            }else if(*s.rbegin()>courses[i][0]){ //不可以是cur - *s.rbegin() + courses[i][0]<=courses[i][1]
            //因为我们保证drop out 之前的longer time course 后，cur 时间必须减小，
            //cur - *s.rbegin() + courses[i][0]<=courses[i][1] 这么做可以保证学的课程数量一样，但可能cur 增加了
            // 比如之前cur = 14, 之前最长的是7， 遇到新的是【9,19], 14-7+9 < 19, 但是课程数量不变的情况下，cur 却从14 变成16
                cur = cur- *s.rbegin()+courses[i][0];    
                s.erase(--s.end());
                s.insert(courses[i][0]);
            }
        }
        return s.size();
    }
};


/*

First, we sort courses by the end date, this way, 
when we're iterating through the courses, 
we can switch out any previous course 
with the current one without worrying about end date.

Next, we iterate through each course, i
f we have enough days, we'll add it to our multiset. 
If we don't have enough days, 
then we can either ignore this course, 
or we can use it to replace a longer course we added earlier.

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // sort courses by the end date
        sort(courses.begin(),courses.end(),
            [](vector<int> a, vector<int> b){return a.back()<b.back();});
            
        multiset<int> cls; // store lengths of each course we take (could be duplicates!)
        int cursum=0;
        
        for (int i=0; i<courses.size(); i++) {
            
            // if we have enough time, we will take this course
            if (cursum+courses[i].front()<=courses[i].back()) {
                cls.insert(courses[i].front());
                cursum+=courses[i].front();
            } else if (*cls.rbegin()>courses[i].front()) {
                // if we don't have enough time, we switch out a longer course
                cursum+=courses[i].front()-*cls.rbegin();
                cls.erase(--cls.end());
                cls.insert(courses[i].front());
            } // if we don't have enough time for course[i], 
              //and it's longer than any courses taken, then we ignore it
        }
        
        return cls.size();
    }
};
My final consideration was when we replace a longer course with a much shorter one, 
does that mean we'll have enough room to take some courses previously ignored for being too long?

The answer is no, because any courses we missed would be longer than what's in multiset cls.
 So the increase in number of days cannot be larger than the largest element in cls, 
 and certainly will be less than a previously ignored course which has to be even longer.

*/
