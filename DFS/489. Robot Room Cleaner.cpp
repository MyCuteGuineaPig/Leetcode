/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

class Solution {
private: 
    vector<vector<int>>directions = {{-1, 0}, {0,1}, {1,0}, {0, -1}};
public:

    void cleanRoom(Robot& robot) {
        unordered_set<string>visited;
        clean(robot, 0, 0, 0 , visited);
    }

    void clean(Robot& robot, int x, int y, int dir, unordered_set<string>&visited){

        string key = to_string(x) + " "+to_string(y);
        visited.insert(key);
        robot.clean();
        for(int i = dir; i<dir+4; ++i){
            int n_x = x + directions[i%4][0]; 
            int n_y = y + directions[i%4][1]; 
            if (!visited.count(to_string(n_x) + " "+to_string(n_y)) && robot.move()){
                clean(robot, n_x, n_y, i%4, visited);
                // backtrack to its original place
                robot.turnRight();
                robot.turnRight();
                robot.move();
                robot.turnRight();
                robot.turnRight();
            }
            robot.turnRight();
        }

    }
};