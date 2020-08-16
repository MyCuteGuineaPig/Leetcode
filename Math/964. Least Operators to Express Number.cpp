/*

- double l: log x to target.
- int a: the integer which is floor(l), then x^a < target < x^(a + 1)
- leastOpsExpressTarget(x, target) = f(x, target) = min(a + f(x, target - x^a), a + 1 + f(x, x^(a + 1) - target))
- Tricky: if x^(a+1) >= target * 2, no need to calculate it since the result is always greater than a + f(x, target - x^a).


 */

class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        unordered_map<int,int>dp;
        return helper(dp, x, target);
    }
    
    int helper(unordered_map<int,int>&dp, int x, int target){
        if(x == target) 
            return 0;
        if(target < x)
            return min(2*target -1, (x-target)*2); 
            /*  比如x = 5, target = 3, 
                2*target -1:  5/5 + 5/4 + 5/5  
                (x-target)*2:  5 - 5/5 - 5/5 
            */
        if(dp.count(target))
            return dp[target];
        double l = log(target)/log(x);
        if(l - (int)l < 0.00001)
            dp[target] = (int)l-1;
        else{
            int a = (int)l;
            dp[target] = a + helper(dp, x, target - pow(x, a));
            if(target * 2 > pow(x, a+1))
                dp[target] = min(dp[target], a+1+helper(dp, x, pow(x,a+1)-target));
        }
        return dp[target];
    }
};




class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
		// At this time, you can get target either by add target times x/x or subtract (x - target) times x/x to x
		// For example, x = 3, target = 2. Then, 3/3 + 3/3 or 3 - 3/3 is possible result
        if (x > target) {
            return min(target * 2 - 1, (x - target) * 2);
        }
        if (x == target) {  // just push x at the end
            return 0;
        }
        
        long long sums = x;
        int times = 0;
        while (sums < target) {  // this is gready, put as much as possible 'x'
            times++;
            sums *= x;
        }
        
        if (sums == target) {  // one more 'x' you put, one more operator
            return times;
        }
        
		// when you have remainder, you have two choices, one is add, the other is subtract
		// for example, x = 3, target = 5. Then, 5 = 3 + 2 or 5 = 9 - 4
        int l = INT_MAX, r = INT_MAX;
        if (sums - target < target) {
            l = leastOpsExpressTarget(x, sums - target) + times;  // using subtract
        }
        r = leastOpsExpressTarget(x, target - (sums / x)) + (times - 1);  // using add
        return min(l, r) + 1;  // No matter +/- used, one more operator is add
    }
};



//Dijkstra
class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        static auto branch = {0, 1};
        set<pair<int, int>> q;
        unordered_set<int> vi;
        q.emplace(0, target);
        while (q.size()) {
            pair<int, int> cur = *q.begin();
            q.erase(q.begin());
            if (vi.count(cur.second)) continue;
            vi.emplace(cur.second);
            if (cur.second == 0) return cur.first - 1;
            int v = log(cur.second) / log(x);
            for (int i : branch) {
                int n = abs(pow(x, v + i) - cur.second);
                if (vi.count(n)) continue;
                q.emplace(cur.first + (v + i == 0 ? 2 : v + i), n);
            }
        }
        __builtin_unreachable();
    }
};




/*
pos the number of operations needed to get y % (x ^ (k+1))
neg the number of operations needed to get x ^ (k + 1) - y % (x ^ (k + 1))

 */


/*

when k = 0:
   only two ways you can get the result. Add cur times x/x or add (cur - x) times x/x to x.
   for example, x = 3, cur = 2. 
   2 = 3/3 + 3/3 or 2 = 3 - 3/3.
when k != 0:
   assume origin target is called y, at every iteration yk and curk got. Then when k = 1.
   y = (y1*x + cur1)*x + cur0
   At time k = 0, we get:
       cur0 = + x/x + ... + x/x               (cur0 * 2 operators)
       cur0 = x - x/x - ... - x/x            ((x - cur0) * 2 operators)
   for same reason, cur1 also have this two statuations.

   cur1 is positive:
      y = (y1 * x + x/x + ... + x/x) * x + x/x + ... + x/x             // cur * k + pos
      y = (y1 * x + x/x + ... + x/x) * x + x - x/x - ... - x/x
        = (y1 * x + x/x + ... + x/x + x/x) * x - x/x - ... - x/x     // (cur + 1) * k + neg

      y = (y1 * x + x - x/x - ... - x/x - x/x) * x + x/x + ... + x/x             // (x - cur) * k + pos
      y = (y1 * x + x - x/x - ... - x/x - x/x) * x + x - x/x - ... - x/x
        = (y1 * x + x - x/x - ... - x/x) * x - x/x - ... - x/x     // (x - cur - 1) * k + neg

比如 x = 3, y = 19
19 = 3 *6 + 1   // y0 = 6, cur0 = 1, k = 0
   = 3 *(2*3 + 0) + 1 // y1 = 2, cur1 = 0,  k = 1
        =  3*(2*3 + 1) - 2
   = 3*(3*(0 + 2)) + 1 // y2 = 0, cur2 = 2, k = 2
        = 3*(3*(1*3-1) +1) - 2

cur0 = 1, y0 = 6
      pos = cur0 * 2 = 2,                 =>        3/3  = 1
      neg = (x - cur) * 2 =  (3-1)*2 = 4  =>        3 - 3/3 - 3/3  = 1


think about this example: 
14 = 3*3 + 3 + 2
   = 3*(4) + 2         // y0 = 4, cur0 = 2, k = 0
   = 3*(3*1 + 1) + 2       // y1 = 1, cur1 = 1, k = 1
   = 3*[3*(0 + 1) + 1] + 2  // y2 = 0, cur2 = 1, k = 2

when k = 1, what we should care is: 14 = 3*(3*1 + 【1) + 1 + 1】
ie. 3 * (1) + (2), things in () can be get by add or subtract
3 * (1) + (2) = 3 * (1) + (1 + 1)   // cur1 * k + pos
              = 3 * (1) + (3 - 1) = 3*(2) - 1      // (cur1 + 1) * k + neg
			  = 3 * (3 - 1 - 1) + (1 + 1) = 3*3 +【3*(-1-1) + 1 + 1】     // (x - cur1) * k + pos
			  // forget the first 3*3, it will be dealt at next time
			  = 3 * (3 - 1 - 1) + (3 - 1) = 3*3 +【3*(-1) + (3 -1)】  // [x - (cur1 + 1)] * k + neg

 */

class Solution {
public:
    int leastOpsExpressTarget(int x, int y) {
        int pos = 0, neg = 0, k, pos2, neg2, cur;
        for (k = 0; y > 0; ++k, y /= x) {
            cur = y % x;
            if (k > 0) {
                pos2 = min(cur * k + pos, (cur + 1) * k + neg);
                neg2 = min((x - cur) * k + pos, (x - cur - 1) * k + neg);
                pos = pos2, neg = neg2;
            } else {
                pos = cur * 2;
                neg = (x - cur) * 2;
            }
        }
        return min(pos, k + neg) - 1;
    }
};