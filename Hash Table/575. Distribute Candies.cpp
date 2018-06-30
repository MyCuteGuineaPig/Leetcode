/*
575. Distribute Candies


Given an integer array with even length, where different numbers in this array represent different kinds of candies. 
Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and sister. 
Return the maximum number of kinds of candies the sister could gain.

Example 1:
Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too. 
The sister has three different kinds of candies. 
Example 2:
Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has candies [1,1]. 
The sister has two different kinds of candies, the brother has only one kind of candies. 
Note:

The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].
*/

/*
Trick: 
分给两个人，如果种类大于 candies size/ 2, 分的多的种类就是 candies,size()/2
如果种类小于 candies size / 2,就是种类的size

*/
class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        unordered_set<int>set;
        for(auto i: candies)
            set.insert(i);
        return min(set.size(), candies.size()/2);
    }
};


class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> s;
        int n = candies.size() / 2;
        for (int candy : candies) {
            if (s.find(candy) == s.end()) {
                s.insert(candy);
            }
            if (s.size() > n) {
                return n;
            }
        }
        return s.size();
    }
};


class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        bitset<200000> bs;
        int count = 0;
        for(int i = 0; i < candies.size(); i++) {
            if(bs[candies[i]+100000]) continue;
            bs[candies[i]+100000] = 1;
            count++;
        }
        int n = candies.size() / 2;
        return min(n, count);
    }
};
class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        int len = candies.size();
        if(len < 2 || len > 10000) return {};
        bitset<200001> bs;
        int cnt = 0;
        for(int i = 0; i < len; i++){
            cnt += !bs.test(candies[i] + 100000);
            bs.set(candies[i] + 100000);
        }
        return min(cnt, len / 2);
    }
};



class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        size_t kinds = 1;
        sort(candies.begin(), candies.end());
        for (int i = 0; i < candies.size(); i++) {
            kinds += candies[i] != candies[i - 1];
        }
        return min(kinds, candies.size() / 2);
    }
};