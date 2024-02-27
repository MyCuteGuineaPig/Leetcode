/*

不会出现卡主的情况:

因为可能有多个enqueue wait, 或者多个dequeue wait
但不会同时 有enqueue 和 dequeue wait, 

所以 enqueue notify_one 必定call dequeue的
    dequeue notify_one 必定call enqueue的

比如 enqueue 1, dequeue, dequeue, enqueue 2


enqueue wait 条件  count == capacity： ,  所以count > 0, dequeue 不会wait
dequeue wait 条件  count == 0:           所以 count < capacity, 不会wait

step 1: 

thread 0: enqueue:  acquire lock
thread 1: dequeue 还没有acquire lock
thread 2: dequeue 还没有acquire lock
thread 3: enqueue: 还没有acquire lock

step 2: 
thread 0: push 1 进 q => notify_one

step 3: 
thread 1: dequeue acquire lock -> 因为 count > 0 不wait, 继续 pop 1 => notify_one

step 4:
thread 2: dequeue acquire lock -> 因为 count == 0， wait, release lock

step 5: 
thread 3: acquire lock,  因为 count < capacity, 不wait, push 2 => notify_one

step 6: 
thread 2: 被step 5的 thread 3 wake up -> pop 2 


*/

/*
不能用 notify_one 可能有问题
当 同时enqueue 和 dequeue 被block, 0 < count < capcacity, 先enqueue 或者先dequeu 都可以

当 size == capacity, cv.wait 叫起来了下一个enqueue request, 又被block住，而没有叫起来dequeue

*/


/*
Notifying waiters while holding the lock would cause waiters to wake-up and immediately block again.

Using block scope (unlock() before notify()) allows at least one waiter to acquire the lock after being signaled. 

It is beneficial for performance and not necessary for correctness.

*/

class BoundedBlockingQueue {
public:    
    BoundedBlockingQueue(int capacity)
      : cap_(capacity) {
        
    }
    
    void enqueue(int element) {
        {
            unique_lock<mutex> l(m_);
            cv_.wait(l, [this]() { return q_.size() != cap_; }) ;
            q_.emplace(element);
        }
        cv_.notify_all();
    }
    
    int dequeue() {
        int element;
        {
            unique_lock<mutex> l(m_);
            cv_.wait(l, [this]() { return !q_.empty(); }) ;
            element = q_.front(); q_.pop();
        }
        cv_.notify_all();
        return element;
    }
    
    int size() {
        unique_lock<mutex> l(m_);
        return q_.size();
    }

private:
    mutex m_;
    condition_variable cv_;
    queue<int> q_;
    int cap_;
};

class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) {
        q_size = capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex>lock(mu);
        cond_enqueue.wait(lock, [&]{return q.size() < q_size ;});
        q.push(element);
        cond_deque.notify_all();
    }
    
    int dequeue() {
        unique_lock<mutex>lock(mu);
        cond_deque.wait(lock, [&]{return q.size();});
        int top = q.front();
        q.pop();
        cond_enqueue.notify_all();
        return top;
    }
    
    int size() {
        int cur_size;
        {
            lock_guard<mutex>lock(mu);
            cur_size = q.size();
        }
        return cur_size;
    }
private: 
    mutex mu;
    int q_size;
    queue<int>q;
    condition_variable cond_deque, cond_enqueue;

};