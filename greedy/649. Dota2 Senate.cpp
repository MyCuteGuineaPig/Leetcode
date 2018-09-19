/*
649. Dota2 Senate649. Dota2 Senate
https://leetcode.com/problems/dota2-senate/description/


In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. Now the senate wants to make a decision about a change in the Dota2 game. 
The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:

Ban one senator's right: 
A senator can make another senator lose all his rights in this and all the following rounds.
Announce the victory: 
If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and make the decision about the change in the game.
Given a string representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party respectively. Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party, you need to predict which party will finally announce the victory and make the change in the Dota2 game. The output should be Radiant or Dire.

Example 1:
Input: "RD"
Output: "Radiant"
Explanation: The first senator comes from Radiant and he can just ban the next senator's right in the round 1. 
And the second senator can't exercise any rights any more since his right has been banned. 
And in the round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
Example 2:
Input: "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in the round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in the round 1. 
And in the round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.

*/


/*

R 和 D一一对比，index小的赢，直到一方全军覆没，
因为是循环的，所以赢得一方下次出现的index = i+n; 

用queue的好处，因为push是按照index push 的，所以queue 是又小到大排序的，queue.front就是当前最靠前的元素

*/

class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int>qR,qD;
        int n = senate.size();
        for(int i = 0; i<n; i++)
            senate[i]=='R'? qR.push(i) : qD.push(i);
        while(qR.size() && qD.size()){
            int r_index = qR.front(), d_index = qD.front();
            qR.pop(); qD.pop();
            r_index < d_index ? qR.push(r_index+n):qD.push(d_index+n);
        }
        return qR.size() ? "Radiant" : "Dire";
    }
};


/*
len = s 表示上一句的没有消灭，表示一方已经获胜

*/
class Solution {
public:
    string predictPartyVictory(string senate) {
        string s = senate;
        int cnt = 0, len = 0;
        while (len != s.size()) {
            string ns;
            len = s.size();
            for (auto c: s) {
                if (c == 'D' && ++cnt > 0) {
                    ns += c;
                } else if (c == 'R' && --cnt < 0){
                    ns += c;
                }
            }
            s = ns;
        }
        return (s.front() == 'D')?"Dire":"Radiant";
    }
};


/*
people当前还有多少个战士各自，如果一方全军覆没，战斗结束
ban 表示当前index，被禁的，比如ban[0]>0, 当后面出现index时候的，被杀掉，不用append

*/
class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int>q; vector<int>ban(2,0); 
        vector<int>people(2,0);
        for(auto s: senate){
            int cur = s == 'R';
            people[cur]++; q.push(cur);
        }
            
        while(people[0] && people[1]){
            int cur = q.front(); q.pop();
            if(ban[cur]) {
                ban[cur]--;
                people[cur]--;
            }
            else{
                ban[cur^1]++;
                q.push(cur);
            }
        }
        return people[0]>0 ? "Dire": "Radiant";
    }
};




class Solution {
public:
    string predictPartyVictory(string senate) {
        int count = 0, len = 0;
        // When the length of senate doesn't decrease, the game is over.
        while (senate.size() != len) {
            string s;
            len = senate.size();
            for (int i = 0; i < len; i++) {
                if (senate[i] == 'R') {
                    if (count++ >= 0) s += 'R';
                }
                else if (senate[i] == 'D') {
                    if (count-- <= 0) s += 'D';
                }
            }  
            swap(s, senate);
        }
        if (senate[0] == 'R') 
            return "Radiant";
        else 
            return "Dire";
    }
};

class Solution {
public:

    string predictPartyVictory(string senate) {
        int r_count = 0, d_count = 0;
		while(true) {
			string s;
			for (int i = 0; i < senate.size(); i++) {
				if (senate[i] == 'R') {
					if (d_count == 0) {
						s += 'R';
						r_count++;
					} else {
						d_count--;
					}
				} else {
					if (r_count == 0) {
						s += 'D';
						d_count++;
					} else {
						r_count--;
					}
				}
			}
			if (s == senate) break;
			senate = std::move(s);
		}
		return senate[0] == 'R' ? "Radiant" : "Dire";
    }
};
