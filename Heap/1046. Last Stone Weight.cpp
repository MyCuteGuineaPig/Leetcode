class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int>pq(stones.begin(), stones.end());
        while(pq.size()>1){
            int y = pq.top(); pq.pop();
            int x = pq.top(); pq.pop();
            if(y - x)
                pq.push(y-x);
        }
        return pq.size() ? pq.top(): 0;
    }
};

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        multiset<int>pq(stones.begin(), stones.end());
        while(pq.size()>1){
            int y = *pq.rbegin(); pq.erase(prev(pq.end())); //not support erase(pq.rbegin())
            int x = *pq.rbegin(); pq.erase(prev(pq.end()));
            if(y - x)
                pq.insert(y-x);
        }
        return pq.size() ? *pq.begin(): 0;
    }
};



//bucket sort
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        vector<int>buckets(1001,0);
        for(auto i: stones)
            buckets[i]++;
        int slow = 1000; //start from the big to small
        for(; slow; slow--){

         // If the number of stones with the same size is even or zero, 
		// these stones can be totally destroyed pair by pair or there is no such size stone existing, 
		// we can just ignore this situation.
		
        // When the number of stones with the same size is odd, 
		// there should leave one stone which is to smash with the smaller size one.   
            if(buckets[slow] % 2 != 0){
                int fast = slow - 1;
                while(fast && buckets[fast] == 0)
                    fast -= 1;
                
                if(fast == 0) break;
                buckets[fast]--;
                buckets[slow - fast] ++;
            }
        }
        return slow;
    }
};