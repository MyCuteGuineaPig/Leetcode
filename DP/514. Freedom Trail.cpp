/*
514. Freedom Trail

In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", 
and use the dial to spell a specific keyword in order to open the door.

Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword needs to be spelled.
 You need to find the minimum number of steps in order to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at 12:00 direction. You need to spell all the characters in the string key one by one
 by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button. 
At the stage of rotating the ring to spell the key character key[i]:
You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step. 
The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction, 
where this character must equal to the character key[i].
If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step.
 After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
Example:


Input: ring = "godding", key = "gd"
Output: 4
Explanation:
 For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
 For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 Also, we need 1 more step for spelling.
 So the final output is 4.

*/

/*
dp[i][j] 代表key中第i个char 是由ring中第j个过来的，上一个是j，到i需要的距离
但是这个solution 比较慢

*/

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size(), m = key.size();
        vector<vector<int>>dp(m,vector<int>(n,100000000));
        for(int i = m-1; i>=0; i--){
            for(int j = 0; j<n; j++){
                for(int k = 0; k<n; k++){
                    if(ring[k] == key[i]){
                        int diff = abs(k-j);
                        int steps = min(n-diff,diff);
                        if(i == m-1)
                            dp[i][j] = min(dp[i][j],steps);
                        else 
                            dp[i][j] = min(dp[i][j],steps+dp[i+1][k]); //steps+dp[i+1][k]，  dp[i+1][k]表示key的i+1从ring中k位置来的，steps表示从j到k，让现在ring 和key的imatch
                    }
                }   
            }
        }
        return dp[0][0]+m;
    }
};


/*
下面的比较快，先记录每个字母的位置，然后loop key，用loopup发现现在key的char的位置减去旧的位置作为step + 过去的minstep
旧的位置step存在dp，新的位置的step存在newDp, newDp = min(newDp, dp+step)，step是loop 移动的位置

记录ring每个字母的位置，字母位置push进vector(相同字母不同位置，vector有的长度大于1)，loop key,把i-1的字母vector作为起始点，
把key[i]字母vector作为现在点，loop（比如上一个字母是b,现在字母是c,ring中两个b，两个c，不知道哪个距离哪个最短，所以需要loop），
找到i位置最小移动距离，如果ring[k] = key[i], update dp[k]的值，

*/

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<vector<int>>mp(26);
        for(int i = 0; i<ring.size();i++)
            mp[ring[i]-'a'].push_back(i);

        vector<int>dp(ring.size(),INT_MAX);
        dp[0] = 0;
        vector<int>startIndex(1,0);
        for(int i = 0; i<key.size();i++){
            vector<int>newDp(ring.size(),INT_MAX);
            for(auto j: mp[key[i]-'a']){
                for(auto k: startIndex){
                    int diff = abs(k-j);
                    int step = min(diff, (int)ring.size()-diff);
                    newDp[j] = min(newDp[j], step+dp[k]);
                }
            }
            dp = newDp;
            startIndex = mp[key[i]-'a'];
        }

        int res = INT_MAX;
        for(auto i: dp)
            res = min(res, i);
        return res+key.size();

    }
};