/*
853. Car Fleet


N cars are going to the same destination along a one lane road.  The destination is target miles away.

Each car i has a constant speed speed[i] (in miles per hour), and initial position position[i] miles towards the target along the road.

A car can never pass another car ahead of it, but it can catch up to it, and drive bumper to bumper at the same speed.

The distance between these two cars is ignored - they are assumed to have the same position.

A car fleet is some non-empty set of cars driving at the same position and same speed.  Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point, it will still be considered as one car fleet.


How many car fleets will arrive at the destination?

 

Example 1:

Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 and 8 become a fleet, meeting each other at 12.
The car starting at 0 doesn't catch up to any other car, so it is a fleet by itself.
The cars starting at 5 and 3 become a fleet, meeting each other at 6.
Note that no other cars meet these fleets before the destination, so the answer is 3.

Note:

0 <= N <= 10 ^ 4
0 < target <= 10 ^ 6
0 < speed[i] <= 10 ^ 6
0 <= position[i] < target
All initial positions are different.

*/

/*
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
根据position 由大到小sort，然后到达终点时间 由大到小sort, 

这么work的原因是：
sort 结果是 [[10, 2],[8,2]] 如果后面的时间小于前面的时间，表示可以追上，
不用担心如果数字小的本来在前面，sort之后被放到后面， 因为出发位置小的，在后面出发，而不是说0在5的前面位置出发


*/
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        if(position.empty()) return 0;
        vector<pair<int,double>>car;
        for(int i = 0; i<position.size();i++){
            car.push_back({position[i], static_cast<double>(target-position[i])/speed[i]});
        }
        sort(car.begin(),car.end());
        reverse(car.begin(),car.end());
        double time = car[0].second;
        int count = 1;
        for(auto i: car){
            if(i.second>time){
                count++;
                time = i.second;
            }
        }
        return count;
    }
};

class Solution {
public:
    int carFleet(int target, vector<int>& pos, vector<int>& speed, int fl = 0, double time = 0) {
        map<int, double> m;
        for (auto i = 0; i < pos.size(); ++i) m[pos[i]] = ((double)target - pos[i]) / speed[i];
        for (auto it = m.rbegin(); it != m.rend(); ++it) {
            if (it->second > time) ++fl, time = it->second;
        }
        return fl;
    }
};
