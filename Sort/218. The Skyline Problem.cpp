/*
218. The Skyline Problem


A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. 
Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), 
write a program to output the skyline formed by these buildings collectively (Figure B).

 Buildings  Skyline Contour
The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], 
where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. 
It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. 
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. 
A key point is the left endpoint of a horizontal line segment. 
Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, 
and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. 
For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

*/



//write by own
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int,int>>res;
        auto cmp = [](const pair<int,int>&a, const pair<int,int>&b){return a.first == b.first? a.second < b.second : a.first < b.first; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)>pq(cmp);

        int i = 0;
        while(i<buildings.size() || !pq.empty()){
            if(i<buildings.size() && (pq.empty()|| pq.top().second>=buildings[i][0])){
                int preh = pq.empty() ? numeric_limits<int>::min(): pq.top().first;
                pq.push({buildings[i][2], buildings[i][1]});
                if(pq.top().first > preh){
                    if(!res.empty() && res.back().first == buildings[i][0]) 
                        res.back() = {buildings[i][0], buildings[i][2]}; //避免情况比如[[1,2,1],[1,2,2],[1,2,3]], 返回多个结果，结果只需要[[1,3],[3,0]]，而不是[[1,1],[1,2],[1,3],[3,0]]
                    else res.push_back({buildings[i][0], buildings[i][2]});
                }
                i++;
            }else{
                int pop_h = pq.top().first, pop_r = pq.top().second; pq.pop();
                while(!pq.empty() && pq.top().first<=pop_h && pq.top().second <= pop_r)
                    pq.pop();
                res.push_back({pop_r, pq.empty()? 0: pq.top().first});
            }
        }
        return res;
    }
};




/*

The idea is to do line sweep and just process the buildings only at the start and end points. 
The key is to use a priority queue to save all the buildings that are still "alive". 
The queue is sorted by its height and end time (the larger height first and if equal height, the one with a bigger end time first). 
For each iteration, we first find the current process time, which is either the next new building start time or the end time of the top entry of the live queue.
 If the new building start time is larger than the top one end time, 
 then process the one in the queue first (pop them until it is empty or find the first one that ends after the new building); 
 otherswise, if the new building starts before the top one ends, then process the new building (just put them in the queue). 
 After processing, output it to the resulting vector if the height changes. Complexity is the worst case O(NlogN)
*/


//https://github.com/beckswu/Leetcode/blob/master/Sort/218.%20The%20Skyline%20Problem.jpg
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> res;
        int cur=0, cur_X, cur_H =-1,  len = buildings.size();
        priority_queue< pair<int, int>> liveBlg; // first: height, second, end time
        while(cur<len || !liveBlg.empty())
        { // if either some new building is not processed or live building queue is not empty
            cur_X = liveBlg.empty()? buildings[cur][0]:liveBlg.top().second; // next timing point to process

            if(cur>=len || buildings[cur][0] > cur_X)
            { //first check if the current tallest building will end before the next timing point
                  // pop up the processed buildings, i.e. those  have height no larger than cur_H and end before the top one
                while(!liveBlg.empty() && ( liveBlg.top().second <= cur_X) ) liveBlg.pop();
                /*
                    把小于当前的cur_x end的弄出去，且height小于当前cur_x的，cur_x的height一定是queue中最大的，
                    remove后queue 剩下的就是落下之后的高度
                
                */
            }
            else
            { // if the next new building starts before the top one ends, process the new building in the vector
                cur_X = buildings[cur][0];
                while(cur<len && buildings[cur][0]== cur_X)  // go through all the new buildings that starts at the same point
                {  // just push them in the queue
                    liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
                    cur++;
                }
            }
            cur_H = liveBlg.empty()?0:liveBlg.top().first; // outut the top one
            if(res.empty() || (res.back().second != cur_H) ) res.push_back(make_pair(cur_X, cur_H));
            /*
            加上(res.back().second != cur_H)是避免新的条件新加进queue中的height是小于queue最高的
            [ [2 9 10], [3 7 15], [5 12 12]], 
            cur_x = 2, cur_h = 10, queue {10,9}
            cur_x = 3, cur_h = 15, queue {10,9} {15,7}
            cur_x = 5, cur_h = 15, queue {10,9} {15,7}, {12,12}  此时不append 进res
            */
        }
        return res;
    }
};



/*
explanation:
https://www.youtube.com/watch?v=GSBLe8cKu0s&t=864s

*/

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        pair<int,int> curr({0,0});
        vector<pair<int,int>> result;
        multiset<pair<int,int>> seq;
        for(auto p:buildings){
            seq.emplace(make_pair(p[0],-p[2]));
            seq.emplace(make_pair(p[1],p[2]));
        }
        multiset<int> height({0});
        for(auto p:seq){
            cout<<" seq first "<<p.first<<" sec "<<p.second<<endl;
            if(p.second<0)height.emplace(-p.second);
            else height.erase(height.find(p.second));
            if(*height.rbegin()!=curr.second){ //看最大的height是否发生了变化,变化了就append结果
                curr.first=p.first;
                curr.second=*height.rbegin();
                cout<<" in curr.first "<<curr.first<<" curr.second "<<curr.second<<endl;
                
                result.push_back(curr);
            }
        }
        return result;
    }
};
