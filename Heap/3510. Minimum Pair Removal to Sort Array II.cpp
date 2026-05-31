
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
        vector<long long> my_nums(nums.begin(), nums.end());

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        vector<int> alive(n, 1); 
        vector<int> L(n, -1);
        vector<int> R(n, -1);

        for(int i = 0 ; i <n-1; ++i){
            if(my_nums[i] > my_nums[i+1]) bad++;
            pq.push(Pair(my_nums[i] + my_nums[i+1], i, i + 1));
            L[i+1] = i;
            R[i] = i + 1; 
        }

        if (bad == 0) return 0;

        auto removeEdge = [&](this auto&& removeEdege, int i, int j) {
            if(i != -1 && j != -1 && alive[i] && alive[j]) {
                if(my_nums[i] > my_nums[j]) { 
                    --bad;
                }
            }
        };

        auto addEdge = [&](this auto&& addEdge, int i, int j) {
            if(i != -1 && j != -1 && alive[i] && alive[j]) {
                if(my_nums[i] > my_nums[j]) ++bad;
                pq.push(Pair((long long)my_nums[i] + (long long)my_nums[j], i, j));
            }
        };

        int steps = 0;
        while(bad) {
            auto [sum, i, j] = pq.top(); pq.pop();

            if (alive[i] == 0 || alive[j] == 0 || R[i] != j || L[j]!=i || sum != 1LL * my_nums[i] + my_nums[j]) 
                continue;

            int left = L[i];
            int right = R[j];

            removeEdge(left, i);
            removeEdge(i, j);
            removeEdge(j, right);

            my_nums[i] += my_nums[j];
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