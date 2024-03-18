//void splice (iterator position, list& x);
//void splice (iterator position, list& x, iterator i);
//void splice (iterator position, list& x, iterator first, iterator last);
//Transfers elements from x into the container, inserting them at position.
//The first version (1) transfers all the elements of x into the container.
//The second version (2) transfers only the element pointed by i from x into the container.
//The third version (3) transfers the range [first,last) from x into the container.



class LRUCache {
    int capacity;
    list<pair<int, int>> li;
    unordered_map<int, list<pair<int, int>>::iterator> um; 

public:
    LRUCache(int capacity) : capacity{capacity} {}
    
    int get(int key) {
        if (um.find(key) == um.end()) return -1;
        li.splice(li.begin(), li, um[key]);
        return um[key]->second;
    }
    
    void put(int key, int value) {
        if (get(key) != -1) {
            um[key]->second = value;
            return;
        }
        
        if (um.size() == capacity) {
            int delKey = li.back().first;
            li.pop_back();
            um.erase(delKey);
        }
        
        li.emplace_front(key, value);
        um[key] = li.begin();
    }
};


class LRUCache {
private:
    // A list of (key, value) pairs
    list<pair<int, int>> items;
    // Map items to iterators (pointers) to list nodes
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    // The capacity of the list
    int capacity;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        // If key is not found in hash map, return -1
        if (cache.find(key) == cache.end())
            return -1;
        // Move the (key, value) pair to the beginning of the list
        items.splice(items.begin(), items, cache[key]);
        return cache[key]->second;
    }

    void set(int key, int value) {
        // The key is not in the hash table
        if (cache.find(key) == cache.end()) {
            // If the cache is full then delete the least recently
            // used item, which is at the end of the list
            if (items.size() == capacity) {
                cache.erase(items.back().first);
                items.pop_back();
            }
            items.push_front(make_pair(key, value));
            cache[key] = items.begin();
        } else {
            // Update the value associated with the key
            cache[key]->second = value;
            // Move the (key, value) pair to the beginning of the list
            items.splice(items.begin(), items, cache[key]);
        }
    }
}

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


class LRUCache {
public:
    int size;
    list<int> lru;                              // MRU ... LRU
    unordered_map<int, list<int>::iterator> mp; // key -> iterator
    unordered_map<int, int> kv;                 // key -> value

    LRUCache(int capacity) : size(capacity) {}
    int get(int key) {
        if (kv.count(key) == 0) return -1;
        updateLRU(key);
        return kv[key];
    }
    void put(int key, int value) {
        if (kv.size() == size && kv.count(key) == 0)
            evict();
        updateLRU(key);
        kv[key] = value;
    }
    void updateLRU(int key) {
        if (kv.count(key)) 
            lru.erase(mp[key]);
        lru.push_front(key);
        mp[key] = lru.begin();
    }
    void evict() {
        mp.erase(lru.back());
        kv.erase(lru.back());
        lru.pop_back();
    }
};


class LRUCache {
private:
    int capacity = 0;
    unordered_map<int, pair<int,list<int>::iterator>> mp;
    list<int>li;
    

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (mp.count(key) == 0){
            return -1;
        }
        li.erase(mp[key].second);
        li.emplace_front(key);
        mp[key].second = li.begin();
        return mp[key].first;
    }
    
    void put(int key, int value) {
        if (mp.count(key)){
            get(key);
            mp[key].first = value;
            return;
        }
        if (li.size() == capacity){
            int val = li.back();
            
            li.erase(prev(li.end()));
            mp.erase(val);
        }
        li.emplace_front(key);
        mp[key] = {value, li.begin()};
    }

};
