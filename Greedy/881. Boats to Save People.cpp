/*
881. Boats to Save People


The i-th person has weight people[i], and each boat can carry a maximum weight of limit.

Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.  
(It is guaranteed each person can be carried by a boat.)

 

Example 1:

Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
Example 2:

Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
Example 3:

Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
Note:

1 <= people.length <= 50000
1 <= people[i] <= limit <= 30000

*/

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int count = 0, cur = 0;
        for(int i = 0, j = people.size()-1; i<=j; j--){
            int cur = people[j];
            if(cur + people[i] <= limit) i++;
            count++;
        }
        return count;
    }
};

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int i,j;
        for (j = people.size() - 1, i = 0; i <= j; --j) {
            if (!(people[i]+people[j] > limit)) ++i;
        }
        return int(people.size()) - j - 1;
    }
};


class Solution {
public:
    // note: each boat can carry at most 2 people 
    int numRescueBoats(vector<int> people, int limit) {
        int i, j;
        sort(people.rbegin(), people.rend());
        for (i = 0, j = people.size() - 1; i <= j; ++i)
            if (people[i] + people[j] <= limit) j--;
        return i;
    }
};