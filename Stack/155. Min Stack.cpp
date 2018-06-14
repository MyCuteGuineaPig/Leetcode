/*
155. Min Stack


Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

*/

/*
两个stack,一个用来正常的push pop，另一个作为min stack用来存最小值(stk中的数是从小到大排序的)，

只有当新来的小于等于minstack.top()，再push，pop时候，
如果普通stack.top() == minstack.top(),minstack也pop

*/

class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>stk;
    stack<int>minstk;
    MinStack() {
        
    }
    
    void push(int x) {
        stk.push(x);
        if(minstk.empty() || x<=minstk.top()) minstk.push(x);
    }
    
    void pop() {
        if(stk.top()==minstk.top()) minstk.pop();
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minstk.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */



// Time:  O(n)
// Space: O(1)


/*
stack 放进去的是: 数和之前min的差，如果差是正数，代表最小的还是原来的min，一旦差是负数，代表现在这个数是min
比如push  10, 7, 8, 6, 4, 5
10:   stk: 0,  min:  10
7,    stk: -3, 0,  min: 7
8,    stk: 1, -3, 0  min: 7
6,    stk: -1, 1, -3, 0   min: 6
4,    stk: -2, -1, 1, -3, 0, min: 4
5,    stk: 1, -2, -1, 1, -3, 0, min: 4

pop:  
5:  stk: -2， -1， 1， -3， 0 min:4
4:  stk:  -1, 1, -3, 0   min: 4-(-2) = 6
6:   stk:  1, -3, 0,    min: 6-(-1) = 7
7,  stk:  -3, 0,   min = 10
10:  stk: 0, min = 10


*/


class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        if(stk.empty()){
            minv = x;
            stk.push(0);
        }else{
            stk.push(static_cast<int64_t>(x)-minv);//存现在这个数比min的差，如果差小于0，需要更新min，大于0的，代表这个数比min大，不用管
            if(stk.top()<0) minv = x;// Restore previous min.
        }
    }
    
    void pop() {
        int64_t diff = stk.top();
        stk.pop();
        if(diff<0)
            minv = minv - diff;// Restore previous min.
    }
    
    int top() {
        if(stk.top()>0){
            return stk.top() + minv;
        }else return minv;
    }
    
    int getMin() {
        return minv;
    }
    stack<int64_t> stk;
    int minv;
};






class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>stk;
    multiset<int>set;
    MinStack() {
        
    }
    
    void push(int x) {
        stk.push(x);
        set.insert(x);
    }
    
    void pop() {
        set.erase(set.find(stk.top()));
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return *set.begin();
    }
};

