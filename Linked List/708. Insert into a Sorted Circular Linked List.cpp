
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (!head) {
            head = new Node(insertVal, nullptr);
            head->next = head;
            return head;
        }

        Node* prev = head;
        Node* next = head->next;
        bool inserted = false;
        while (true) {
            // insert when:
            // 1. prev <= insertVal <= next
            // 2. insertVal < min (insert at the tail)
            // 3. insertVal > max (insert at the tail)
            if ((prev->val <= insertVal && insertVal <= next->val) ||
                (prev->val > next->val && insertVal < next->val) ||
                (prev->val > next->val && insertVal > prev->val)) {
                prev->next = new Node(insertVal, next);
                inserted = true;
                break;
            }

            prev = prev->next;
            next = next->next;
            if (prev == head) break;
        }
        
        if (!inserted) {
            // The only reason why `value` was not inserted is that
            // all values in the list are the same and are not equal to `value`.
            // So, we could insert `value` anywhere.
            prev->next = new Node(insertVal, next);
        }

        return head;
    }
};