/*
735. Asteroid Collision


We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

Example 1:
Input: 
asteroids = [5, 10, -5]
Output: [5, 10]
Explanation: 
The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
Example 2:
Input: 
asteroids = [8, -8]
Output: []
Explanation: 
The 8 and -8 collide exploding each other.
Example 3:
Input: 
asteroids = [10, 2, -5]
Output: [10]
Explanation: 
The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
Example 4:
Input: 
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]
Explanation: 
The -2 and -1 are moving left, while the 1 and 2 are moving right.
Asteroids moving the same direction never meet, so no asteroids will meet each other.
Note:

The length of asteroids will be at most 10000.
Each asteroid will be a non-zero integer in the range [-1000, 1000]..


*/

//write by own
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int>final;
        for(auto i: asteroids){
            if(final.empty() || final.back()<0 && i > 0 || final.back() * i > 0)
                //only pass if i < 0 && stack.top() > 0 which collison happens
                final.push_back(i);
            else{
                while(!final.empty() && final.back()>0 && i<0){
                    i = final.back() == -i ? 0 : final.back() > -i ? final.back(): i;
                    final.pop_back();
                }
                if(i)
                    final.push_back(i);
            }
        }
        return final;
    }
};


//self
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int>stk;
        for(auto i: asteroids){
            if(i<0){
                while(!stk.empty() && stk.back() > 0 && stk.back() < -i){
                    stk.pop_back();
                }
                if(stk.empty() || stk.back() < 0)
                    stk.push_back(i);
                else if(stk.back() == -i)
                    stk.pop_back();
            }
            else stk.push_back(i);
        }
        return stk;
    }
};


class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int>stk;
        for(int i = 0; i<asteroids.size(); i++){
            stk.push_back(asteroids[i]);
            while(stk.size()>1 && stk.back()<0 && stk[stk.size()-2]>0 ){
                if( stk.back() == -stk[stk.size()-2]){
                    stk.pop_back(); stk.pop_back();
                }
                else{
                    stk[stk.size()-2] = -stk.back() > stk[stk.size()-2] ? stk.back() : stk[stk.size()-2];
                    stk.pop_back();
                }
            }
        }
        return stk;
    }
};


/*
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]

碰撞的都是back>0, i<0的, 如果back < -i, pop back （比如 back 7, i = -10, 就pop out 7)
如果i>0 , 没有碰撞，铁定push 进stack， 
如果i < 0, 看back 是不是小于0(之前都是小于0的，或则stack为空，不会出现[10,-5], 也不会出现[5,,-10])，是的话 也push i, 比如 stack [ -2] i < 0
*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& a) {
        vector<int> s; // use vector to simulate stack.
        for (int i : a) {
            while (!s.empty() && s.back() > 0 && s.back() < -i)
                s.pop_back();
                //^while top element gets lashed out by an Opposite Asteroid which is of Higher Value
            	//Eg. top([5, 10]) < -(-15) -> Pop Until Opposite asteroid is lashed out by Stack Top
            if (s.empty() || i > 0 || s.back() < 0)//i>0 碰撞的都是新的i小于0的 如果i>0,代表没有碰撞 push_back
                s.push_back(i);
            	//^ If it's empty or if AST is greater value or Stack top is of Lesser Value -> Keep pushing
            else if (i < 0 && s.back() == -i)//when TOP and AST are Equal Eg. top([5, 10]) == -(-10) -> Pop
                s.pop_back();
        }
        return s;
    }
};


class Solution {
public:
    vector<int> asteroidCollision(vector<int>& a) {
        vector<int> s; // use vector to simulate stack.
        for (int i = 0; i < a.size(); i++) {
            if (a[i] > 0 || s.empty() || s.back() < 0) // a[i] is positive star or a[i] is negative star and there is no positive on stack
                s.push_back(a[i]);
            else if (s.back() <= -a[i]) { // a[i] is negative star and stack top is positive star
                if(s.back() < -a[i]) i--; // only positive star on stack top get destroyed, stay on i to check more on stack.
                s.pop_back(); // destroy positive star on the frontier;
            } // else : positive on stack bigger, negative star destroyed.
        }
        return s;
    }
};

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> result;
        for (const auto& asteroid : asteroids) {
            bool is_exploded = false;
            while (!result.empty() && asteroid < 0 && 0 < result.back()) {
                if (result.back() < -asteroid) {
                    result.pop_back();
                    continue;
                } else if (result.back() == -asteroid) {
                    result.pop_back();
                }
                is_exploded = true;
                break;
            }
            if (!is_exploded) {
                result.emplace_back(asteroid);
            }
        }
        return result;
    }
};
