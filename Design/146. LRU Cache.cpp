class LRUCache {
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }
    
    int get(int key) {
        if(map_.find(key) != map_.end()){
            int value = map_[key]->second;
            update(key, value);
            return value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(map_.size() == capacity_ && map_.find(key)==map_.end()){
            int key = list_.back().first;
            map_.erase(key);
            list_.erase(prev(list_.end(),1));
        }
        update(key, value); 
    }
    
    void update(int key, int value){
        if(map_.find(key) != map_.end()){
            list_.erase(map_[key]);
        }
        list_.push_front({key, value});
        map_[key] = list_.begin();
    }
    
    int capacity_;
    unordered_map<int, list<pair<int,int>>::iterator>map_;
    list<pair<int,int>>list_; //key value, key is used for when delete value 
    
};