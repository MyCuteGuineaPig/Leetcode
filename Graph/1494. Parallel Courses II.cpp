class Solution {
public:
    int minCourse(int bitMap, unordered_map<int, unordered_set<int>>& graph, unordered_map<int, int>&dp, int n, int k){
        if(bitMap == (1<<n) - 1){
            return 0;
        }
        if (dp.count(bitMap)){
            return dp[bitMap];
        }
        int zeroIndegree = 0;
        for(int i = 0; i<n; ++i){
            if(bitMap & (1<<i)){
                continue;
            }
            bool takeAllPreCourses = true;
            for(auto & prev: graph[i]){
                if ( (bitMap & (1<<prev)) == 0){
                    takeAllPreCourses = false;
                    break;
                }
            }
            if (takeAllPreCourses) 
                zeroIndegree |= (1<<i);
        }
        if (__builtin_popcount(zeroIndegree) <= k){
            return 1 + minCourse(bitMap | zeroIndegree, graph, dp, n, k);
        }
        int min_semster = n + 1;
        for(int subset = zeroIndegree & (zeroIndegree-1); subset; subset = (subset-1) & zeroIndegree){
            if (__builtin_popcount(subset) != k)
                continue;
            
            min_semster = min(min_semster,  1 + minCourse(bitMap | subset, graph, dp, n, k));
            
        }
        return dp[bitMap] = min_semster;
    }


    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        unordered_map<int, unordered_set<int>>graph;
        for(auto & e: relations){
            graph[e[1]-1].insert(e[0]-1);
        }
        unordered_map<int, int>dp;
        return minCourse(0, graph, dp, n, k);
    }
};

class Solution 
{
    std::vector<std::vector<int>> list;
    std::vector<int> solutions;
    int n;
    int k;

    int minCourses(int bitMap)
    {
        if (bitMap == (1 << n) - 1)
        {
            return 0;
        }

        if (solutions[bitMap] >= 0)
        {
            return solutions[bitMap];
        }

        int zeroDegrees = 0;

        for (int i = 0; i < n; ++i)
        {
            if (bitMap & (1 << i))//don't want to take the same course twice
            {
                continue;
            }

            bool indicator = true;

            for (const int& prev : list[i])
            {
                if (!(bitMap & (1 << prev))) //有先课还没有上，不考虑i, 
                {
                    indicator = false;
                    break;
                }
            }

            if (indicator) //所有的提前课都上完了
            {
                zeroDegrees |= 1 << i;
            }
        }

        if (__builtin_popcount(zeroDegrees) <= k)
        {
            return solutions[bitMap] = minCourses(bitMap | zeroDegrees) + 1;
        }

        int min = n + 1;

        for (int newMap = (zeroDegrees - 1) & zeroDegrees; newMap; newMap = (newMap - 1) & zeroDegrees)
        {   
            //get all combination of the zeroDegrees
            if (__builtin_popcount(newMap) != k)
            {
                continue;
            }

            min = std::min(min, minCourses(bitMap | newMap) + 1);
        }

        return solutions[bitMap] = min;
    }

public:

    int minNumberOfSemesters(int n, std::vector<std::vector<int>>& relations, int k)
    {
        this->n = n;
        this->k = k;

        // Adjacency list
        list.resize(n);

        for (const std::vector<int>& edge : relations)
        {
            list[edge[1] - 1].push_back(edge[0] - 1);
        }

        solutions.assign(1 << n, -1);

        return minCourses(0);
    }
};

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        // dependency[i]: dependency mask of course i, the set bits is dependent
        vector<int> dependency(n, 0);
        for (size_t i = 0; i < dependencies.size(); ++i) {
            int course = dependencies[i][1] - 1;
            int prerequisite = dependencies[i][0] - 1;
            dependency[course] |= 1 << prerequisite;
        }

        // prerequisites[i]: prerequisites mask of mask i, the set bits is prerequisites
        vector<int> prerequisites(1 << n, 0);
        // iterate all mask and generate prerequisites mask of each mask
        for (int i = 0; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    prerequisites[i] |= dependency[j];
                }
            }
        }

        // dp[i]: minimum number of semesters of mask i, the set bits are courses that have not been taken
        vector<int> dp(1 << n, n + 1);
        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i) { //表示这一天可以上完i
            // iterate all submask of mask i, and this mask is the mask of last semester
            // see: https://cp-algorithms.com/algebra/all-submasks.html
            for (int j = i; j; j = (j - 1) & i) {
                cout<<i<<"  j "<<j<<endl;
                if (count_setbit(j) > k) {
                    continue;
                }

                int already_taken = i ^ ((1 << n) - 1);
                if ((already_taken & prerequisites[j]) == prerequisites[j]) {
                    dp[i] = min(dp[i], dp[i ^ j] + 1);
                }
            }
        }

        return dp[(1 << n) - 1];
    }

private:
    int count_setbit(int mask) {
        if (mask == 0) {
            return 0;
        }
        return 1 + count_setbit(mask & (mask - 1));
    }
};