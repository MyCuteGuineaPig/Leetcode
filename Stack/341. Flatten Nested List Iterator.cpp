/*
341. Flatten Nested List Iterator

Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].



*/

// Solution 1 Stack + recursion
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size()-1; i>=0; i--){
            get_num(nestedList[i]);
        }
    }
    
    void get_num(NestedInteger ni){
        if(ni.isInteger()) stk.push(ni.getInteger());
        else{
            for(int i = ni.getList().size()-1; i>=0;i--){
                get_num(ni.getList()[i]);
            }
        }
    }

    int next() {
        int res = stk.top();
        stk.pop();
        return res;
    }

    bool hasNext() {
        return !stk.empty();
    }
    stack<int>stk;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) : s(0) {
        getList_R(nestedList, 0, ans);
    }

    int next() { 
        return ans[s++];
    }

    bool hasNext() { 
        return s < ans.size(); 
    }
    
private:
    vector<int> ans;
    int s;
    
    void getList_R(vector<NestedInteger>& nestedList, int start, vector<int>& flatList) {
        if (start == nestedList.size()) return;
        
        nestedList[start].isInteger() ? 
            flatList.push_back(nestedList[start].getInteger()) :
            getList_R(nestedList[start].getList(), 0, flatList);
        
        getList_R(nestedList, start+1, flatList);
    }        
};


//Solution 2 Queue
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        addToQueue(nestedList);    
    }

    int next() {
        int n = q.front();
        q.pop();
        return n;
    }

    bool hasNext() {
        return !q.empty();    
    }
    
private:
    queue<int> q;
    void addToQueue(vector<NestedInteger>& nestedList)
    {
        for (auto e : nestedList)
        {
            if (e.isInteger()) q.push(e.getInteger());
            else addToQueue(e.getList());
        }
    }
};




/*
Stack of NestedInteger, hasNext generate number
*/
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size()-1; i>=0; i--){
            stk.push(nestedList[i]);
        }
    }
    

    int next() {
        int res = stk.top().getInteger();
        stk.pop();
        return res;
    }

    bool hasNext() {
        while(!stk.empty()){
            if(stk.top().isInteger()) return true;
            auto nxt = stk.top().getList(); stk.pop();
            for(int i = nxt.size()-1; i>=0; i--)
                stk.push(nxt[i]);
        }
        return false;
    }
    stack<NestedInteger>stk;
};




// Using stack and iterator.
class NestedIterator {
public:
    using IT = vector<NestedInteger>::const_iterator;
    NestedIterator(vector<NestedInteger> &nestedList) {
        depth_.emplace(nestedList.cbegin(), nestedList.cend());
    }

    int next() {
        return (depth_.top().first++)->getInteger();
    }
    
    bool hasNext() {
        while (!depth_.empty()) {
            auto& cur = depth_.top();
            if (cur.first == cur.second) {
                depth_.pop();
            } else if (cur.first->isInteger()) {
                return true;
            } else {
                auto& nestedList = cur.first->getList();
                ++cur.first; //push的时候++， 
                depth_.emplace(nestedList.cbegin(), nestedList.cend());
            }
        }
        return false;
    }

private:
    stack<pair<IT, IT>> depth_;
};


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    using IT = vector<NestedInteger>::const_iterator;
    NestedIterator(vector<NestedInteger> &nestedList) {
       stk.push({nestedList.cbegin(), nestedList.cend()});
    }
    

    int next() {
        return (stk.top().first++)->getInteger();;
    }
    

    bool hasNext() {
        while(!stk.empty()){
            if(stk.top().first == stk.top().second){
                stk.pop();
                if(!stk.empty())
                    stk.top().first++; //pop 时候
            }else{
                if(stk.top().first->isInteger())return true;
                else{
                    stk.push({stk.top().first->getList().cbegin(), stk.top().first->getList().cend()});
                }
            }
        }
        return false; 
    }
    stack<pair<IT,IT>>stk;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */



class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        begins.push(nestedList.begin());
        ends.push(nestedList.end());
    }

    int next() {
        hasNext();
        return (begins.top()++)->getInteger();
    }

    bool hasNext() {
        while (begins.size()) {
            if (begins.top() == ends.top()) {
                begins.pop();
                ends.pop();
            } else {
                auto x = begins.top();
                if (x->isInteger())
                    return true;
                begins.top()++;
                begins.push(x->getList().begin());
                ends.push(x->getList().end());
            }
        }
        return false;
    }

private:
    stack<vector<NestedInteger>::iterator> begins, ends;
};
