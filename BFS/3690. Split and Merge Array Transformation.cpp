class Solution {
public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        if (equal(nums1.begin(), nums1.begin()+nums1.size(), nums2.begin())){
            return 0;
        }
        int steps = 0;
        set<vector<int>>visited;
        queue<vector<int>>q;
        q.push(nums1);
        int n = nums1.size();
        visited.insert(nums1);
        while(!q.empty()){
            int size = q.size();
            for(int z = 0; z < size; ++z){
                auto top = q.front(); q.pop();
                
                for(int l = 0; l <n; ++l){
                    for(int r = l + 1; r <=n; ++r){
                        vector<int>sub (top.begin() + l, top.begin() + r);
                        vector<int>remain; 
                        for(int k = 0; k < l; ++k) remain.push_back(top[k]);
                        for(int k = r; k < n; ++k) remain.push_back(top[k]);
                        
                        for(int k = 0; k <= remain.size(); ++k){
                            vector<int> merge; merge.reserve(n);
                            merge.insert(merge.end(), remain.begin(), remain.begin()+k);
                            merge.insert(merge.end(), sub.begin(), sub.end());
                            merge.insert(merge.end(), remain.begin()+k, remain.end());
                            if(visited.count(merge)) continue;
                            if(equal(merge.begin(), merge.begin()+n, nums2.begin())) {
                                return steps + 1;
                            }
                            visited.insert(merge);
                            q.push(merge);
                        }
                    }
                }
            }
            steps += 1;
        }
        return -1;
    }
};