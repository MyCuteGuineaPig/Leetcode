/*
757. Set Intersection Size At Least Two

An integer interval [a, b] (for integers a < b) is a set of all consecutive integers from a to b, including a and b.

Find the minimum size of a set S such that for every integer interval A in intervals, 
the intersection of S with A has size at least 2.

Example 1:
Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
Output: 3
Explanation:
Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
Also, there isn't a smaller size set that fulfills the above condition.
Thus, we output the size of this set, which is 3.
Example 2:
Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
Output: 5
Explanation:
An example of a minimum sized set is {1, 2, 3, 4, 5}.
Note:

intervals will have length in range [1, 3000].
intervals[i] will have length 2, representing some integer interval.
intervals[i][j] will be an integer in [0, 10^8].


*/


/*
Solution 1: 先按照start 点由小到大sort，再按照end 由大到小sort， 
让end 有大到小sort， 是start 一样的点 而是end大的，提前充满，避免到它点，往S push之前使用过的点

建一个vector cnt 初始值为2，表示点i还需要几个点让它还剩几个点就覆盖，

然后从后往前看，如果这个点还剩 2个值，就用start, start + 1, 一个值就用start + 1, 如果前面的也在这个范围内，就--cnt,
前面的点的start1 < cur点，因为是按start从小到大排序的，我们只需看 cur点是不是小于等于end

注意： 不能不管start 点，否则有的点会count 两回
比如 [1,2], [2,4], [2,3], [4,5] 正确的点是 4,5, 2,3, 1

如果顺序变成[1,2], [2,3], [2,4],  [4,5]，
 点【4，5】，S={4,5} 让cnt[2]-1(点[2,4])
 点 [2,4], S  = 2 让cnt[1] - 1（点[2,3])
 到[2,3] 发现还剩1个值，S = 2; 与上面的2重复使用了

*/


class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return (a[0] != b[0]) ? (a[0] < b[0]) : (b[1] < a[1]);
             });
        vector<int> cnts(intervals.size(), 2);
        int res = 0;
        while(!intervals.empty()){
            int start = intervals.back()[0]; intervals.pop_back();
            int cnt = cnts.back(); cnts.pop_back();
            for(int cur = start; cur<start+cnt; cur++){
                for(int i = 0; i<intervals.size(); i++){
                   if(cnts[i] && cur<=intervals[i][1]){
                       cnts[i]--;
                   } 
                }
            }
            res+=cnt;
        }
        return res;
    }
};


/*
Solution 2: 
根据end 来sort： 如果end 一样根据start sort，

当loop 时候因为是根据end sort，所以只需判断start <= largest ? second <= second? 
如果都小于，继续
如果只有second 不满足，+1 个点， second = largest, largest = p[1]
如果两个点都不满足, + 2 个点, second = p[1]-1, largest = p[1]

如果sort不管start，  [[1,3],[3,7],[5,7],[7,8]]， 
结束[1,3], largest = 1, second = 3;   res = 2
结束[3,7], largest = 7, second = 3;    res = 3
到了[5,7], 发现second 不在里面, largest = p[1] = 7, second = largest = 7；  res = 4
largest 和second 一样大

但实际上我们需要 [1,3, 5, 7, 8] 五个点才够

或者我们可以不管sort start，如果largest == end， second = largest - 1

*/

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](const vector<int>&a, const vector<int>& b){ return a[1] == b[1] ? a[0]>b[0]: a[1]<b[1];});
        int largest = -1, second = -1, res = 0;
        for(auto p: intervals){
            bool is_largest_in = p[0] <= largest;
            bool is_second_in = p[0] <= second;
            if(is_largest_in && is_second_in) continue;
            
            res += is_largest_in ? 1: 2;
            second = is_largest_in ? largest: p[1] - 1;
            largest = p[1];
        }
        return res;
    }
};



class Solution { //不 sort start
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](const vector<int>&a, const vector<int>& b){ return a[1]<b[1];});
        int largest = -1, second = -1, res = 0;
        for(auto p: intervals){
            bool is_largest_in = p[0] <= largest;
            bool is_second_in = p[0] <= second;
            if(is_largest_in && is_second_in) continue;
            
            res += is_largest_in ? 1: 2;
            second = !is_largest_in || largest == p[1] ? p[1] - 1 : largest;
            /*
            比如 [[1,3],[3,7],[5,7],[7,8]]， 
            到【5，7]时，largest = 7, second = 3, is_largest_in = true, 但是 largest == p[1], second = 7 - 1 = 6
            */
            largest = p[1];
        }
        return res;
    }
};

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] > b[0]); 
        });
        int n = intervals.size(), ans = 0, p1 = -1, p2 = -1; //p1 第二大 second, p2 = largest
        for (int i = 0; i < n; i++) {
            if (intervals[i][0] <= p1) continue;
            if (intervals[i][0] > p2) {
                ans += 2;
                p2 = intervals[i][1];
                p1 = p2-1;
            }
            // only p2 works;  
            else {
                ans++;
                p1 = p2;
                p2 = intervals[i][1];
            }
        }
        return ans;
    }
};