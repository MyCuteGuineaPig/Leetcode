/*
232. Implement Queue using Stacks

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);  
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false
Notes:

You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).


*/



/*

Do you know when we should use two stacks to implement a queue?


he application for this implementation is to separate read & write of a queue in multi-processing. 
One of the stack is for read, and another is for write. They only interfere each other when the former one is full or latter is empty.


When there's only one thread doing the read/write operation to the stack, 
there will always one stack empty. However, in a multi-thread application, 
if we have only one queue, for thread-safety, either read or write will lock the whole queue. 
In the two stack implementation, as long as the second stack is not empty, push operation will not lock the stack for pop.

在多线程上，读和写可以同时进行，只要写的不为空，读可以push，写可以pop，写的要是为空，需要lock两个stack, dump读的进写的

*/





class MyQueue {
public:
    /** Initialize your data structure here. */
    stack<int>in;
    stack<int>out;
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        in.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int a = peek();
        out.pop();
        return a;
    }
    
    /** Get the front element. */
    int peek() {
        if(out.empty()){
            while(!in.empty()){
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return in.empty() && out.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */




class MyQueue {
    stack<int> queue;
    int front;
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if(queue.empty()) front = x;
        queue.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        stack<int> temp;
        int size = queue.size();
        for(int i=0;i<size-1;i++){
            temp.push(queue.top());
            queue.pop();
        }
        int ret = queue.top();  //把stack 所有元素倒过来，然后再还原回去
        queue.pop();
        if(!temp.empty()) front = temp.top();
        while(!temp.empty()){
            queue.push(temp.top());
            temp.pop();
        }
        return ret;
    }
    
    /** Get the front element. */
    int peek() {
        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return queue.empty();
    }
};




class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
		while (!nums.empty()) {
			helper.push(nums.top());
			nums.pop();
		}
		nums.push(x);
		while (!helper.empty()) {
			nums.push(helper.top());
			helper.pop();
		}
    }
    // Removes the element from in front of queue.
    void pop(void) {
        nums.pop();
    }
    // Get the front element.
    int peek(void) {
        return nums.top();
    }
    // Return whether the queue is empty.
    bool empty(void) {
		return nums.empty();
    }
private:
	std::stack<int> helper, nums;
};