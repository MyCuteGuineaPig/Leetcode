/*
825. Friends Of Appropriate Ages


Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person. 

Person A will NOT friend request person B (B != A) if any of the following conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.

*/
//[108,115,5,24,82]  5, 24, 82, 108, 115


/*
Sort + binary search: 
max(cur, 0); 是因为比如 [5, 24, 82, 108, 115], 当ages[i] = 5, lowerbound 返回24(5*0.5+8 = 10)，upperbound 返回24, 再减去1，等于-1了

75ms
O(nlogn)
*/
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(),ages.end());
        int res = 0;
        for(int i = 0; i<ages.size();i++){
            int lower = ages[i]*0.5 + 8;
            int cur = upper_bound(ages.begin(),ages.end(),ages[i]) - lower_bound(ages.begin(),ages.end(),lower)-1;
            res += max(cur, 0);
        }
        return res;
    }
};

/*
use unordered_map
O(n + k^2) k is the unordered_map size 
46ms
*/
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        unordered_map<int,int>m;
        for(auto i: ages)
            m[i]++;
        int res = 0;
        for(auto i1: m){
            for(auto i2: m){
                if((i2.first <= i1.first && i2.first>i1.first*0.5 + 7)){
                    res += i2.second*(i1.second - (i1.first == i2.first ? 1:0));
                }
            }
        }
        return res;
    }
};

/*
use map  

51 ms
*/
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        map<int,int>m;
        for(auto i: ages)
            m[i]++;
        int res = 0;
        for(auto i1: m){
            for(auto i2: m){
                if((i2.first <= i1.first && i2.first>i1.first*0.5 + 7)){
                    res += i2.second*(i1.second - (i1.first == i2.first ? 1:0));
                }
                else if(i2.first>i1.first) break;
            }
        }
        return res;
    }
};