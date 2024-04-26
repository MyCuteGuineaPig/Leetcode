class SparseVector {
public:
    unordered_map<int, int>mp;
    SparseVector(vector<int> &nums) {
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] != 0){
                mp[i] = nums[i];
            }
        }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int res = 0; 
        for(auto &it: vec.mp){
            if (mp.count(it.first)){
                res += it.second * mp[it.first];
            }
        }
        return res;
    }
};



class SparseVector {
public:
    vector<pair<int,int>>non_zeros;
    SparseVector(vector<int> &nums) {
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] != 0){
                non_zeros.push_back({i, nums[i]});
            }
        }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int res = 0;
        for(int i = 0, j = 0;  i < vec.non_zeros.size() && j < non_zeros.size();){
            if(vec.non_zeros[i].first < non_zeros[j].first ) ++i;
            else if (vec.non_zeros[i].first > non_zeros[j].first ) ++j;
            else res += vec.non_zeros[i++].second * non_zeros[j++].second;
        }
        return res;
    }
};