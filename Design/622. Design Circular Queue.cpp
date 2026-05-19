class MyCircularQueue {
private: 
    struct ListNode {
        shared_ptr<ListNode> next;
        int val;
        ListNode(int val, shared_ptr<ListNode> next): val(val), next(next) {}
        ListNode() {}
    };
    int capacity = 0;
    int count = 0;
    shared_ptr<ListNode> head;
    shared_ptr<ListNode> tail;
public:
    MyCircularQueue(int k) {
        capacity = k;
    }
    
    bool enQueue(int value) {
        if (count == capacity) {
            return false;
        }

        shared_ptr<ListNode> node = make_shared<ListNode>(value, nullptr);
        if(count == 0) {
            head = tail = node;
            head->next = tail;
        } else {
            tail->next = node;
            tail = node;
        }

        ++count;
        return true;
    }
    
    bool deQueue() {
        if(count == 0) return false;
        --count;
        head = head->next;
        return true;
    }
    
    int Front() {
        return count == 0 ? -1: head->val; 
    }
    
    int Rear() {
        return count == 0 ? -1: tail->val; 
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};



class MyCircularQueue {
private: 
    vector<int>data;
    int capacity = 0;
    int count = 0; 
    int head = 0;
public:
    MyCircularQueue(int k) {
        data.resize(k);
        count = 0;
        head = 0;
        capacity = k;
    }
    
    bool enQueue(int value) {
        if(isFull()) {
            return false;
        } 
        data[(head + count)% capacity] = value; //<-- important
        count++;
        return true;
    }
    
    bool deQueue() {
        if(isEmpty()) {
            return false;
        }
        head = (head + 1) % capacity; //<-- important
        --count;
        return true;
    }
    
    int Front() {
        return count == 0 ? -1 : data[head]; //<-- important
    }
    
    int Rear() {
        return count == 0 ? -1: data[(head+count-1) % capacity]; //<-- important
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */




//Array
class MyCircularQueue {
private:
    vector<int> queue;
    int headIndex;
    int count;
    int capacity;

public:
    // Constructor
    MyCircularQueue(int k) {
        capacity = k;
        queue.resize(k);
        headIndex = 0;
        count = 0;
    }

    // Insert an element into the circular queue
    bool enQueue(int value) {
        if (count == capacity)
            return false;
        queue[(headIndex + count) % capacity] = value;
        count++;
        return true;
    }

    // Delete an element from the circular queue
    bool deQueue() {
        if (count == 0)
            return false;
        headIndex = (headIndex + 1) % capacity;
        count--;
        return true;
    }

    // Get the front item
    int Front() {
        if (count == 0)
            return -1;
        return queue[headIndex];
    }

    // Get the last item
    int Rear() {
        if (count == 0)
            return -1;
        int tailIndex = (headIndex + count - 1) % capacity;
        return queue[tailIndex];
    }

    // Check if empty
    bool isEmpty() {
        return count == 0;
    }

    // Check if full
    bool isFull() {
        return count == capacity;
    }
};