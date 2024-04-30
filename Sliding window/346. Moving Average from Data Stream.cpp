class MovingAverage {
public:
    queue<int>q;
    int capacity;
    double total;
    MovingAverage(int size) {
        capacity = size;
    }
    
    double next(int val) {
        if(q.size() == capacity){
            total -= q.front(); q.pop();
        }
        q.push(val);
        total += val;
        return total / q.size();
    }
};