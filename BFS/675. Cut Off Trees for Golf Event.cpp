/*

675. Cut Off Trees for Golf Event.cpp

You are asked to cut off trees in a forest for a golf event. The forest is represented as a non-negative 2D map, in this map:

0 represents the obstacle can't be reached.
1 represents the ground can be walked through.
The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.
You are asked to cut off all the trees in this forest in the order of tree's height - always cut off the tree with lowest height first. 
And after cutting, the original place has the tree will become a grass (value 1).

You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees. 
If you can't cut off all the trees, output -1 in that situation.

You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.

Example 1:
Input: 
[
 [1,2,3],
 [0,0,4],
 [7,6,5]
]
Output: 6
Example 2:
Input: 
[
 [1,2,3],
 [0,0,0],
 [7,6,5]
]
Output: -1
Example 3:
Input: 
[
 [2,3,4],
 [0,0,5],
 [8,7,6]
]
Output: 6
Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.
Hint: size of the given matrix will not exceed 50x50.



*/



class Solution {
public:

    int cutOffTree(vector<vector<int>>& forest) {
        n = forest.size();
        m = forest[0].size();
        for(int i = 0; i<n;i++){
            for(int j = 0; j<m;j++){
                if(forest[i][j]>1)
                    trees.push_back({forest[i][j],i,j});
            }
        }
        sort(trees.begin(),trees.end());
        int step = 0, currow = 0, curcol = 0;
        for(int i = 0; i<trees.size();i++){
            int curstep = findStep(forest,currow,curcol,trees[i][1],trees[i][2]);
            if(curstep == -1) return -1;
            step = curstep + step;
            currow = trees[i][1];
            curcol = trees[i][2];
        }
        return step;
    }
private:
    int findStep(vector<vector<int>>& forest, int cr, int cc, int tr, int tc){ //current row & column, tree row & column
        if(cr == tr && cc == tc) return 0;
        queue<pair<int,int>>q;
        vector<vector<bool>>visited(n,vector<bool>(m,false));
        visited[cr][cc] = true;
        vector<vector<int>>dir = {{-1,0},{0,-1},{1,0},{0,1}};
        q.push(make_pair(cr,cc));
        int step = 0;
        while(q.size()){
            step++;
            int cursize = q.size();
            for(int i = 0; i<cursize;i++){
                int currow = q.front().first;
                int curcol = q.front().second;
                q.pop();
                for(int j = 0; j<4;j++){
                    int newrow = currow + dir[j][0];
                    int newcol = curcol + dir[j][1];
                    if(newrow == tr && newcol == tc) return step;
                    if(newrow>=0 && newrow < n && newcol>= 0 && newcol < m && (!visited[newrow][newcol]) && forest[newrow][newcol]>=1){
                        //cout<<" currow "<<currow<<" curcol "<<curcol<<" newrow "<<newrow <<" newcol "<<newcol<<endl;
                        visited[newrow][newcol] = true;
                        q.push({newrow,newcol});
                    }
                }

            }
        }
        return -1;
    }


    int n, m;
    int step;
    vector<vector<int>>trees;
};