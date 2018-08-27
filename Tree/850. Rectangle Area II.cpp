/*
850. Rectangle Area II


We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , 
where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.

Find the total area covered by all rectangles in the plane.  Since the answer may be too large, return it modulo 10^9 + 7.



Example 1:

Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: As illustrated in the picture.
Example 2:

Input: [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.
Note:

1 <= rectangles.length <= 200
rectanges[i].length = 4
0 <= rectangles[i][j] <= 10^9
The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit in a 64-bit signed integer.



*/

/*
Solution 1: 
画出height的轮廓，根据height一层一层的算当层长方体面积;   高度是curh (height map的key) - prevh
用count 表示当这个height结束时，那快区域是open的， open的区域用curx 表示
count[i] 表示当前从set【i]到set[i+1] 点有几个长方形共同拥有它为底
当前面积是 area = (curh - prevh) * curx

先计算当前高度往下长方形block的体积
然后更新当前x

比如：
[[0,0,2,2],[1,0,2,3],[1,0,3,1]] 

xcoordinate:   0  1  2   3
index:         0  1  2   3

初始化Prevh 是height最小的height, area = 0, curx = 0;
当高度为0 时，area = area+ (0 - 0) * 0 = 0
更新curx 的值, 
            value: 1, 0, 2                   value: 1, 1, 2                 value: 1, 1, 3
             xcoordinate:   0  1  2   3      xcoordinate:   0  1  2   3     xcoordinate:   0  1  2   3 
               count:       1  1  0   0        count:       1  2  0   0       count:       1  3  1   0
            prevh = 0, curx = 3

当高度为1 时，area = area+ (1 - 0) * 3 = 3 
更新curx 的值, 
            value: -1, 1, 3    
            xcoordinate:   0  1  2   3
             count:        1  2  0   0
            prevh = 1, curx = 2

当高度为2 时，area = area+ (2 - 1) * 2 = 3 + 2 = 5
更新curx 的值, 
            value: -1, 0, 2    
            xcoordinate:   0  1  2   3
             count:        0  1  0   0
            prevh = 2, curx = 1


当高度为3 时，area = area+ (3 - 2) * 1 = 5 + 1 = 6 
更新curx 的值, 
            value: -1, 1, 2    
            xcoordinate:   0  1  2   3
             count:        0  0  0   0
            prevh = 0, curx = 0
            
*/

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        if(rectangles.empty()) return 0;
        set<int>xcoordinate;
        map<int,vector<vector<int>>>heights; //height key is the height, value is the value for coordinate, 
        //vector[0] is open 1(底) or close -1(高), vector[1] x-start, vector[2]: x-end
        for(auto p: rectangles){
            xcoordinate.insert(p[0]); xcoordinate.insert(p[2]);
            heights[p[1]].push_back({1, p[0], p[2]});  //open
            heights[p[3]].push_back({-1, p[0], p[2]}); //close
        }
        unordered_map<int,int>Xi; int index = 0;
        vector<int>X_index_tox(xcoordinate.begin(),xcoordinate.end());
        for(auto x: xcoordinate) {Xi[x] = index++; } //把每个x 按小到大 一个一个sign 一个index
        
        long long prevh = heights.begin()->first, area = 0, mod = 1e9+7, curx = 0;
        vector<int>count(xcoordinate.size());
        for(auto l: heights){
            int curh = l.first;
            area = ( area +  (curh - prevh)*curx )%mod;

            for(auto p: l.second){
                int sign = p[0], xstart = p[1], xend = p[2];
                for(int i = Xi[xstart]; i<Xi[xend]; i++)
                    count[i] += sign;
            }
           
            curx = 0; //求下一层的x
            for(int i = 0; i<count.size(); i++)
                if(count[i] > 0)
                    curx += X_index_tox[i+1] - X_index_tox[i];

            prevh = curh;
        }
        
        return area;
    }
};











/*
Solution 2: 
画出整体的轮廓，根据x, 算当前height的可以计算height的高度；
area = area +  h * (x - prevx)

先计算当前

比如：
[[0,0,2,2],[1,0,2,3],[1,0,3,1]]
当

*/
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        if(rectangles.empty()) return 0;
        map<int, vector<vector<int>>>heights; //key是x 的值，value是点
        for(auto p: rectangles){
            heights[p[0]].push_back({1, p[1], p[3]}); //rectangle左侧, //以x为开始，底的y和顶的y
            heights[p[2]].push_back({0, p[1], p[3]}); //rectangle右侧
        }
        
        multiset<pair<int,int>>open;
        long long prevx = 0, area = 0, mod = 1e9 + 7;
        for(auto it: heights){
            long long x = it.first;
            if(!open.empty())
            {
                int lower = -1, total = 0;
                for(auto l: open){
                    if(lower >= l.second) continue; //之前的最低点大于之前的最高点、比如之前是pair = {1,6}, 现在pair 是{2,4}, {2,4}就不用考虑, 避免重复计算
                    lower = max(lower, l.first);
                    total += l.second - lower;
                    lower = l.second; 
                }
                area = (area + total*(x - prevx))%mod;
            }
            prevx = x;
            for(auto p: it.second){
                if(p[0]>0) // means open
                    open.insert({p[1],p[2]});
                else
                    open.erase(open.find({p[1],p[2]}));
            }
        }
        return area;
    }
};

/*
Solution 3: 
https://leetcode.com/problems/rectangle-area-ii/discuss/138206/C++-10-lines-normalized-canvas
用一个二维的map 记录是不是经过当前的距离，经过了不算面积，没经过，算面积
map 是把长方形坐标划分成 若干的小份

*/

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles, int res = 0) {
    set<int> sx, sy;
    for (auto v : rectangles) sx.insert(v[0]), sy.insert(v[1]), sx.insert(v[2]), sy.insert(v[3]);
    vector<int> x(begin(sx), end(sx)), y(begin(sy), end(sy));
    vector<vector<int>> m(x.size(), vector<int>(y.size(), 0));

    for (auto v : rectangles) {
        for (auto i = lower_bound(begin(x), end(x), v[0]); *i != v[2]; ++i)
        for (auto j = lower_bound(begin(y), end(y), v[1]); *j != v[3]; ++j)
            if (m[i - begin(x)][j - begin(y)]++ == 0) 
            res = (res + ((long long)*next(i) - *i) * (*next(j) - *j)) % 1000000007;
    }
    return res;
    }
};


/*
Solution 4： segment Tree
跟solution 1 相似

*/


class Solution {
public:
    enum { OPEN = 1, CLOSE = -1};
    
    int rectangleArea(vector<vector<int>>& rectangles) {
        vector<vector<int>> events;
        set<int> Xvals;
        for (const auto& rec: rectangles) {
            events.emplace_back(vector<int>{rec[1], OPEN, rec[0], rec[2]});
            events.emplace_back(vector<int>{rec[3], CLOSE, rec[0], rec[2]});
            Xvals.emplace(rec[0]);
            Xvals.emplace(rec[2]);
        }
        sort(events.begin(), events.end());
        vector<int> X(Xvals.cbegin(), Xvals.cend());
        unordered_map<int, int> Xi;
        for (int i = 0; i < X.size(); ++i) {
            Xi[X[i]] = i;
        }

        auto st = new SegmentTreeNode(0, X.size() - 1, X);
        int64_t result = 0;
        int64_t cur_x_sum = 0;
        int cur_y = events[0][0];
        for (const auto& event: events) {
            int y = event[0], type = event[1], x1 = event[2], x2 = event[3];
            result += cur_x_sum * (y - cur_y);
            cur_x_sum = st->update(Xi[x1], Xi[x2], type);
            cur_y = y;
        }
        return result % static_cast<int64_t>(1e9 + 7);
    }

    class SegmentTreeNode {
    public:
        SegmentTreeNode(int start, int end, const vector<int>& X) :
            start_(start),
            end_(end),
            X_(X),
            left_(nullptr),
            right_(nullptr),
            count_(0),
            total_(0) {
        }

        int mid() const {
            return start_ + (end_ - start_) / 2;
        }

        SegmentTreeNode *left() {
            if (left_ == nullptr) {
                left_ = new SegmentTreeNode(start_, mid(), X_);
            }
            return left_;
        }

        SegmentTreeNode *right() {
            if (right_ == nullptr) {
                right_ = new SegmentTreeNode(mid(), end_, X_);
            }
            return right_;
        }
        
        int64_t total() const {
            return total_;
        }

        int64_t update(int i, int j, int val) {
            if (i >= j) {
                return 0;
            }
            if (start_ == i && end_ == j) {
                count_ += val;
            } else {
                left()->update(i, min(mid(), j), val);
                right()->update(max(mid(), i), j, val);
            }
            if (count_ > 0) {
                total_ = X_[end_] - X_[start_];
            } else {
                total_ = left()->total() + right()->total();
            }
            return total_;
        }
        
    private:
        int start_, end_;
        const vector<int>& X_;
        SegmentTreeNode *left_, *right_;
        int count_; //count是这个区间内有几个是open的，total是左右两个x的数
        int64_t total_;
    };
};
