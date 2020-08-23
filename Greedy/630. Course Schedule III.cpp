/*
Solution 1: 移花接木

需要先sort，按照结课的时间排序; 
需要一个priority queue, 得到当前最大时间(上课需要的duration)，用于移花接木；移花接木是保持总共的课程量不变，
但是把课程的所需时间变短；

先，然后用cur 记录当前时间, 如果cur + c[0] <= c[1]，pq.push(c[0])
如果cur + c[0] <= c[1] 不成立，考虑pq.top > c[0]成立吗
    - 若成立，可以吧top的区间用现在c[0] 代替，假设pq.top 最长的课程， 所属的course index为ind
      我们可以把之前的ind给删了,把c[0] 放在ind的位置，因为course 按最晚结课时间排序，当
        c[1] > course[ind][1], 
        又因为c[0] < pq.top() = course[ind][1]
        所以  course[i][0] + 老的cur < course[ind][0] + 老的cur < course[ind][1] 
        相当于我们把c = course[i] 放到了course[ind]的位置，完美替代

比如 [[5,5], [1,6],[4,6],[2,6]],
 到4的时候， pq.top = 5; 因为 5 < 6(结束位置小), 5 > 4（但需要时间长于现在的)，可以用【4，6】代替[5,5]的位置, 现在时间是 [4,6], [1,6]



如果不用移花接木， 

根据index 1sort，下面结果会报错
Example:  [[5,5],[4,6],[2,6]]
output: 2

根据index 0sort，下面结果会报错
Example： [[5,15],[3,19],[6,7],[2,10],[5,16],[8,14],[10,11],[2,19]]
output: 4

followup question: 如果我们remove priority queue top是不是还有空间容纳别的我们之前忽略的元素？
answer:No! 因为我们之前忽略的课程一定是 longer than what's in priority queue,  (cur + 忽略的 > c[0], 忽略的是大于pq.top())
increase的(pt.top - c[0])的不可能大于pt.top which is lrgest element in queue， 小于之前忽略的课程, 

*/

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(),courses.end(), [](const vector<int> a, const vector<int> &b){
            if (a[1]==b[1]) return a[0]<b[0]; else return a[1]<b[1];
        });

        int cur = courses[0][0];
        multiset<int>s;
        s.insert(courses[0][0]);
        for(int i = 1; i<courses.size();i++){
           if(cur+courses[i][0]<=courses[i][1]){
                cur += courses[i][0];
                s.insert(courses[i][0]);
            }else if(*s.rbegin()>courses[i][0]){ //不可以是cur - *s.rbegin() + courses[i][0]<=courses[i][1]
            //因为我们保证drop out 之前的longer time course 后，cur 时间必须减小，
            //cur - *s.rbegin() + courses[i][0]<=courses[i][1] 这么做可以保证学的课程数量一样，但可能cur 增加了
            // 比如之前cur = 14, 之前最长的是7， 遇到新的是【9,19], 14-7+9 < 19, 但是课程数量不变的情况下，cur 却从14 变成16
                cur = cur- *s.rbegin()+courses[i][0];    
                s.erase(--s.end());
                s.insert(courses[i][0]);
            /*
            可以保证 course[i][0] 有位置放，*s.rbegin()所属的course index为ind
            比如 之前在处理ind时候,  course[ind][0] + 老的cur < course[ind][1]， 现在course[i]<course[ind]
            我们可以把之前的ind给删了,我们可以把course[i][0] 放在ind的位置，course[i][1] > course[ind][1]
            course[i][0] < course[ind][0]
            所以  course[i][0] + 老的cur < course[ind][0] + 老的cur < course[ind][1] 
            */
            }
        }
        return s.size();
    }
};



class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](const vector<int>&a, const vector<int>&b){return a[1]<b[1];}); 
        //sort 不用[0], 比如[2,6], [4,6], 先加小的， 如果大的能加还会<end;  如果先加大的，到小的加不进去，可以通过multiset绕回去
        int course = 0, cur = 0;
        multiset<int>pq;
        for(auto c: courses){
            if(cur + c[0] <= c[1]){
                course++;
                cur = cur + c[0];
                pq.insert(c[0]);
            }
            else if(!pq.empty() && *pq.rbegin() > c[0]){ //加上empty是为了避免[[100, 2], [32,20]], 这样duration>end的情况, pq.empty(); 从而不会造成*pq.rbegin() errror
                cur = cur - *pq.rbegin() + c[0];
                pq.erase(--pq.end());
                pq.insert(c[0]);
            }
        }
        return course;
    }
};



class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });
        priority_queue<int> max_heap;
        int now = 0;
        for (const auto& course : courses) {
            max_heap.emplace(course[0]);
            now += course[0];  
            if (now > course[1]) {
                now -= max_heap.top(), max_heap.pop();
            }
            /*
             比如上一个满足，这个不满足，可能是因为这次加个很大的，或者是之前加个很大的, 不管顺序是这次是大，还是之前是大，就pop掉大的
             比如 now = 20, top = 4, 这次[9,25], pop掉9 , now 还是20
             比如 now = 20, top = 9, 这次是[4,25], pop掉9， now = 20 - 9 + 4 = 16, 
             pop掉肯定满足，因为上一个满足，所以end >= 20, 而这次pop之后，变成16 比20更小了，肯定满足

             */
        }
        return heap.size();
    }
};


