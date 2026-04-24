
class MyLinkedList {
struct ListNode{
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    int val = 0;
    ListNode (int val,  ListNode* prev = nullptr,  ListNode* next = nullptr): val(val), prev(prev), next(next) {}
};

ListNode* head;
ListNode* tail;
int size = 0;

public:
    MyLinkedList() {
        head = new ListNode(0);
        tail = new ListNode(0);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    ~MyLinkedList() {
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    ListNode* getNode(int index) {
        if (index < 0 || index >= size) return nullptr;
        ListNode* tmp;
        
        // Optimization: find if index is closer to head or tail
        if (index < size / 2) {
            tmp = head;
            for (int i = 0; i < index + 1; ++i) tmp = tmp->next;
        } else {
            tmp = tail;
            for (int i = 0; i < size - index; ++i) tmp = tmp->prev;
        }
        return tmp;
    }

    
    int get(int index) {
        /*
        cout<<" get "<<index<<" size "<<size<<endl;
        ListNode* prev = head;
        while (prev) {
            cout << "[while] "<< prev->val <<endl;
            prev = prev->next;
        }
        */
        ListNode* res = getNode(index);
        return res? res->val: -1;
    }
    
    void addAtHead(int val) {
        ListNode* first = head, *next = first->next;
        
        ++size;
        ListNode* cur = new ListNode(val,first, next);
        first->next = cur;
        next->prev = cur;
    }
    
    void addAtTail(int val) {
        ListNode* last = tail, *prev = tail->prev;

        ++size;
        ListNode* cur = new ListNode(val, prev, last);
        prev->next = cur;
        last->prev = cur;
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index > size) return; // <--- 注： index == size 是合法的，表示在tail之前添加一个节点
        
        ListNode *prev,  *next;
        if(index  < size - index ) {
            prev = head;
            for(int i = 0 ; i < index; ++i) { // <--- 注意这里是 < index, 因为 prev 是在 index 之前的节点
                prev = prev->next;
            }
            /* or 
            next = head;
            for(int i = 0 ; i < index + 1; ++i) {
                next = next->next;
            }
            prev = next->prev;
            */
            next = prev->next;
        } else {
            next = tail;
            for(int i = 0; i<size - index ; ++ i) {
                next = next->prev;
            }
            prev = next->prev;
        }
        ++size;
        ListNode* cur = new ListNode(val, prev, next);
        prev->next = cur;
        next->prev = cur;   
        //cout<<" size "<<size<<endl;
        prev = head;
    }
    
    void deleteAtIndex(int index) {
        ListNode* res = getNode(index);
        if(!res) return;

        --size;
        ListNode* prev =res->prev;
        ListNode* next = res->next;
        prev->next = next;
        next->prev = prev;
        delete res;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */


class MyLinkedList {
private:
struct ListNode {
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
};

    int size;
    // Sentinel nodes as pseudo-head and pseudo-tail
    ListNode *head, *tail;

public:
    MyLinkedList() {
        size = 0;
        head = new ListNode(0);
        tail = new ListNode(0);
        head->next = tail;
        tail->prev = head;
    }

    // Destructor to clean up memory
    ~MyLinkedList() {
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    /** Get the value of the index-th node. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0 || index >= size) return -1;

        ListNode* curr;
        // Choose the fastest way: move from head or move from tail
        if (index + 1 < size - index) {
            curr = head;
            for (int i = 0; i < index + 1; ++i) curr = curr->next;
        } else {
            curr = tail;
            for (int i = 0; i < size - index; ++i) curr = curr->prev;
        }

        return curr->val;
    }

    /** Add a node of value val before the first element. */
    void addAtHead(int val) {
        ListNode *pred = head, *succ = head->next;

        size++;
        ListNode* toAdd = new ListNode(val);
        toAdd->prev = pred;
        toAdd->next = succ;
        pred->next = toAdd;
        succ->prev = toAdd;
    }

    /** Append a node of value val to the last element. */
    void addAtTail(int val) {
        ListNode *succ = tail, *pred = tail->prev;

        size++;
        ListNode* toAdd = new ListNode(val);
        toAdd->prev = pred;
        toAdd->next = succ;
        pred->next = toAdd;
        succ->prev = toAdd;
    }

    /** Add a node of value val before the index-th node. */
    void addAtIndex(int index, int val) {
        if (index > size) return;
        if (index < 0) index = 0;

        ListNode *pred, *succ;
        if (index < size - index) {
            pred = head;
            for (int i = 0; i < index; ++i) pred = pred->next;
            succ = pred->next;
        } else {
            succ = tail;
            for (int i = 0; i < size - index; ++i) succ = succ->prev;
            pred = succ->prev;
        }

        size++;
        ListNode* toAdd = new ListNode(val);
        toAdd->prev = pred;
        toAdd->next = succ;
        pred->next = toAdd;
        succ->prev = toAdd;
    }

    /** Delete the index-th node in the linked list, if valid. */
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;

        ListNode *pred, *succ;
        if (index < size - index) {
            pred = head;
            for (int i = 0; i < index; ++i) pred = pred->next;
            succ = pred->next->next;
        } else {
            succ = tail;
            for (int i = 0; i < size - index - 1; ++i) succ = succ->prev;
            pred = succ->prev->prev;
        }

        // Pointer to the node being removed so we can delete it
        ListNode* toDelete = pred->next;
        size--;
        pred->next = succ;
        succ->prev = pred;
        
        delete toDelete; // Manual memory management
    }
};




