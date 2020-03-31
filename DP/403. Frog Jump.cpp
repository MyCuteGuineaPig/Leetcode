/*
403. Frog Jump

A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. 
The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. 
Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units.
 Note that the frog can only jump in the forward direction.

Note:

The number of stones is ≥ 2 and is < 1,100.
Each stone's position will be a non-negative integer < 231.
The first stone's position is always 0.
Example 1:

[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping 
1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.

*/

/*
backtrack 会timeout 因为这个会重复很多，比如现在move是10， next move 11，start 是100, 
vector有100，101，102，103，104，105，106，107，108，112，往前动了12，发现不行，又回到100，
然后next move是10，再roll from 100到110，又动了10还是不行
然后next move是9，再roll from 100到109，发现不行，于是重复了很多遍

*/

class Solution {
public:
    bool canCross(vector<int>& stones) {
        return backtrack(stones,1,1);
    }
    
    bool backtrack(vector<int>&stones, int index, int k){
        if(index == stones.size())
            return true;
        for(int i = index; i<stones.size()&& stones[i]<=stones[index-1]+k;i++){
            if(stones[i] == stones[index-1]+k){
                if(backtrack(stones,i+1, k+1) || backtrack(stones,i+1, k) || (k>1 && backtrack(stones,i+1, k-1)))
                    return true;
            }
        }
        return false;
    }
};

/*
DFS 也timeout 

*/

class Solution {
public:
    bool canCross(vector<int>& stones, int pos = 0, int k = 0) {
        for (int i = pos + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[pos];
            if (gap < k - 1) continue;
            if (gap > k + 1) return false;
            if (canCross(stones, i, gap)) return true;
        }
        return pos == stones.size() - 1;
    }
};

/****************ACCEPT SOLUTION ***********************/

/*
把k和 pos combine起来，比如第8位置的k=2， 和第8位置k=3，key是不一样的

*/
class Solution {
public:
unordered_map<int, bool> dp;

    bool canCross(vector<int>& stones, int pos = 0, int k = 0) {
        int key = pos | k << 11;

        if (dp.count(key) > 0)
            return dp[key];

        for (int i = pos + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[pos];
            if (gap < k - 1)
                continue;
            if (gap > k + 1)
                return dp[key] = false;
            if (canCross(stones, i, gap))
                return dp[key] = true;
        }

        return dp[key] = (pos == stones.size() - 1);
    }
};

/****************ACCEPT SOLUTION ***********************/
/*
DP
*/


class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones[1]!=1) return false;
        unordered_map<int,unordered_set<int>>dp;
        for(auto i: stones)
            dp[i] = {};
        dp[1].insert(1);
        for(int i = 1; i<stones.size()-1;i++){
            for(auto j: dp[stones[i]]){
                for(int move: {j-1, j, j+1}){
                    if(move>0 && dp.count(move+stones[i])){
                        dp[move+stones[i]].insert(move);
                    }
                }
            }
        }
        return dp[stones.back()].size()!=0;
    }
};