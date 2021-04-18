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