class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        map<int, unordered_map<string, int>>table_count;
        set<string>foods;
        for(const auto& order: orders){
            ++table_count[stoi(order[1])][order[2]];
            foods.insert(order[2]);
        }
        
        vector<vector<string>>results = {{"Table"}};
        copy(foods.cbegin(), foods.cend(), back_inserter(results.back()));
        for(const auto& it: table_count){
            results.push_back({to_string(it.first)});
            transform(foods.cbegin(), foods.cend(), back_inserter(results.back()),
                [&it](const string& food){
                return to_string(it.second.count(food) ? it.second.at(food): 0);  
                    //cannot use it.second[food]
                }
            );
        }
        return results;
    }
};


class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        vector<unordered_map<string, int>> tables(501);
        set<string> foods;
        for (auto &v : orders) {
            foods.insert(v[2]);
            ++tables[stoi(v[1])][v[2]];
        }
        vector<vector<string>> res;
        for (auto t = 0; t <= 500; ++t) {
            if (t > 0 && tables[t].empty())
                continue;
            res.push_back(vector<string>());
            res.back().push_back(t == 0 ? "Table" : to_string(t));
            for (auto it = begin(foods); it != end(foods); ++it) {
                res.back().push_back(t == 0 ? *it : to_string(tables[t][*it]));
            }
        }
        return res;
    }
};