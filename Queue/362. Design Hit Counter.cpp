class HitCounter {
private:
    
    int total;
    queue<pair<int, int> > hits;
    
public:
    
    /** Initialize your data structure here. */
    HitCounter() {
        this->total = 0;
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        if (this->hits.empty() || this->hits.back().first != timestamp) {
            // Insert the new timestamp with count = 1
            this->hits.push({timestamp, 1});
        } else {
            // Update the count of latest timestamp by incrementing the count by 1
            this->hits.back().second++;
        }
        this->total++;
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        while (!this->hits.empty()) {
            int diff = timestamp - this->hits.front().first;
            if (diff >= 300) {
                // Decrement total by the count of the oldest timestamp
                this->total -= this->hits.front().second;
                this->hits.pop();
            }
            else break;
        }
        return this->total;
    }
};

/*
this solution will takes too much memory since each element in queue is a single hit.
 It's better to map timestamp to the number of hits at this timestamp.
*/
class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {
        
    }
    queue<int>hits;
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        hits.push(timestamp);
        int prev = timestamp - 300;
        while(!hits.empty() && hits.front() <= prev){
            hits.pop();
        }
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int prev = timestamp - 300;
        while(!hits.empty() && hits.front() <= prev){
            hits.pop();
        }
        return hits.size();
    }
};


class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {
        times.resize(300,0);
        hits.resize(300, 0);
    }
    vector<int>times;
    vector<int>hits;
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        int index = timestamp % 300;
        if (times[index] != timestamp) {
            times[index] = timestamp;
            hits[index] = 1;
        } else {
            hits[index]++;
        }
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int total = 0;
        for (int i = 0; i < 300; i++) {
            if (timestamp - times[i] < 300) {
                total += hits[i];
            }
        }
        return total;
    }
};