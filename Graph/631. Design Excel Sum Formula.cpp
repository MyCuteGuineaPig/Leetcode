class Excel {
public:
    Excel(int height, char width) {
        point_value.resize(26, vector<int>(26));
        this->height = height;
        this->width = width - 'A';
    }
    
    void set(int row, char column, int val) {
        int x = row - 1;
        int y = column - 'A';
        int change = val - point_value[x][y];
        int cur = x*26 + y;

        //remove all nodes from nxt -> cur; 
        // maybe there is a formula setup to cur, remove all of them
        for(auto& nxt: reverse_graph[cur]){
            graph[nxt].erase(cur);
        }
        reverse_graph.erase(cur);
        propagate(cur, change);
    }
    
    int get(int row, char column) {
        return point_value[row-1][column-'A'];
    }
    
    int sum(int row, char column, vector<string> numbers) {
        int cur_x = row - 1; 
        int cur_y = column - 'A';
        int cur_xy = cur_x*26 + cur_y;
        int increase_value = 0;
        int old_value = point_value[cur_x][cur_y];

        //remove all nodes from nxt -> cur; 
        // maybe there is a formula setup to cur, remove all of them
        for(auto& nxt: reverse_graph[cur_xy]){
            graph[nxt].erase(cur_xy);
        }
        reverse_graph.erase(cur_xy);

        for(auto& num: numbers){
            size_t break_ =  num.find(':');
            if(break_  == string::npos){
                int x = 0, y = 0;
                get_x_y(num, x, y);
                int xy = x*26 + y; 
                graph[xy][cur_xy] += 1;
                increase_value += point_value[x][y];
                reverse_graph[cur_xy].insert(xy);
            } else {
                
                int x0 = 0, y0 = 0,  x1 = 0, y1 = 0; 
                get_x_y(num.substr(0, break_), x0, y0);
                get_x_y(num.substr(break_ + 1, num.size()-break_ - 1), x1, y1);

                for(int a = x0; a <=x1; ++a ){
                    for(int b = y0; b <=y1; ++b ){
                        int ab = a * 26 + b;
                        graph[ab][cur_xy] += 1;
                        increase_value += point_value[a][b];
                        reverse_graph[cur_xy].insert(ab);
                    }
                }
                
            }
        }
        
        propagate(cur_xy, increase_value - old_value);
        point_value[cur_x][cur_y] = increase_value;
        

        return  point_value[cur_x][cur_y];
    }

private: 
    unordered_map<int, unordered_map<int, int>> graph; 
    unordered_map<int, unordered_set<int>>reverse_graph;
    //first is the source, second key is dest, value is number of count 
    vector<vector<int>>point_value;
    int height = 0; 
    int width = 0;

    void get_x_y(const string& s, int& x, int& y){
        y = s[0]-'A';
        x = stoi(s.substr(1, s.length()-1))-1;
    }

    void propagate(int cur, int value){
        int x = cur / 26;
        int y = cur % 26; 
        
        point_value[x][y] += value;
        for(auto & nxt: graph[cur]){
            propagate(nxt.first, value * nxt.second);
        }
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(height, width);
 * obj->set(row,column,val);
 * int param_2 = obj->get(row,column);
 * int param_3 = obj->sum(row,column,numbers);
 */



class Excel {
public:
    Excel(int height, char width): values(height, vector<int>(width - 'A' + 1)), expressions(height, vector<vector<string>>(width - 'A' + 1)) {}
    
    void set(int row, char column, int val) {
        values[row - 1][column - 'A'] = val;
        expressions[row - 1][column - 'A'].clear();
        clear(row, column);
    }
    
    int get(int row, char column) {
        if (expressions[row - 1][column - 'A'].empty())
            return values[row - 1][column - 'A'];
        if (cache.count({row, column}))
            return cache[{row, column}];
        int res = 0;
        for (const string& expression: expressions[row - 1][column - 'A'])
        {
            if (const size_t pos = expression.find(':');
                pos == string::npos)
            {
                const int r = stoi(expression.substr(1));
                const char c = expression.front();
                res += get(r, c);
            }
            else
            {
                const string first = expression.substr(0, pos);
                const string second = expression.substr(pos + 1);
                const int x1 = stoi(first.substr(1));
                const int x2 = stoi(second.substr(1));
                const char y1 = first.front();
                const char y2 = second.front();
                for (int i = x1; i <= x2; i++)
                {
                    for (char j = y1; j <= y2; j++)
                    {
                        res += get(i, j);
                    }
                }
            }
        }
        return cache[{row, column}] = res;
    }
    
    int sum(int row, char column, vector<string> numbers) {
        expressions[row - 1][column - 'A'] = numbers;
        clear(row, column);
        return get(row, column);
    }

private:
    vector<vector<int>> values;
    vector<vector<vector<string>>> expressions;
    constexpr static auto hasher = [] (const pair<int, char>& p) {
        return hash<int>{}(p.first) ^ hash<char>{}(p.second);
    };
    unordered_map<pair<int, char>, int, decltype(hasher)> cache;
    
    void clear(const int row, const char column)
    {
        cache.clear();
    }
};