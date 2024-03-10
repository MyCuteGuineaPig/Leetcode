class Solution {
public:
    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        int n = regular.size()+1;
        vector<long long>dp_r(n, numeric_limits<long long>::max());
        vector<long long>dp_e(n, numeric_limits<long long>::max());
        dp_r[0] = 0;
        dp_e[0] = expressCost;
        vector<long long>res;
        for(int i = 0; i < n - 1; ++i){
            dp_r[i+1] = min(dp_r[i], dp_e[i]) + regular[i];
            dp_e[i+1] = min(dp_e[i], dp_r[i] + expressCost) + express[i] ;     
            res.push_back(min(dp_r[i+1], dp_e[i+1]));
        }
        return res;
    }
};


class Solution {
public:
    long long TopDown(vector<int>& regular, vector<int>& express, int expressCost, int index, vector<long long >&dp_e, vector<long long >&dp_r, bool is_express){
        if(index == 0){
            return is_express? expressCost: 0;
        }
        if(is_express && dp_e[index] > -1){
            return dp_e[index];
        } 
        else if(!is_express && dp_r[index] > -1){
            return dp_r[index];
        }
        if (is_express){
            dp_e[index] = min(TopDown(regular, express, expressCost, index-1, dp_e, dp_r, is_express),
                              TopDown(regular, express, expressCost, index-1, dp_e, dp_r, !is_express) + expressCost) + express[index-1];
            return dp_e[index];
        } else{
            dp_r[index] = min(TopDown(regular, express, expressCost, index-1, dp_e, dp_r, is_express),
                              TopDown(regular, express, expressCost, index-1, dp_e, dp_r, !is_express)) + regular[index-1];
            return dp_r[index];
        }
    }

    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        int n = regular.size();
        vector<long long >dp_e(n+1, -1);
        vector<long long >dp_r(n+1, -1);
        TopDown(regular, express, expressCost, n, dp_e, dp_r, true);
        TopDown(regular, express, expressCost, n, dp_e, dp_r, false);
        vector<long long>res;
        for(int i = 1; i<=n; ++i){
            res.push_back(min(dp_e[i], dp_r[i]));
        }
        return res;
    }
};