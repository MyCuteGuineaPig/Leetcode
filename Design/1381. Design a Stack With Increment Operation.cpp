class CustomStack {
public:
    vector<int> stack, inc;
    int n;
    CustomStack(int maxSize) {
        n = maxSize;
    }

    void push(int x) {
        if (stack.size() == n) return;
        stack.push_back(x);
        inc.push_back(0);
    }

    int pop() {
        int i = stack.size() - 1;
        if (i < 0) return -1;
        if (i > 0) inc[i - 1] += inc[i];
        int res = stack[i] + inc[i];
        stack.pop_back();
        inc.pop_back();
        return res;
    }

    void increment(int k, int val) {
        int i = min(k, (int)stack.size()) - 1;
        if (i >= 0) inc[i] += val;
    }
};


//Deque 可以loop
class CustomStack {
public:
    // Space Complexity: O(n)
    deque<int> dq;
    int n;
    
    CustomStack(int maxSize) {
        // Time Complexity: O(1)
        n = maxSize;
    }
    
    void push(int x) {
        // Time Complexity: O(1)
        if (dq.size() == n) return;
        dq.push_back(x);
    }
    
    int pop() {
        // Time Complexity: O(1)
        if (dq.empty()) return -1;
        int x = dq.back();
        dq.pop_back();
        return x;
    }
    
    void increment(int k, int val) {
        // Time Complexity: O(k)
        for (auto it = dq.begin(); it != (k > dq.size() ? dq.end() : dq.begin() + k); ++it)
            *it += val;
    }
};
