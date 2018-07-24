/*
657. Judge Route Circle

Initially, there is a Robot at position (0, 0). Given a sequence of its moves, 
judge if this robot makes a circle, which means it moves back to the original place.

The move sequence is represented by a string. And each move is represent by a character. 
The valid robot moves are R (Right), L (Left), U (Up) and D (down). 
The output should be true or false representing whether the robot makes a circle.

Example 1:
Input: "UD"
Output: true
Example 2:
Input: "LL"
Output: false


*/


class Solution {
public:
    bool judgeCircle(string moves) {
        int up = 0, left = 0;
        for(auto i : moves)
        {
            if( i == 'U' || i == 'D') up += i == 'U' ? 1 : -1;
            else left += i == 'L' ? 1 : -1;
        }
        return up == 0 && left == 0;
    }
};


class Solution {
public:
    bool judgeCircle(string moves) {
        auto v = 0, h = 0;
        for (const auto& move : moves) {
            switch (move) {
                case 'U': ++v; break;
                case 'D': --v; break;
                case 'R': ++h; break;
                case 'L': --h; break;
            }
        }
        return v == 0 && h == 0;
    }
