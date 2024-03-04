class MyHashMap {
    vector<list<pair<int,int>>> m_data;
    size_t m_size = 10000;
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        m_data.resize(m_size);
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        auto &list = m_data[key % m_size];
        for (auto & val : list) {
            if (val.first == key) {
                val.second = value;
                return;
            }
        }
        list.emplace_back(key, value);
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        const auto &list = m_data[key % m_size];
        for (const auto & val : list) {
            if (val.first == key) {
                return val.second;
            }
        }
        return -1;
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        auto &list = m_data[key % m_size];
        list.remove_if([key](auto n) { return n.first == key; });
    }
};



struct Node {
public:
    int key, val;
    Node* next;
    Node(int k, int v, Node* n) {
        key = k;
        val = v;
        next = n;
    }
};
class MyHashMap {
public:
    const static int size = 19997;
    const static int mult = 12582917;
    Node* data[size];
    int hash(int key) {
        return (int)((long)key * mult % size);
    }
    void put(int key, int val) {
        remove(key);
        int h = hash(key);
        Node* node = new Node(key, val, data[h]);
        data[h] = node;
    }    
    int get(int key) {
        int h = hash(key);
        Node* node = data[h];
        for (; node != NULL; node = node->next)
            if (node->key == key) return node->val;
        return -1;
    }    
    void remove(int key) {
        int h = hash(key);
        Node* node = data[h];
        if (node == NULL) return;
        if (node->key == key) data[h] = node->next;
        else for (; node->next != NULL; node = node->next)
            if (node->next->key == key) {
                node->next = node->next->next;
                return;
            }
    }
};



class MyHashMap {
public:
    vector<list<pair<int,int>>>hashMap;
    int num_element = 0;
    MyHashMap() {
        hashMap.resize(16);
    }
    
    void put(int key, int value) {
        if((double) num_element/hashMap.size() > 0.5) grow();
        auto &list = hashMap[key % hashMap.size()];
        ++num_element;
        for(auto &it: list){
            if(it.first == key){
                it.second = value;
                return;
            }
        }
        list.emplace_back(key, value);
    }
    
    int get(int key) {
        auto& list = hashMap[key % hashMap.size()];
        for(auto& it: list){
            if(it.first == key){
                return it.second;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        auto& list = hashMap[key % hashMap.size()];
        list.remove_if([&](const pair<int,int>& p){
            if(p.first == key){
                --num_element;
                return true;
            }
            return false;
        });
    }

    void grow(){
        num_element = 0;
        vector<list<pair<int,int>>> vec2(hashMap.size());
        vec2.swap(hashMap);
        hashMap.resize(hashMap.size() * 2);
        for(auto& list: vec2){
            for(auto & it: list){
                put(it.first, it.second);
            }
        }

    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

class MyHashMap {
public:
    vector<list<pair<int, int>>> v;
    int numElements;
    /** Initialize your data structure here. */
    MyHashMap() {
        numElements = 0;
        v.resize(20);
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        //if load factor > 0.5
        if((double)(numElements / v.size()) > 0.5) grow();
        auto &list = v[key % v.size()];
        auto it = list.begin();
        while(it != list.end()){
            if(it->first == key) it->second = value;
            ++it;
        }
        
        if(it == list.end()){
            list.push_back(make_pair(key, value));
            ++numElements;
        }
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        auto &list = v[key % v.size()];
        auto it = find_if(list.begin(), list.end(), [key](auto x){
           return x.first == key; 
        });
        return (it == list.end()) ? -1 : it->second;
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        auto &list = v[key%v.size()];
        list.remove_if([key, this](auto x) { 
            if(x.first == key){
                --numElements;
                return true;
            }
            return false; 
        });
    }
    
    void grow(){
        vector<list<pair<int, int>>> v2;
        v2.resize(v.size());
        v.swap(v2);
        v.resize(v.size() * 2);
        numElements = 0;
        for(auto l : v2){
            auto it = l.begin();
            while(it != l.end()){
                put(it->first, it->second);
                ++it;
            }
        }
    }
    
};