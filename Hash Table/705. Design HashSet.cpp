class MyHashSet {
public:
    vector<list<int>>hashset;
    size_t num_element; 
    MyHashSet() {
        hashset.resize(16);
    }
    
    void add(int key) {
        if((double) num_element / hashset.size() > 0.5) grow();
        auto& list = hashset[key % hashset.size()];
        ++num_element;
        for(auto & it: list){
            if(it == key)
                return;
        }
        list.emplace_back(key);
    }
    
    void remove(int key) {
        auto& list = hashset[key % hashset.size()];
        list.remove_if([&](auto it){
            if(it == key){
                --num_element;
                return true;
            }
            return false;
        });
    }
    
    bool contains(int key) {
        auto & list = hashset[key % hashset.size()];
        auto it = find(list.begin(), list.end(), key);
        return it != list.end();
    }

    void grow(){
        vector<list<int>> vec2 (hashset.size());
        vec2.swap(hashset);
        num_element = 0;
        hashset.resize(hashset.size() * 2);
        for(auto& li : vec2){
            for(auto& val: li)
                add(val);
        }
    }
};


//Approach 1: Basic Implementation
class MyHashSet {
private:
	int prime;
	vector<list<int>> table;

	int hash(int key) {
		return key % prime;
	}

	list<int>::iterator search(int key) {
		int h = hash(key);
		return find(table[h].begin(), table[h].end(), key);
	}

public:
	MyHashSet() : prime(10007), table(prime) {}
	
	void add(int key) {
		int h = hash(key);
		if (!contains(key))
			table[h].push_back(key);
	}
	
	void remove(int key) {
		int h = hash(key);
		auto it = search(key);
		if (it != table[h].end())
			table[h].erase(it);
	}
	
	bool contains(int key) {
		int h = hash(key);
		return search(key) != table[h].end();
	}
};



//Approach 2: Table-Doubling
class MyHashSet {
private:
	int m_size, capacity;
	double load_factor;
	vector<list<int>> table;

	int hash(int key) {
		return key % capacity;
	}

	list<int>::iterator search(int key) {
		int h = hash(key);
		return find(table[h].begin(), table[h].end(), key);
	}

	void rehash() {
	    m_size = 0;
		capacity = max(2, capacity);
		vector<list<int>> old_table(move(table));
		table = vector<list<int>>(capacity);
		
		for (list<int>& chain: old_table)
			for (int& key: chain)
				add(key);
	}

public:
	MyHashSet() : m_size(0), capacity(2), load_factor(0.75), table(capacity) {}
	
	void add(int key) {
		if (contains(key))
			return;
		
		m_size++;
		int h = hash(key);
		table[h].push_back(key);
		
		if (m_size >= load_factor * capacity) {
			capacity *= 2;
			rehash();
		}
	}
	
	void remove(int key) {
		int h = hash(key);
		auto it = search(key);
		
		if (it == table[h].end())
			return;
		
		m_size--;
		table[h].erase(it);
		
		if (m_size <= 0.5 * load_factor * capacity) {
			capacity /= 2;
			rehash();
		}
	}
	
	bool contains(int key) {
		int h = hash(key);
		return search(key) != table[h].end();
	}
};