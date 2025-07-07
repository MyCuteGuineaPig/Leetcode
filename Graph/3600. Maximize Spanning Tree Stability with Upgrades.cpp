/*
Final Result
The final result is the minimum of:

weakest "must" edge
weakest non-doubled edge (n - 1 - k) : 第一个不用double 的edge
weakest edge multiplied by 2 (if k != 0） 每一个都需要multiple的

我们尽可能用大的strength的edge组成tree
 */


class Solution {
public:
    int find(int i, vector<int> &ds) {
        //cout<<" i "<<i <<" ds[i] "<<ds[i]<<endl;
        return ds[i] < 0 ? i : ds[i] = find(ds[i], ds);
    }
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        vector<array<int, 3>> s_u_v;
        vector<int> ds(n, -1);
        int used_e = 0, res = 200000, min_single = 200000, min_double = 100000;
        for (const auto &e : edges) {
            if (e[3]) {
                if (int a = find(e[0], ds), b = find(e[1], ds); a == b)
                    return -1;
                else {
                    ++used_e;
                    ds[b] = a;
                    res = min(res, e[2]);                    
                }
            }
            else
                s_u_v.push_back({e[2], e[1], e[0]});
        }
        sort(begin(s_u_v), end(s_u_v), greater<>());
        for (auto &[s, u, v] : s_u_v)  {  
            cout<< " s " << s << " u " << u << " v "<< v << endl;            
            if (int a = find(u, ds), b = find(v, ds); a != b) {
                ds[b] = a;
                if (++used_e == n - 1 - k)
                    min_single = s;
                min_double = s;
                cout<<" min_single "<<min_single<< " min_double "<<min_double<<endl;
            }
        }
        return used_e == n - 1 ? min({res, min_single, min_double * (k ? 2 : 1)}) : -1;
    }
};


class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        auto find = [&](this auto&& find, int i, vector<int>&dp) -> int{
            return dp[i] < 0 ? i : dp[i] = find(dp[i], dp);
        };

        vector<array<int,3>> tree;
        vector<int>dp(n,-1);
        int used_e = 0, min_single = numeric_limits<int>::max(), min_double = numeric_limits<int>::max(), must = numeric_limits<int>::max();
        for(const auto & e: edges){
            if (e[3]) {
                if ( int root_a = find(e[0], dp), root_b = find(e[1], dp); root_a == root_b)
                {
                    return -1;
                } else {
                    ++used_e; 
                    dp[root_b] =  root_a; 
                    must = min(must, e[2]);
                }
            } else {
                tree.push_back({e[2], e[0], e[1]});
            }
        }
        sort(tree.begin(), tree.end(), greater<>());
        for(const auto& [s, u, v]: tree){
            if ( int root_a = find(u, dp), root_b = find(v, dp); root_a != root_b) {
                dp[root_b] = root_a;
                if (++used_e == n - 1- k  ){
                    //让最大的edge 不double， 小的edge double， 才能获得最大的score
                    // 如果n个点，需要n-1 edge, 除去k个double的，剩下是n-1-k个
                    min_single = s;
                }
                min_double = s;
            }
            //for(auto k : dp)
            //    cout << k << " , ";
            //cout << endl;
        }
        //cout<<" used_e "<<used_e<<endl;
        return used_e == n - 1 ? min({(long)must, (long)min_single, (long)min_double*(k>0 ? 2 : 1)}): -1;
    }
};