class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
    }
    
    int get(int key) {
        if(m.count(key) == 0)
            return -1;
        auto &v = m[key];
        freq[v.second++].erase(mIter[key]);
        
        if(freq[minFreq].empty())
            ++minFreq;
        
        freq[v.second].push_front(key);
        mIter[key] = freq[v.second].begin();
        return v.first;
    }
    
    void put(int key, int value) {
       if(capacity <= 0) return;
        
       if(m.count(key)!=0){
           get(key);
           m[key].first = value;
       }
       else{
           if(capacity == size){
               int last = freq[minFreq].back();
               freq[minFreq].pop_back();
               mIter.erase(last);
               m.erase(last);
               --size;
            }
            
            minFreq = 1;
            m[key] = {value, 1};
            freq[1].push_front(key);
            mIter[key] = freq[1].begin();
            ++size;
        }
    }


class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (key_val_pair.count(key) == 0){
            return -1;
        }
        int& key_freq = key_val_pair[key].second;

        freq[key_freq].erase(mIter[key]);
        if (freq[key_freq].size() == 0 && min_freq == key_freq){
            min_freq += 1;
        }

        key_freq += 1;
        freq[key_freq].push_front(key);
        mIter[key] = freq[key_freq].begin();
        return key_val_pair[key].first;
    }
    
    void put(int key, int value) {
        if (capacity <= 0 ) 
            return;

        if(key_val_pair.count(key)) {
            get(key);
            key_val_pair[key].first = value;
        } else {
            if (size == capacity){
                int last = freq[min_freq].back();
                
                int key_freq = key_val_pair[last].second;
                freq[key_freq].erase(mIter[last]);
                mIter.erase(last);
                key_val_pair.erase(last);
                --size;
            } 
            ++size;
            key_val_pair[key] = {value, 1};
            freq[1].push_front(key);
            mIter[key] = freq[1].begin();
            min_freq =  1;
        }
    }
private:
    int size = 0;
    int capacity = 0;
    int min_freq = 0;
    unordered_map<int, pair<int, int>> key_val_pair;
    unordered_map<int,list<int>> freq;
    unordered_map<int, list<int>::iterator> mIter;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */