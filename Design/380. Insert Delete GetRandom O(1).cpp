class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    unordered_map<int,int>index;
    vector<int>nums;
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(index.count(val)) 
            return false;
        index[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(index.count(val) == 0)
            return false;
        if(index[val] != nums.size()-1){
            int last = nums[nums.size()-1];
            nums[index[val]] = last;
            index[last] = index[val];
        }
        index.erase(val);
        nums.pop_back();
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (used_.count(val)) {
            return false;
        }

        set_.emplace_back(val);
        used_[val] = set_.size() - 1;

        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (!used_.count(val)) {
            return false;
        }

        used_[set_.back()] = used_[val];
        swap(set_[used_[val]], set_.back());

        used_.erase(val);
        set_.pop_back();

        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return set_[rand() % set_.size()];
    }

private:
    vector<int> set_;
    unordered_map<int, int> used_;
};