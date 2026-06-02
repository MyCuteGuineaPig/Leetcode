class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int max_level = 0;
        unordered_map<int, vector<int>> mp;
        auto dfs = [&](this auto&& dfs, vector<NestedInteger>&li, int l) -> void {
            max_level = max(max_level, l);
            for(int i = 0; i < li.size(); ++i) {
                if(li[i].isInteger()) {
                    mp[l].push_back(li[i].getInteger());
                }
                else {
                    dfs(li[i].getList(), l+1);
                }
            }
        };

        dfs(nestedList, 1);
        int res = 0;
        for(auto i: mp){
            int level = i.first; 
            for(auto num: i.second) 
                res += (max_level - level + 1) * num;
        }
        return res;
    }
};



class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int max_level = 0;
        unordered_map<int, vector<int>> mp;
        queue<vector<NestedInteger>> q; 
        q.push(nestedList);
        while(!q.empty()) {
            ++max_level;
            int size = q.size();
            for(int i = 0; i < size; ++i) {
                auto li = q.front(); q.pop();
                for(int i = 0; i < li.size(); ++i) {
                    if(li[i].isInteger()) {
                        mp[max_level].push_back(li[i].getInteger());
                    }
                    else {
                        q.push(li[i].getList());
                    }
                }   
            }
        }

        int res = 0;
        for(auto i: mp){
            int level = i.first; 
            for(auto num: i.second) 
                res += (max_level - level + 1) * num;
        }
        return res;
    }
};


/*

The answer is

∑value⋅(maxDepth−depth+1)

Expanding:

=∑(value⋅(maxDepth+1)−value⋅depth)

Using distributivity:

=(maxDepth+1)∑value−∑(value⋅depth)


 */
class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        
        auto dfs = [&](this auto&& dfs, const vector<NestedInteger>& li, int level ) -> tuple<int, int, int> {
            int maxdepth = level; 
            int sumOfElements = 0; 
            int sumOfProducts = 0; 

            for(int i = 0; i < li.size(); ++i) {
                if (li[i].isInteger()) {
                    sumOfElements += li[i].getInteger();
                    sumOfProducts += li[i].getInteger() * level;
                } else {
                    auto [child_maxdepth, child_sumOfElements, child_sumOfProducts] = dfs(li[i].getList(), level + 1);
                    maxdepth = max(child_maxdepth, maxdepth);
                    sumOfElements += child_sumOfElements;
                    sumOfProducts += child_sumOfProducts;
                }
            }
            return {maxdepth, sumOfElements, sumOfProducts};
        };

        auto [maxdepth, sumOfElements, sumOfProducts] = dfs(nestedList, 1);
        return (maxdepth + 1)*sumOfElements - sumOfProducts;
    } 
};


class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        auto [maxDepth, sumOfElements, sumOfProducts] =
            getWeightedSumTriplet(nestedList, 1);

        return (maxDepth + 1) * sumOfElements - sumOfProducts;
    }

private:
    tuple<int, int, int> getWeightedSumTriplet(
        const vector<NestedInteger>& list,
        int depth
    ) {
        int sumOfProducts = 0;
        int sumOfElements = 0;
        int maxDepth = 0;

        for (const NestedInteger& nested : list) {
            if (nested.isInteger()) {
                int val = nested.getInteger();

                sumOfProducts += val * depth;
                sumOfElements += val;
                maxDepth = max(maxDepth, depth);
            } else {
                auto [childMaxDepth, childSumOfElements, childSumOfProducts] =
                    getWeightedSumTriplet(nested.getList(), depth + 1);

                sumOfProducts += childSumOfProducts;
                sumOfElements += childSumOfElements;
                maxDepth = max(maxDepth, childMaxDepth);
            }
        }

        return {maxDepth, sumOfElements, sumOfProducts};
    }
};