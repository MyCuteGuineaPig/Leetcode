/*

      Problem	                   Example
left node deleted	             alive[a]==false
right node deleted	             alive[b]==false
nodes no longer adjacent	        R[a] != b


for  sum != 1LL * nums[i] + nums[j]


After a merge, node values change:  nums[i] += nums[j];

So old heap entries may still have: (old sum, i, j)

even though: nums[i] + nums[j] is now different.

Example

Suppose heap contains:

(5, 2, 3)

Later node 2 gets merged with something else:

nums[2] changes

But pair (2,3) may still be adjacent/alive.

alive[2] == true
alive[3] == true
R[2] == 3

BUT:

stored sum != current sum

So the heap order becomes invalid.

You may process a pair too early.






What R[a] = right means

Originally:    R[a] = b

But after deleting b, the node right of a should become right.

so R[a] = right;

changes:

a -> b    into:  a -> right'



Visual Example

Suppose indices are:

0    1    2    3
5 <-> 2 <-> 3 <-> 1

We merge (2,3):

5 <-> 5 <-> 1

Here:

a = node 1
b = node 2
right = node 3

Originally:

R[1] = 2
L[3] = 2

After deleting node 2:

R[1] = 3;
L[3] = 1;

Now linked list becomes:

0 <-> 1 <-> 3



*/



/*

🚨 Concrete example

Start with:

index:  0   1   2   3
nums =  [4,  1,  3,  2]
Step 1: initial pairs

We push:

(4,1) -> sum = 5
(1,3) -> sum = 4   ← chosen first
(3,2) -> sum = 5

Heap order:

(1,3) is picked first
Step 2: merge (1,3)

We merge:

nums = [4, 4, 2]

Now structure:

4 <-> 4 <-> 2

So node values changed:

node 1 becomes 4 (merged)
node 3 is deleted

Step 3: now heap STILL has old entries

Heap still contains stale entries like:

(3,2)  // old sum = 5
(4,1)  // old sum = 5

But now the real adjacent pairs are:

(4,4) = 8
(4,2) = 6

So heap is completely outdated.

Step 4: why your checks are NOT enough

Now suppose we look at heap entry:

(4,1) => i = 0, j = 1

We check:

alive[0] && alive[1] && R[0] == 1

This might still be TRUE → so you accept it.

BUT:

❗ actual reality:

After merging:

nums[4] is no longer 4 or structure changed

So real sum is NOT 5 anymore.

It may now be:

nums[4] + nums[1] = 8 or something else

BUT heap still thinks it's:

5
💥 What goes wrong?

Heap behavior depends on the stored priority.

So this stale entry:

(4,1) with sum = 5

may be popped BEFORE the correct pair:

(4,2) with sum = 6

even though in the REAL current array:

(4,2) should be considered earlier/later differently

👉 So the algorithm makes WRONG greedy decisions.

*/






class Solution {
private: 
    struct Pair {
        long long sum;
        int l, r;

        bool operator>(const Pair& other) const {
            if(sum!=other.sum) return sum > other.sum;
            return l > other.l;
        }
    };

public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        int bad = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        vector<int> alive(n, 1); 
        vector<int> L(n, -1);
        vector<int> R(n, -1);

        for(int i = 0 ; i <n-1; ++i){
            if(nums[i] > nums[i+1]) bad++;
            pq.push(Pair(nums[i] + nums[i+1], i, i + 1));
            L[i+1] = i;
            R[i] = i + 1; 
        }

        if (bad == 0) return 0;

        auto removeEdge = [&](this auto&& removeEdege, int i, int j) {
            if(i != -1 && j != -1 && alive[i] && alive[j]) {
                if(nums[i] > nums[j]) { 
                    --bad;
                }
            }
        };

        auto addEdge = [&](this auto&& addEdge, int i, int j) {
            if(i != -1 && j != -1 && alive[i] && alive[j]) {
                if(nums[i] > nums[j]) ++bad;
                pq.push(Pair(nums[i] + nums[j], i, j));
            }
        };

        int steps = 0;
        while(bad) {
            auto [sum, i, j] = pq.top(); pq.pop();

            if (alive[i] == 0 || alive[j] == 0 || R[i] != j || L[j]!=i || sum != 1LL * nums[i] + nums[j]) 
                continue;

            int left = L[i];
            int right = R[j];

            removeEdge(left, i);
            removeEdge(i, j);
            removeEdge(j, right);

            nums[i] += nums[j];
            alive[j] = false;
            R[i] = right;
            if (right != -1) L[right] = i;

            addEdge(left, i);
            addEdge(i, right);
            
            ++steps;
        }
        return steps;
    }
};