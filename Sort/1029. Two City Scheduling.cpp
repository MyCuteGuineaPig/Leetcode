    /*
        greedy的思想，这里是根据到AB城市的距离来进行排序，如果到B的距离远远大于A，那么得到的差值越小
        排序就越在前面，越应该选择到A点而不是去B
    */

/*

Why simple sort work?

assume two people person1, cost = [a, a+a'],   person2 cost = [b,b+b']

choice  1->A & 2->B   VS   1->B & 2->A
cost    a + a + b'    VS   a + b + a'

only b' and a' affect the result 

If there are more than 2 persons, we could think it by divid and conquer idea and 
    finally there are only 2 "peoples" left in that array.


 */

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        sort(costs.begin(),costs.end(),[](vector<int>&a, vector<int>&b){return abs(a[0]-a[1]) > abs(b[0]-b[1]);});
        
        int res = 0;
        for(int i = 0, n1 = costs.size()/2, n2 = costs.size()/2; i<costs.size(); ++i){
            if(n1 && costs[i][0] < costs[i][1] || n2 <= 0){
                res += costs[i][0];
                n1 -- ;
            }else {
                res += costs[i][1];
                n2--;
            }
        }
        
        return res;
    }
};

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& cs, int res = 0) {
        sort(begin(cs), end(cs), [](vector<int> &v1, vector<int> &v2) {
            return (v1[0] - v1[1] < v2[0] - v2[1]);
        });
        for (auto i = 0; i < cs.size() / 2; ++i) {
            res += cs[i][0] + cs[i + cs.size() / 2][1];
        }
        return res;
    }
};

//O(N) on average
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& cs, int res = 0) {
        nth_element(begin(cs), begin(cs) + cs.size() / 2, end(cs), [](vector<int> &a, vector<int> &b) {
            return (a[0] - a[1] < b[0] - b[1]);
        });
        for (auto i = 0; i < cs.size() / 2; ++i) {
            res += cs[i][0] + cs[i + cs.size() / 2][1];
        }
        return res;
    }
};


//DP O(n^2)
/*

for (i+j)th people, he/she can be assigned either to A city or B city,
the min cost if he is assigned to A city: dp[i-1][j]+costs[i+j-1][0]; //because it is to A, so we should use i-1
the min cost if he is assigned to B city: dp[i][j-1]+costs[i+j-1][1]; //because it is to B, so we should use j-1
so dp[i][j] = Math.min(dp[i-1][j]+costs[i+j-1][0] , dp[i][j-1]+costs[i+j-1][1]);

another way to represent the dp equation is: dp[totalPerson][personToA], toatalPerson is the number of people have been assigned, and personToA of them are assigned to city A, so the the equation:
dp[totalPerson][personToA]= Math.min(dp[totalPerson-1][personToA]+costs[totalPerson-1][1], //the last one to B
dp[totalPerson-1][personToA-1]+costs[totalPerson-1][0]);//the last one to A
 */
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int N = costs.size() / 2;
        vector<vector<int>>dp(N+1, vector<int>(N+1));
        for (int i = 1; i <= N; i++) {
            dp[i][0] = dp[i - 1][0] + costs[i - 1][0];
        }
        for (int j = 1; j <= N; j++) {
            dp[0][j] = dp[0][j - 1] + costs[j - 1][1];
        }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dp[i][j] = min(dp[i - 1][j] + costs[i + j - 1][0], dp[i][j - 1] + costs[i + j - 1][1]);
            }
        }
        return dp[N][N];
    }
};