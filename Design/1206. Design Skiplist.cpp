class Skiplist {

struct Node {
    Node* right, *down;
    int val;
    Node(Node* right, Node* down, int val): right(right), down(down), val(val) {}
};

public:
    Node* head = new Node(nullptr, nullptr, 0);
    Skiplist() {
        
    }
    
    bool search(int target) {
        Node* p = head;
        while (p) {
            while(p->right && p->right->val < target) p = p->right;
            if(p->right and p->right->val == target) {
                return true;
            }
            p = p->down;
        }
        return false;
    }
    
    void add(int num) {
        vector<Node*> insertPoints;
        Node* p = head;
        while(p) {
            while(p->right && p->right->val < num) p = p->right;
            insertPoints.push_back(p);
            p = p->down;
        }

        Node* downNode = nullptr;
        bool insertUp = true;
        while(insertUp and not insertPoints.empty()) {
            Node* cur = insertPoints.back();
            insertPoints.pop_back();

            cur->right = new Node(cur->right, downNode, num);
            downNode = cur->right;
            insertUp = (rand() & 1 ) == 0;
        }
        if(insertUp) {
            head = new Node(new Node(nullptr, downNode, num), head, 0);
        }
    }
    
    bool erase(int num) {
        Node* p = head;
        bool seen = false;
        while (p) {
            while(p->right and p->right->val < num) p=p->right;
            if (p->right and p->right->val == num) {
                seen = true;
                p->right = p->right->right;
            }
            p = p->down;
        }
        return seen;
    }
};
