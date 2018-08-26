/*
699. Falling Squares
On an infinite number line (x-axis), we drop given squares in the order they are given.
The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point being positions[i][0] and sidelength positions[i][1].
The square is dropped with the bottom edge parallel to the number line, and from a higher height than all currently landed squares. 
We wait for each square to stick before dropping the next.
The squares are infinitely sticky on their bottom edge, 
and will remain fixed to any positive length surface they touch (either the number line or another square). 
Squares dropped adjacent to each other will not stick together prematurely.
Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped, 
after dropping squares represented by positions[0], positions[1], ..., positions[i].
Example 1:
Input: [[1, 2], [2, 3], [6, 1]]
Output: [2, 5, 5]
Explanation:
After the first drop of positions[0] = [1, 2]:
_aa
_aa
-------
The maximum height of any square is 2.
After the second drop of positions[1] = [2, 3]:
__aaa
__aaa
__aaa
_aa__
_aa__
--------------
The maximum height of any square is 5.  
The larger square stays on top of the smaller square despite where its center
of gravity is, because squares are infinitely sticky on their bottom edge.
After the third drop of positions[1] = [6, 1]:
__aaa
__aaa
__aaa
_aa
_aa___a
--------------
The maximum height of any square is still 5.
Thus, we return an answer of [2, 5, 5].
Example 2:
Input: [[100, 100], [200, 100]]
Output: [100, 100]
Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.
Note:
1 <= positions.length <= 1000.
1 <= positions[i][0] <= 10^8.
1 <= positions[i][1] <= 10^6.
[[2,3],[5,1],[6,2],[4,2]]
*/

/*
Solution 1: 
跟218. The Skyline Problem 解法类似， 画出square的轮廓
找到现在 xbegin - xend(p.first+p.second)的所有的点，最高的高度为地基的高度（h0)，再remove 所有xbegin 到xend 点
把 xbegin 设为 h0 + 高度(p.second), xend 设为 h1(p.first+p.second的前一点)

对比现在的高度和之前最高的高度，记录最高的高度

-1, 0 表示 在x = -1 高度为0,
需要两个iterator，
    itr 记录第一个大于

*/

class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        vector<int>res;
        map<int, int>height;
        int maxh = height[-1] = 0;
        for(auto p: positions){
            int l = p.first, h = p.second;
            auto itl = height.upper_bound(l); // 第一个比first 大的， prev(itl) 就是第一个比first一样的或者小的，再first下面的
            auto itr = height.lower_bound(l+h); // first + second是结束后第一个点, 可能等于
            // itr 不能是upper_bound, 如果是upper_bound, itr是大于l+h的点,
            // 但是当 erase(itl, itr)时可能删除l+h的点, 如果erase(itl, prev(itr)) 可能少删除了一点 小于l+r的一点 ( b.c prev(itr) 可能小于l+r)
            int h0 = prev(itl)->second;
            int h1 = itr->first == l+h ?  itr->second : prev(itr)->second;
            for(auto it = itl; it!=itr; it++)
                h0 = max(h0, it->second);//找p点下方最高的点
            height.erase(itl, itr);
            height[l] = h0 + h;
            height[l+h] = h1;
            maxh = max(maxh, h0+h);
            res.push_back(maxh);
        }
        return res;
    }
};


class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& pos) {
        map<int, int> h;
        vector<int> ans;
        for (auto& sqr : pos) {
            int x = sqr.first, y = sqr.first+sqr.second, hnow = sqr.second;
            auto it = h.upper_bound(x);
            
            int crnt = it==h.begin() ? 0 : prev(it)->second;
            int maxh = crnt;
            while (it!=h.end() && it->first<y) {
                crnt = it->second;
                maxh = max(maxh, crnt);
                it = h.erase(it);
            }
            
            h[x] = maxh + hnow;
            h[y] = crnt;
            
            ans.push_back( ans.empty() || ans.back()<maxh+hnow ? maxh+hnow : ans.back());
        }
        return ans;
    }
};



/* 
Solution 2  Offline Propagation, 
到i点之后，再到后面的点看是不是与后面的点交叉, 如果交叉更新点,

交叉点像       _____        ________       _____             i的左侧小于j的右侧,  j的左侧小于i的右侧
         ____|_    |   or  |  ___  |  or  |   _|__
        |    | |   |       | |   | |      |  | |  |

heights[i] 表示到i点的高度, 
heights[j] = max(heights[j], heights[i]) 不会移掉之前建立的地基， 
因为heights[j] 还没有process j点, 
分两个情况 
1. (i_0, i_01), (i_1, i_11), 相互不交接，但都与j交接，heights[j] 回去i_0 和i_1的最高值作为地基

比如[[1,1],[2,2],[1,3]]
        0  1  2   3   4   5   6 
    i = 0                           
            a               更新heights[0] = heights[2] = 1 （0和2点交叉）
        
    i = 1 
              a   a          更新heights[1] = 2, 此时 1点和2点交叉, 更新2点的地基为2
            a a   a 
           


2. (i_0, i_01), (i_1, i_11), 相互交接，还都与j交接, i_1 会建立在i_0上盖，再更新j点
比如[[1,3],[2,3],[2,6]]
     0  1  2   3   4   5   6 
i = 0                           
        a  a   a              更新heights[0] = heights[1] = heights[2] = 3都是交集的
        a  a   a                 
     -  a  a   a 

i = 1      a   a   a  
           a   a   a 
           a   a   a                          
        a  a   a              更新heights[1] += 3 = 6, 再跟新的了heights[2] = 6, 
        a  a   a                 
     -  a  a   a 



*/
class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        vector<int>heights(positions.size());
        for(int i = 0; i<positions.size(); i++){
            int i_left = positions[i].first, i_size = positions[i].second, i_right = positions[i].first+positions[i].second;
            heights[i] += i_size;
            for(int j = i+1; j<positions.size(); j++){
                int j_left = positions[j].first, j_size = positions[j].second, j_right = positions[j].first+positions[j].second;
                if(i_left < j_right && j_left <i_right){
                    heights[j] = max(heights[j], heights[i]);
                }
            }
        }

        vector<int>res;
        for(auto h: heights){
            res.push_back(res.empty()? h : h < res.back()? res.back():h);
        }
        return res;
    }
};


/* 
Solution 3 Segment Tree with Lazy Propagation

segment Tree with lazy progation: 

当现在点符合update range时候，只update 现在的点，不update child, 把update 给child的值存进lazy tree里 （lazy tree child 比较是update 它还是自己大)
比如： 现在segment tree 取的最大值: 
      
                         10 [0,7] 
                       /              \ 
                   4 [0:3]            10 [4: 7]            
              /          \          /        \
           3 [0:1]  4 [2:3]      10[4:5]     6 [6:7] 
        /    \     /    \      /     \      /    \
      0 [0] 3[1] 2 [2] 4 [3]  5 [4] 10 [5] 6 [6] 4 [7]

update [0:3] 为5， 
                                                                Lazy Tree 为
                         10 [0,7]                                              0
                       /              \                                      /   \ 
                   5 [0:3]            10 [4: 7]                            0       0
              /          \          /        \                            / \    /   \
           3 [0:1]  4 [2:3]      10[4:5]     6 [6:7]                     5   5   0    0
        /    \     /    \      /     \      /    \                      /\   /\  /\   /\
      0 [0] 3[1] 2 [2] 4 [3]  5 [4] 10 [5] 6 [6] 4 [7]                  0 0  0 0 0 0  0 0


step 1:  
    先coordinate compresion， 找到critical point: 
    比如[[1,2],[3,1],[2,4]] 第0个点start在1，结束在2，第二个点开始在3，结束还在3， 第二个点开始在2，结束在5， 
    用set (1,2,3,5)找到所有critical point, 这么做的好处是只有critical point才能决定高度
    比如x = 4只在2,4之间，我们知道4的值由点3,5的高度决定，4不是开始 也不是结束，所以x = 4点不重要

step 2: 
    构建segment tree with lazy propagation (query & update for those critical points),  
    query， update 不管范围是不是大了还是小了，如果此时lazy 不为0，先update lazy的，如果lazy 比现在值小，不update，但是需要把lazy的放进现在child

step 3： 
    每次query返回一个在[first, first + second -1]地基的高度，地基的高度+second = falling 之后的高度，现在到现在为止最高的maxh比，比它大，更新maxh


*/

// Time:  O(nlogn)
// Space: O(n)
// Segment Tree solution.
class Solution {
public:
    struct SegmentTree{
        vector<int>lazy,tree;
        int n;
        SegmentTree(int size){
            n = 1<<(static_cast<int>(ceil(log(size)/log(2)+1)));
            lazy.resize(n,0); tree.resize(n,0);
        }
        
        int query(int L, int R, int index, int s, int e){
            if(lazy[index]!=0){
                int update = lazy[index];
                tree[index] = max(tree[index], update);
                if(s!=e){
                    lazy[2*index]= max(lazy[2*index], update);  
                    /*
                    需要对比原因是 比如现在lazy 10   在10 的lazy 为8，所以我们要update 时候不动root 和右边的，动左面的 lazy 变成8
                                           /  \    
                                          2    10
                    */
                    lazy[2*index+1] = max(lazy[2*index+1], update);
                }
            }
            if( s> e || s > R || L > e) return 0; //s > R 现在起点大于 寻找终点: (寻找) (现在）, L > e 寻找的起点大于现在终点 (现在) (寻找) 
            if(L<=s && e <=R)  {
                return tree[index];
            }
            int mid = s + (e - s)/2;
            return max(query(L,R, 2*index, s, mid),query(L,R, 2*index+1, mid+1, e));
        }
        
        void update(int L, int R, int h, int index, int s, int e){
            if(lazy[index]!=0){
                int update = lazy[index];
                tree[index] = max(tree[index], update);
                if(s!=e){
                    lazy[2*index]= max(lazy[2*index], update);
                    lazy[2*index+1] = max(lazy[2*index+1], update);
                }
            }
            if( s> e || s > R || L > e)return;
            if(L<=s && e <=R) {
                tree[index] =  max(tree[index], h);
                if(s != e){
                    lazy[2*index]= max(lazy[2*index], h);
                    lazy[2*index+1] = max(lazy[2*index+1], h);
                }
                return;
            }
            int mid = s + (e - s)/2;
            update(L, R, h, 2*index, s, mid);
            update(L, R, h, 2*index+1, mid+1, e);
            tree[index] = max(tree[2*index],tree[2*index+1]);     
        }
        
    };
    
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        set<int>index; //coorindate compression
        for(auto p: positions){
            index.insert(p.first); 
            index.insert(p.first+p.second - 1);
        }
        SegmentTree sgt(index.size());
        vector<int>res; 
        int maxh = 0;
        for(auto p: positions){
            auto L = distance(index.begin(), index.find(p.first));
            auto R = distance(index.begin(), index.find(p.first+p.second-1));
            int h = sgt.query(L,R,1,0,index.size()-1) + p.second;
            sgt.update(L,R,h,1,0,index.size()-1);
            maxh = max(maxh, h);
            res.push_back(maxh);
        }
        return res;
    }
};





class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        set<int>coordinate;
        for(auto p: positions){
            coordinate.insert(p.first); coordinate.insert(p.first+p.second-1);
        }
        SegmentTree sgt(coordinate.size()); 
        int maxh = 0;
        vector<int>res;
        for(auto p: positions){
            auto L = distance(coordinate.begin(), coordinate.find(p.first));
            auto R = distance(coordinate.begin(), coordinate.find(p.first + p.second - 1));
            int h = sgt.query(L,R) + p.second;
            maxh = max(h, maxh);
            sgt.update(L, R, h);
            res.push_back(maxh);
        }
        
        return res;
    }
private:
    struct SegmentTreeNode{
        int start, end, val;
        SegmentTreeNode* left, *right;
        SegmentTreeNode(int start_, int end_, int val): start(start_), end(end_), left(NULL), right(NULL), val(val){}
    };
    
    class SegmentTree{
    public:      
        SegmentTreeNode* tree, *lazytree;
        SegmentTree(int size){
            buildTree(tree, lazytree, 0, size-1);
        }
        
        void buildTree(SegmentTreeNode*& root, SegmentTreeNode*& lazy, int start, int end){
            if(start > end) return;
            root = new SegmentTreeNode(start, end, 0);
            lazy = new SegmentTreeNode(start, end, 0);
            if(start == end) return;
            int mid = start + (end-start)/2;
            buildTree(root->left, lazy->left, start, mid);
            buildTree(root->right, lazy->right, mid+1, end);
        }
        
        int query(int L, int R){
            return queryutil(L,R, tree, lazytree);
        }
        
        int queryutil(int L, int R, SegmentTreeNode* root, SegmentTreeNode* lazy){
            if(lazy->val!=0) updateLazy(root, lazy);
            
            if(L>root->end || R < root->start) return 0;
            if(L <= root->start && R >= root->end) return root->val;
            
            int mid = root->start + (root-> end - root->start)/2;
            return max(queryutil(L, R, root->left, lazy->left), queryutil(L, R, root->right, lazy->right));
        }
        
        void update(int L, int R, int h){
            updateUtil(L, R, h, tree, lazytree);
        }
        
        int updateUtil(int L, int R, int h, SegmentTreeNode* root, SegmentTreeNode* lazy){
            if(lazy->val!=0) updateLazy(root, lazy);
            
            if(L>root->end || R < root->start) return root->val; //return 是val 不是0, 是0的话可能改变val 的值
            if(L <= root->start && R >= root->end) {
                root->val = max(root->val, h);
                if(root->start != root->end){
                    lazy->left->val = max(lazy->left->val, h);
                    lazy->right->val = max(lazy->right->val, h);
                }
                return root->val;
            }
            root->val = max(updateUtil(L, R, h, root->right, lazy->right), updateUtil(L,R,h,root->left, lazy->left));
            return root->val;
        }
        /*
        int updateUtil(int L, int R, int h, SegmentTreeNode* root, SegmentTreeNode* lazy){
            if(lazy->val!=0) updateLazy(root, lazy);
            
            if(L>root->end || R < root->start) return 0;
            if(L <= root->start && R >= root->end) {
                root->val = max(root->val, h);
                if(root->start != root->end){
                    lazy->left->val = max(lazy->left->val, h);
                    lazy->right->val = max(lazy->right->val, h);
                }
                return root->val;
            }
            root->val = max(root->val, max(updateUtil(L, R, h, root->left, lazy->left), updateUtil(L,R,h,root->right, lazy->right)));
            
            //或者可以
            //updateUtil(L, R, h, root->left, lazy->left);
            //updateUtil(L, R, h, root->right, lazy->right);
            //root->val = max(root->left->val, root->right->val);
           // 不可以root->val = max( updateUtil(L, R, h, root->left, lazy->left), updateUtil(L,R,h,root->right, lazy->right) );
           // 因为当 L>root->end || R < root->start 返回0， 是不行的
            
        
            return root->val;
        }
        */
        
        
        void updateLazy(SegmentTreeNode* root, SegmentTreeNode* lazy){
            int update = lazy->val;
            root->val = max(root->val, update);
            if(root->start != root-> end){
                lazy->left->val =max(lazy->left->val, update);
                lazy->right->val = max(lazy->right->val, update);
            }
        }
        
    };
};