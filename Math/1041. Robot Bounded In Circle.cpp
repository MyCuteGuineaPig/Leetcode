/*
If the robot doesn't face north at the end of the first cycle, then that's the limit cycle trajectory.

First, let's check which direction the robot faces after 4 cycles.

Let's use numbers from 0 to 3 to mark the directions: north = 0, east = 1, south = 2, west = 3. 

After one cycle the robot is facing direction k != 0.

After 4 cycles, the robot faces direction (k * 4) % 4 = 0, i.e. after 4 cycles, the robot is always facing north.

Second, let's find the robot coordinates after 4 cycles.


After one cycle, the new coordinates are x_1 = x +  d_x,  y_1 = y + d_y where d_x and d_y could be both positive or negative


1. After one cycle, the robot faces north.

x_1 = x +  d_x  +  d_x  +  d_x  +  d_x = x + 4 d_x
y_1 = y +  d_y  +  d_y  +  d_y  +  d_y = y + 4 d_y


2. After one cycle, the robot faces east.


x_1 = x +  d_x  -  d_y  -  d_x  +  d_y = x
y_1 = y +  d_y  +  d_x  -  d_y  -  d_x = y


3. After one cycle, the robot faces south.

x_1 = x +  d_x  -  d_x  +  d_x  -  d_x = x
y_1 = y +  d_y  +  d_y  -  d_y  +  d_y = y


4. After one cycle, the robot faces west.

x_1 = x +  d_x  +  d_y  -  d_x  -  d_y = x
y_1 = y +  d_y  -  d_x  -  d_y  +  d_x = y


*/


class Solution {
public:
    bool isRobotBounded(string instructions) {
        vector<vector<int>>direction = {{0,1},{-1,0}, {0,-1},{1,0}};
        int x = 0, y = 0, idx = 0;
        for(auto i: instructions){
            if(i == 'L' )
                idx = (idx + 1 )%4;
            else if(i == 'R')
                idx = (idx + 3) % 4;
            else{
                x += direction[idx][0];
                y += direction[idx][1];
            }
        }
        return (x == 0 && y == 0) || idx != 0; 
    }
};