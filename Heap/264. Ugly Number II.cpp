/*
264. Ugly Number II

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:  

1 is typically treated as an ugly number.
n does not exceed 1690.

*/



/*

We have an array k of first n ugly number. 
We only know, at the beginning, the first one, which is 1. Then

k[1] = min( k[0]x2, k[0]x3, k[0]x5). The answer is k[0]x2. So we move 2's pointer to 1. 
Then we test:

k[2] = min( k[1]x2, k[0]x3, k[0]x5). And so on. Be careful about the cases such as 6, 
in which we need to forward both pointers of 2 and 3.

x here is multiplication.


I think maybe this way is easier to understand: 
In order to produce a new smallest ugly number, one of (or some of) 2, 3, 5 
needs to multiply a smaller ugly number, and there come the pointers. 
After an ugly number is produced,
 the corresponding pointer(s) needs to move forward. 
 Otherwise it will produce the same ugly number. 
 And the order is retained since each product is larger or equal than before and we extract the minimum every time.

*/
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> uglies(n);
        uglies[0] = 1;
    
        int f2 = 2, f3 = 3, f5 = 5;
        int idx2 = 0, idx3 = 0, idx5 = 0;
    
        for (int i = 1; i < n; ++i) {
            int min_val = min(min(f2, f3), f5);
            uglies[i] = min_val;
    
            if (min_val == f2) {
                f2 = 2 * uglies[++idx2];
            }
            if (min_val == f3) {
                f3 = 3 * uglies[++idx3];
            }
            if (min_val == f5) {
                f5 = 5 * uglies[++idx5];
            }
        }
    
        return uglies[n - 1];
    }
};

/*
1 t2 0 k[t2] 1    t3 0 k[t3] 1    t5 0 k[t5] 1  k[i] 2
2 t2 1 k[t2] 2    t3 0 k[t3] 1    t5 0 k[t5] 1  k[i] 3
3 t2 1 k[t2] 2    t3 1 k[t3] 2    t5 0 k[t5] 1  k[i] 4
4 t2 2 k[t2] 3    t3 1 k[t3] 2    t5 0 k[t5] 1  k[i] 5
5 t2 2 k[t2] 3    t3 1 k[t3] 2    t5 1 k[t5] 2  k[i] 6
6 t2 3 k[t2] 4    t3 2 k[t3] 3    t5 1 k[t5] 2  k[i] 8
7 t2 4 k[t2] 5    t3 2 k[t3] 3    t5 1 k[t5] 2  k[i] 9
8 t2 4 k[t2] 5    t3 3 k[t3] 4    t5 1 k[t5] 2  k[i] 10
9 t2 5 k[t2] 6    t3 3 k[t3] 4    t5 2 k[t5] 3  k[i] 12

*/

class Solution {
public:
    int nthUglyNumber(int n) {
        if(n <= 0) return false; // get rid of corner cases 
        if(n == 1) return true; // base case
        int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5 //t2, t3, t5代表用了几回2，3，5
        /*比如已经用了3回，那么下一个用3个，至少是dp[3]*3
        上一个最小的是在 dp[t3-1]*3，dp[t3]肯定比3大，所以下一个用3的最小的肯定是dp[t3]*3

        比如现在p3 = i, 上一个乘以3的pt是i-1, dp[i-1]是dp[i]的下一个最小的ungly number，
        所以可以正好整除3的解, 肯定是由dp[i]*3 获得的
        */
        vector<int> k(n);
        k[0] = 1;
        for(int i  = 1; i < n ; i ++)
        {
            cout<<i<<" t2 "<<t2<<" k[t2] "<<k[t2]<<"    t3 "<<t3<<" k[t3] "<<k[t3]<<"    t5 "<<t5<<" k[t5] "<<k[t5];
            k[i] = min(k[t2]*2,min(k[t3]*3,k[t5]*5));
            if(k[i] == k[t2]*2) t2++; 
            if(k[i] == k[t3]*3) t3++;
            if(k[i] == k[t5]*5) t5++;
            cout<<"  k[i] "<<k[i]<<endl;
        }
        return k[n-1];
    }
};



/*
static dp
*/
class Solution {
public:
    int nthUglyNumber(int n) {
        static vector<int> nums{1};
        static int i2 = 0;
        static int i3 = 0;
        static int i5 = 0;
        while (nums.size() < n) {
            const int next2 = nums[i2] * 2;
            const int next3 = nums[i3] *3;
            const int next5 = nums[i5] * 5;
            const int next = min(next2, min(next3, next5));
            if (next == next2) ++i2;
            if (next == next3) ++i3;
            if (next == next5) ++i5;
            nums.push_back(next);
        }
        return nums[n-1];
    }
};



// Time:  O(n)
// Space: O(1)
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long long, vector<long long>, greater<long long>>pq;//越大越往后
        pq.push(1);
        long long ungly_number = 1;
        for(int i = 0; i<n; i++){
            ungly_number = pq.top();
            pq.pop();
            if(ungly_number %2 == 0){
                pq.push(ungly_number*2);
            }else if(ungly_number %3 == 0){//只能除以3，就乘以2和3
                pq.push(ungly_number*2);
                pq.push(ungly_number*3);
            }else{//只能除以1，5，就乘以2，3，5 比如25，不乘以2，50不会到的， 不乘以3，75也不会到
                pq.push(ungly_number*2);
                pq.push(ungly_number*3);
                pq.push(ungly_number*5);
            }
        }
        return ungly_number;
    }
};


/*
注：上面的解不可以写成


           if(ungly_number %2 == 0 || ungly_number %3 == 0 || ungly_number %5 == 0){
                pq.push(ungly_number*2);
            }if(ungly_number %3 == 0 ||ungly_number %5 == 0){
                pq.push(ungly_number*3);
            } if(ungly_number %5 == 0){
                pq.push(ungly_number*5);
            }

这样比如  18,  3*2*3 可以, 3*3*2 都等于 18, 会被push 

*/



class Solution { //这个解会慢很多，上面priority queue的解每次push进的数都是unqiue的，这个会push进很多一样数的
public:
    int nthUglyNumber(int n) {
        priority_queue<long long, vector<long long>, greater<long long>>pq;
        pq.push(1);
        long long ungly_number = 1;
        for(int i = 0; i<n; i++){
            ungly_number = pq.top();
            while(!pq.empty() && pq.top() == ungly_number) pq.pop();
            pq.push(ungly_number*2);
            pq.push(ungly_number*3);
            pq.push(ungly_number*5);
        }
        return ungly_number;
    }
};

// BST solution.
class Solution3 {
public:
    int nthUglyNumber(int n) {
        long long ugly_number = 0;
        set<long long> bst;
        
        bst.emplace(1);
        for (int i = 0; i < n; ++i) {
            ugly_number = *bst.cbegin();
            bst.erase(bst.cbegin());
            if (ugly_number % 2 == 0) {
                bst.emplace(ugly_number * 2);
            } else if (ugly_number % 3 == 0) {
                bst.emplace(ugly_number * 2);
                bst.emplace(ugly_number * 3);
            } else {
                bst.emplace(ugly_number * 2);
                bst.emplace(ugly_number * 3);
                bst.emplace(ugly_number * 5);
            }
        }
        return ugly_number;   
    }
};
