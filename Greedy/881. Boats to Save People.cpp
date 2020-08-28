
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
        for (j = people.size() - 1, i = 0; i <= j; --j) { //减了几次j就是几个船
            if (!(people[i]+people[j] > limit)) ++i;
        }
        return int(people.size()) -1 - j;
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





//O(limit)
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        vector<int>buckets(limit+1);
        for(int p: people) buckets[p]++;
        int start = 0;
        int end = limit;
        int solution = 0;
        while(start <= end) {
			//make sure the start always point to a valid number
            while(start <= end && buckets[start] <= 0) start++;
			//make sure end always point to valid number
            while(start <= end && buckets[end] <= 0) end--;
			//no one else left on the ship, hence break.
            if(buckets[start] <= 0 && buckets[end] <= 0) break;
            solution++;
            if(start + end <= limit) buckets[start]--; // both start and end can carry on the boat
            buckets[end]--;
        }
        return solution;
    }
};