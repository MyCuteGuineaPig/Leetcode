class Solution {
public:
    int fillCups(vector<int>& amount) {
        priority_queue<int>q;
        int step = 0;
        for(auto i: amount){
            if (i != 0)
                q.push(i);
        }
        while (q.size()){
            int cur = q.top(); q.pop();
            int next = 0;
            if (!q.empty())
            {
                next = q.top();
                q.pop();
            }
            if (next == 0){
                step += cur;
                break;
            }
            else {
                ++step;
                if (--cur > 0) q.push(cur);
                if (--next > 0) q.push(next);
            }
        }
        return step;
    }
};


/*

Explanation
It's a brain-teaser.

Necessary conditions (lower bound)

res >= max(A)
Because each time,
one type can reduce at most 1 cup,
so the final result is bigger or equal to max(A)

res >= ceil(sum(A) / 2)
Because each time,
we can fill up to 2 cups,
so the final result is bigger or equal to ceil(sum(A) / 2)

Sufficient considtion (realizeable)
One strategy is to greedily fill up 2 cups with different types of water.
Each step, we pick the 2 types with the most number of cups, until there is only one kind.

Conclusion
The lower bound is realizable,
so it's proved as the minimum steps.
*/

class Solution {
public:
    int fillCups(vector<int>& A) {
        int mx = 0, sum = 0;
        for(int& a: A) {
            mx = max(a, mx);
            sum += a;
        }
        return max(mx, (sum + 1) / 2);
    }

};

class Solution {
public:
    int fillCups(vector<int>& amount) {
      sort(amount.begin(),amount.end()); 
      int x=amount[0];
      int y=amount[1];
      int z=amount[2];
      int sum=x+y+z;
      if(x+y>z) return sum/2+sum%2;
      if(x==0 && y==0) return z;
      else return z;
    }
};


class Solution {
public:
    int fillCups(vector<int>& a) {
        int res = 0;
        for (; max({a[0], a[1], a[2]}) > 0; ++res) {
            sort(begin(a), end(a));
            --a[2];
            --a[1];
        }
        return res;
    }
};


class Solution {
public:
    int fillCups(vector<int> &amount) {
        sort(amount.begin(), amount.end(), greater<>());
        if (!amount[0]) return 0;
        if (amount[1]) {
            amount[0]--, amount[1]--;
            return 1 + fillCups(amount);
        } else return amount[0];
    }
};