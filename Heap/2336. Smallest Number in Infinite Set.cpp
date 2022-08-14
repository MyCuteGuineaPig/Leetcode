class SmallestInfiniteSet {
public:
    set<int>st;
    int cur = 0;
    SmallestInfiniteSet() {
        
    }
    
    int popSmallest() {
        if(st.empty())
            return ++cur;
        else{
            int res = *st.begin();
            st.erase(res);
            return res;
        }
        
    }
    
    void addBack(int num) {
        if (num <= cur ) {
            st.insert(num);
        } 
    }
};


class SmallestInfiniteSet {
public:
    int cur = 1;
    set<int> added; 
    int popSmallest() {
        if (!added.empty()) {
            int res = *begin(added);
            added.erase(begin(added));
            return res;
        }
        return cur++;
    }
    void addBack(int num) {
        if (num < cur)
            added.insert(num);
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */

