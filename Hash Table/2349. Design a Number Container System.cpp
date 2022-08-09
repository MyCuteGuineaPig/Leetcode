class NumberContainers {
public:
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        if (mp.count(index)) {
            number_index[mp[index]].erase(index);
            if (number_index[mp[index]].empty())
                number_index.erase(mp[index]);
        }
        number_index[number].insert(index);
        mp[index] = number;
    }
    
    int find(int number) {
        if (number_index.count(number) == 0) return -1;
        return *(number_index[number].begin());
    }
    
    unordered_map<int, set<int>>number_index;
    unordered_map<int, int>mp;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */