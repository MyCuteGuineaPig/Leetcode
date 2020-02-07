"""
307. Range Sum Query - Mutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.

"""

/*

BIT TREE: 

比如一个tree 有8个节点，更新时候
更新1 ->2 ->4 ->8
更新2 ->4 -> 8
更新3(11) -> 4(11+1 = 100)->8
更新4 (100) ->8(100+100 = 1000)
更新5 -> 6 -> 8
更新6(110) ->8 (110 + 10 = 1000)
更新7->8

如果左面连续都是1，直接上最左面bit的下一位 比如110 -> 1000, 1110 -> 10000, 1100 -> 10000
原因: 左面的1已经存了需要的sum，比如110， 100 存了前4，所以110-> 1000 保证8拥有(5,6的和)，比如111->1000， 因为110存了（5，6的和), 100(存了1-4的和），也因为8已经存了5和6的和，只需存第7个数即可

求sum 
求1:  1
求2:  2
求3:  3 + 2 (11, 10)
求4:  4
求5:  5 + 4 (101, 100)
求6:  6 + 4 (110, 100)
求7:  7 + 6 + 4 （111， 110， 100）
求8， 8

BIT index n只存最小bit下面的和
比如1110 有的和是1110 + 1101 
比如1100， 有和的是1001 + 1010 + 1011 + 1100
比如100 有的和是1， 10, 100,

*/
class NumArray {
public:
    vector<int>sums;
    vector<int>nums;
    int size;
    NumArray(vector<int> nums_) {
        nums = nums_;
        size = nums.size();
        sums.resize(size+1,0); //必须size +1, 否则 i =0, i+=lowerbot(0) = 0 无线循环
        for(int i = 0; i<nums.size();i++){
            updateTree(i,nums[i]);
        }
    }
    
    void update(int i, int val) {
        updateTree(i,val-nums[i]);
        nums[i] = val;
    }

    int sumRange(int i, int j) {
       return getSum(j)-getSum(i-1);
    }
private:
    void updateTree(int i, int delta){
        i++;
        while (i<=size){ //注意是 i <= size
            sums[i] += delta;
            i += lowerbit(i);
        }
    }
    int lowerbit(int x) {return x & (-x);}

    int getSum(int i){
        int res = 0;
        i++;
        while( i>0){ //注意是i>0
            res += sums[i];
            i -= lowerbit(i);
        }
        return res;
    }
    
};


class NumArray {
public:
    vector<int>arr;
    vector<int>nums;
    int size;
    NumArray(vector<int> nums) {
        size = nums.size();
        arr.resize(size+1, 0);
        this->nums = nums;
        for(int i = 0; i<size; i++){
            updateTree(i+1, nums[i]);
        }
    }
    
    void update(int i, int val) {
        updateTree(i+1, val - nums[i]);
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        return getSum(j+1) - getSum(i);
    }
    
    void updateTree(int i, int delta){
        while(i<=size){
            arr[i]+=delta;
            i += i&(-i);
        }
    }
    
    int getSum(int i){
        int sum = 0;
        while(i>0){
            sum += arr[i];
            i -= i&(-i);
        }
        return sum;
    } 
};


/*
Segment Tree
                 41 [0:5]
              /           \  
            14[0:2]       27 [3:5]
          /    \         /        \  
        4[0:1]  5[2:2]  16[3:4]  11 [5:5]
        /   \          /     \ 
    1[0:0]  3 [1:1] 7[3: 3]  9 [4:4]

buildTree 把start, end一分为2，cur 的sum表示 [start : end]的sum， left = [start, mid], right = [mid+1, end]

modifyTree: 先找到start == end == i的index，并找到diff，把parent 都加上diff

queryTree: 如果当前是 [start, end] start< i < mid < j <end: queryTree(i, mid, node->left) + queryTree(mid+1, j, node->right);
如果是 mid < i < j <= end, queryTree(i, j, node->right);
如果是 start <= i < j <= mid, queryTree(i, j, node->left);

*/
struct SegmentTreeNode{
    int start, end, sum;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end): start(start), end(end), sum(0), left(NULL), right(NULL){}
};


class NumArray {
public:
    NumArray(vector<int> nums) {
        root = buildTree(nums, 0, nums.size()-1);
    }
    
    void update(int i, int val) {
        modifyTree(i, val, root);
    }
    
    int sumRange(int i, int j) {
        return queryTree(i, j, root);
    }
    
    SegmentTreeNode* buildTree(const vector<int>& nums, int start, int end){
        if(start > end) return nullptr;
        SegmentTreeNode* cur = new SegmentTreeNode(start, end);
        if(start == end){
            cur->sum = nums[start];
            return cur;
        }
        int mid = (start+end)>>1;
        cur->left = buildTree(nums, start, mid);
        cur->right = buildTree(nums, mid+1, end);
        cur->sum += cur->left->sum + cur->right->sum;
        return cur;
    }
    
    int modifyTree(int i, int val,SegmentTreeNode* node){
        if(!node || node->start > i || node->end < i) return 0;
        int diff;
        if(node->start == i && node->end == i){
            diff = val - node->sum;
            node->sum = val;
            return diff;
        }
        int mid = (node->start + node->end)>>1;
        if( i <= mid) diff = modifyTree(i, val, node->left);
        else diff = modifyTree(i, val, node->right);
        node->sum += diff;
        return diff;
    }
    
    int queryTree(int i, int j, SegmentTreeNode* node){
        if(!node) return 0;
        if(node->start == i && node->end == j) return node->sum;
        int mid = (node->start + node->end)>>1;
        if(i>mid) return queryTree(i, j, node->right);
        else if(j<=mid) return queryTree(i, j, node->left);
        return queryTree(i, mid, node->left) + queryTree(mid+1, j, node->right);
    }
    
private:
    SegmentTreeNode *root;
};



class NumArray {
struct Tree{
    Tree* left = nullptr;
    Tree* right = nullptr;
    int sum = 0;
    int l, r; 
    Tree(int lf, int rf, int sum): l(lf), r(rf), sum(sum){}
}; 
public:
    Tree* t;
    NumArray(vector<int>& nums) {
        buildTree(&t, 0, nums.size()-1, nums);
    }
    
    void update(int i, int val) {
        modifyTree(t, i, val);
    }
    
    int sumRange(int i, int j) {
        return calculateSum(t, i, j);
    }

    int buildTree(Tree **tree, int l, int r, const vector<int>& nums){
        if(l>r) 
            return 0;
        if(l == r){
           *tree = new Tree(l,r, nums[l]);
            return nums[l];
        }
        int mid = (l + r ) >> 1;
        *tree = new Tree(l, r, 0);
        int left = buildTree(&((*tree)->left), l, mid, nums);
        int right = buildTree(&((*tree)->right), mid+1, r, nums);
        (*tree)->sum += left + right;
        return (*tree)->sum;
    }

    int modifyTree(Tree* tree, int index, int num){
        if(tree->l == tree->r && tree->l == index){
            int delta = num - tree->sum; 
            tree->sum = num;
            return delta;
        }
        int delta ;
        int mid = (tree->l + tree->r)>>1;
        if(mid >= index)
            delta = modifyTree(tree->left, index, num);
        else
            delta = modifyTree(tree->right, index, num);
        tree->sum += delta;
        return delta;
    }

    int calculateSum(Tree* tree, const int& l, const int& r){
        if(!tree) return 0;
        if(tree->l > r || tree->r < l ) return 0;
        if(tree->l >= l && tree->r <= r)
            return tree->sum; 
        int left = 0, right = 0;
        if(tree->r >= l ) left = calculateSum(tree->left, l , r);
        if(tree->l <= r) right = calculateSum(tree->right, l, r);
        return left + right;
    }
};
