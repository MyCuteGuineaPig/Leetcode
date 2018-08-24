/*
699. Falling Squares


On an infinite number line (x-axis), we drop given squares in the order they are given.

The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point being positions[i][0] and sidelength positions[i][1].

The square is dropped with the bottom edge parallel to the number line, and from a higher height than all currently landed squares. 
We wait for each square to stick before dropping the next.

The squares are infinitely sticky on their bottom edge, 
and will remain fixed to any positive length surface they touch (either the number line or another square). 
Squares dropped adjacent to each other will not stick together prematurely.


Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped, 
after dropping squares represented by positions[0], positions[1], ..., positions[i].

Example 1:
Input: [[1, 2], [2, 3], [6, 1]]
Output: [2, 5, 5]
Explanation:

After the first drop of positions[0] = [1, 2]:
_aa
_aa
-------
The maximum height of any square is 2.


After the second drop of positions[1] = [2, 3]:
__aaa
__aaa
__aaa
_aa__
_aa__
--------------
The maximum height of any square is 5.  
The larger square stays on top of the smaller square despite where its center
of gravity is, because squares are infinitely sticky on their bottom edge.


After the third drop of positions[1] = [6, 1]:
__aaa
__aaa
__aaa
_aa
_aa___a
--------------
The maximum height of any square is still 5.

Thus, we return an answer of [2, 5, 5].


Example 2:
Input: [[100, 100], [200, 100]]
Output: [100, 100]
Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.
Note:

1 <= positions.length <= 1000.
1 <= positions[i][0] <= 10^8.
1 <= positions[i][1] <= 10^6.

[[2,3],[5,1],[6,2],[4,2]]
*/

/*

跟218. The Skyline Problem 解法类似， 画出square的轮廓

*/

class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        vector<int>res;
        map<int, int>height;
        int maxh = height[-1] = 0;
        for(auto p: positions){
            int l = p.first, h = p.second;
            auto itl = height.upper_bound(l); // 第一个比first 大的， prev(itl) 就是第一个比first一样的或者小的，再first下面的
            auto itr = height.lower_bound(l+h); // first + second是结束后第一个点, 可能等于 
            int h0 = prev(itl)->second;
            int h1 = itr->first == l+h ?  itr->second : prev(itr)->second;
            for(auto it = itl; it!=itr; it++)
                h0 = max(h0, it->second);//找p点下方最高的点
            height.erase(itl, itr);
            height[l] = h0 + h;
            height[l+h] = h1;
            maxh = max(maxh, h0+h);
            res.push_back(maxh);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        vector<int> result;
        map<int, int> heights;
        int maxH = heights[-1] = 0;
        for (const auto& p : positions) {
            auto it0 = heights.upper_bound(p.first);
            auto it1 = heights.lower_bound(p.first + p.second);
            int h0 = prev(it0)->second; //小于等于起点位置(p.first) 可以直到之前的高度, 在p点下方的点
            int h1 = it1->first == p.first + p.second ? it1->second : prev(it1)->second; //小于结束的位置(p.first,) p.first + p.second是结束后第一个点,
            //cout<<" h0 "<<h0<<" h0first "<<prev(it0)->first<<" ; h1 "<<h1<<" h1first "<<prev(it1)->first<<endl;
            for (auto it = it0; it != it1; ++it) {
                //cout<<"max "<<it->first<<" sec "<<it->second<<endl;
                h0 = max(h0, it->second); 
            } 
            //cout<<" h0 "<<h0<<endl;
            heights.erase(it0, it1);
            heights[p.first] = h0 + p.second;
            heights[p.first + p.second] = h1;
            cout<<endl;
            for(auto it: heights)
                cout<<it.first<<" sec "<<it.second<<endl;
            cout<<endl;
            maxH = max(maxH, h0 + p.second);
            result.emplace_back(maxH);
        }
        return result;
    }
};