/*


In the end,n = 1,
the index of winner index is 0 (base-0)

We think with one step back,
when n = 2,
the index of winner is 0 + k,
but we have only n peopple,
so the winner index is (0 + k) % 2 (base-0)

We think with one more step back,
when n = 3,
the index of winner is f(2) + k,
but we have only n peopple,
so the winner index is (f(2) + k) % 3 (base-0)

We think with n more step back,
the index of winner is f(n-1) + k,
but we have only n peopple,
so the winner index is (f(n-1) + k) % n (base-0)

Done.

*/

class Solution {
public:
    int findTheWinner(int n, int k) {
        int a = 0; 
        for(int i = 1; i<=n; ++i){
            a = (a + k) % i;
        }
        return a + 1;
    }
};


class Solution {
public:
    int findTheWinner(int n, int k) {
        int a = 0; 
        for(int i = 1; i<=n; ++i){
            a = (a + k - 1) % i;
            ++a;
        }
        return a;
    }
};


class Solution {
public:
    int findTheWinner(int n, int k) {
        if(n==1)
            return 1;
        return (findTheWinner(n-1,k)+k-1)%n+1;
    }
};


class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> q;
        for(int i=1;i<=n;i++){
            q.push(i);
        }
        while(q.size()!=1){
            int x=k;
            while(x>1){
                int r=q.front();
                q.pop();
                q.push(r);
                x--;
            }
            q.pop();
        }
        return q.front();
    }
};

class Solution {
public:
    int findTheWinner(int n, int k) {
        vector<bool> f(n, true);
        int i = 0, cnt = n;
        while (cnt > 1) {
            for (int j = 0; j < k; ++j, ++i) {
                while(!f[i % n])
                    ++i;
            }
            f[(i - 1) % n] = false;
            --cnt;
        }
        for (i = 0; !f[i]; ++i);
        return i  + 1;
    }
};