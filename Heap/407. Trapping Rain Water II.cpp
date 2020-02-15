/*
407. Trapping Rain Water II

Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.


*/

/*
把长方形四边所有的cell push进min heap, 
然后pop 当前最小的height的cell,loop它的四边, 相当于从长方形从外向内走，先选取高最短的，然后看边上有没有比它矮的还没visit过边
- 如果cell一个边的高小于cell高， res +=  cell.h- heightmap[x][y]，

push进queue(push的height是当前height和cell的最大值, 不能是最小值, 
因为cell.height的最小值，所以圈内height有这个值决定（木桶效益取决于最短的板）


*/



class Solution {
public:
    struct cell{
        int x, y, h;
        cell(int x, int y, int h): x(x), y(y), h(h){
            //visited[x][y] = 1;
        }
    };
    
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.size() == 0 || heightMap[0].size() == 0) return 0;
        int n = heightMap.size(), m = heightMap[0].size();
        vector<vector<int>>visited(n,vector<int>(m));
        
        auto cmp = [](cell a, cell b){return a.h > b.h;};
        priority_queue<cell, vector<cell>, decltype(cmp)>minheap(cmp);
        
        for(int i = 0; i<n; i++){
            minheap.push(cell(i,0,heightMap[i][0])); visited[i][0] = 1;
            minheap.push(cell(i,m-1,heightMap[i][m-1])); visited[i][m-1] = 1;
        }
        for(int i = 1; i<m-1; i++){
            minheap.push(cell(0, i,heightMap[0][i])); visited[0][i] = 1;
            minheap.push(cell(n-1, i,heightMap[n-1][i]));  visited[n-1][i] = 1;
        }
        int res = 0;
        vector<pair<int,int>>dir = {{-1,0},{0,-1},{1,0}, {0,1}};
        while(!minheap.empty()){
            cell top = minheap.top(); minheap.pop();
            for(auto it : dir){
                int x = it.first + top.x;
                int y = it.second + top.y;
                if(x<0 || x>=n || y<0 || y>=m || visited[x][y])  continue;
                if(heightMap[x][y] < top.h) res+= top.h - heightMap[x][y];
                minheap.push(cell(x,y, max(top.h, heightMap[x][y]))); //因为top.h 是外面最低的,
                //if heightMap[x[y] < top.h, 那么这个block 已经fill 了 top.h - heightMap[x][y])
                visited[x][y] = 1;
            }
            
        }
        return res;
    }
};

// Time:  O(m * n * log(m + n)) ~ O(m * n * log(m * n))
// Space: O(m * n)

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        // Init m_, n_, is_visited_.
        m_ = heightMap.size();
        if (!m_) {
            return 0;
        }
        n_ = heightMap[0].size();
        if (!n_) {
            return 0;
        }

        is_visited_ = vector<vector<bool>>(m_, vector<bool>(n_, false));

        int trap = 0;

        // Put the cells on the border into min heap.
        for (int i = 0; i < m_; ++i) {
            heap_.emplace(Cell{i, 0, heightMap[i][0]});
            is_visited_[i][0] = true;
            heap_.emplace(Cell{i, n_ - 1, heightMap[i][n_ - 1]});
            is_visited_[i][n_ - 1] = true;
        }
        for (int j = 0; j < n_; ++j) {
            heap_.emplace(Cell{0, j, heightMap[0][j]});
            is_visited_[0][j] = true;
            heap_.emplace(Cell{m_ - 1, j, heightMap[m_ - 1][j]});
            is_visited_[m_ - 1][j] = true;
        }
        const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                {-1, 0}, {1, 0}};
        // BFS with priority queue (min heap)
        while (!heap_.empty()) {
            Cell c = heap_.top();
            heap_.pop();
            for (const auto& d : directions) {
            	trap += fill(heightMap, c.i + d.first, c.j + d.second, c.height);
            }
        }

        return trap;
    }

private:
    int fill(const vector<vector<int>>& heightMap, int i, int j, int height) {
        // Out of border.
        if ( i < 0 || i >= m_ || j < 0 || j >= n_) {
            return 0;
        }

        // Fill unvisited cell.
        if (!is_visited_[i][j]) {
            heap_.emplace(Cell{i, j, max(height, heightMap[i][j])});
            is_visited_[i][j] = true; // Marked as visited.
            return max(0, height - heightMap[i][j]); // Fill in the gap.
        }

        return 0;
    }

    struct Cell {
        int i;
        int j;
        int height;
    };

    struct Compare {
        bool operator()(const Cell& a, const Cell& b) {
            return a.height > b.height;
        }
    };

    int m_;
    int n_;
    vector<vector<bool>> is_visited_;
    priority_queue<Cell ,vector<Cell>, Compare> heap_; // Use min heap to get the lowerest cell.
};
