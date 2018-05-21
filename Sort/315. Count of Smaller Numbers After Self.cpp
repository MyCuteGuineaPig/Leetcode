/*

315. Count of Smaller Numbers After Self


You are given an integer array nums and you have to return a new counts array. 
The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0] 
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

*/


/*
Merge Sort
*/

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int>smaller(nums.size(),0);
        vector<int>indices(nums.size(),0);
        iota(indices.begin(),indices.end(),0);
        mergeSort(nums,indices,0,nums.size(),smaller); 
        return smaller;
    }
    
    void mergeSort(const vector<int>& nums,vector<int>& indices, int l, int r, vector<int>& smaller){
        if(r-l<=1) return;
        int mid = (l+r)>>1;
        mergeSort(nums, indices, l, mid, smaller);
        mergeSort(nums, indices, mid, r, smaller);
        vector<int>temp;
        int i = mid-1, j = r-1;
        while(i>=l || j>=mid){
            if(j<mid || (i>=l && nums[indices[i]] > nums[indices[j]])){
                temp.push_back(indices[i]); //先推nums大的进temp，为了有小到大排序，最后reverse
                smaller[indices[i]] += j-mid+1;
                i--;
            }else{
                temp.push_back(indices[j]);
                j--;
            }
        }
        reverse(temp.begin(),temp.end());
        move(temp.begin(),temp.end(),indices.begin()+l);
    }
};



class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int>smaller(nums.size(),0);
        vector<int>indices(nums.size(),0);
        iota(indices.begin(),indices.end(),0);
        mergeSort(nums,indices,0,nums.size()-1,smaller);
        return smaller;
    }
    
    void mergeSort(const vector<int>& nums,vector<int>& indices, int l, int r, vector<int>& smaller){
        if(r-l<1) return;
        int mid = (l+r)>>1;
        mergeSort(nums, indices, l, mid, smaller);
        mergeSort(nums, indices, mid+1, r, smaller); //l必须是mid+1,因为容易进死循环，比如长度为2，l=0,r=1, 做mid永远为0
        vector<int>temp;
        int i = mid, j = r;
        while(i>=l || j>=mid+1){
            if(j<=mid || (i>=l && nums[indices[i]] > nums[indices[j]])){
                temp.push_back(indices[i]); //先推nums大的进temp，为了有小到大排序，最后reverse
                smaller[indices[i]] += j-mid;
                i--;
            }else{
                temp.push_back(indices[j]);
                j--;
            }
        }
        reverse(temp.begin(),temp.end());
        move(temp.begin(),temp.end(),indices.begin()+l);
    }
};


class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,0);
        vector<pair<int,int>> numindex;
        for(int i=0;i<n; i++)
            numindex.emplace_back(nums[i],i);
        mergeSort(numindex, res, 0, n-1);
        return res;
    }
    void mergeSort(vector<pair<int,int>>& numindex, vector<int> & res, int start, int end){
        if(start>=end)
            return;
        int mid = start + (end-start)/2;
        mergeSort(numindex, res, start, mid);
        mergeSort(numindex, res, mid+1, end);
        auto compare = [](pair<int, int> a, pair<int, int> b) { return a.first < b.first;};
        for(int i= mid; i >=start; i--){
            auto it = lower_bound(numindex.begin()+mid+1, numindex.begin()+end+1, numindex[i], compare);
            int dist = distance(numindex.begin()+mid+1, it);
            if(dist==0) break;
            res[numindex[i].second]+=dist;
        }
        inplace_merge(numindex.begin()+start, numindex.begin()+mid+1, numindex.begin()+end+1,compare);
    }
};


/*
binary search
首先可以使用用二分搜索法，思路是将给定数组从最后一个开始，用二分法插入到一个新的数组，这样新数组就是有序的，
*/
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> t, res(nums.size());
        for (int i = nums.size() - 1; i >= 0; --i) {
            int d = distance(t.begin(), lower_bound(t.begin(), t.end(), nums[i]));
            res[i] = d;
            t.insert(t.begin() + d, nums[i]);
        }
        return res;
    }
};


/*
balanced search tree, 

比如[3, 2, 2, 6, 1], 树【0】记录的是left-tree node 个数（包含重复的）,树[1] 记录的是duplicate的个数,每次insert，记录向右走过的tree的个数
                1(0, 1)
                     \
                     6(3, 1)
                     /
                   2(0, 2)
                       \
                        3(0, 1)

*/


class Solution {
public:
    struct TreeNode
	{
		int dup = 1, sum = 0, val = 0;
		TreeNode* left = nullptr, *right = nullptr;
		TreeNode(int val) : val(val) {}
	};

    void insert(TreeNode *&root, vector<int>&smaller,int preCount, int val, int pos){
        if(!root){
            root = new TreeNode(val);
            smaller[pos] = preCount;
        }
        else if(root->val == val){
            root->dup++;
            smaller[pos] = preCount+root->sum;
        }
        else if(root->val>val){
            root->sum++;
            insert(root->left, smaller,preCount,val, pos);
        }else{
            insert(root->right,smaller, preCount+root->sum+root->dup,val, pos);
        }
    }
    
    vector<int> countSmaller(vector<int>& nums) {
        TreeNode *tree = nullptr;
        vector<int>smaller(nums.size(),0);
        for(int i = nums.size()-1; i>=0;i--){
            cout<<" i "<<i<<endl;
            insert(tree,  smaller, 0, nums[i], i);
        }
        return smaller;
    }
};



// Binary Search Tree
class Solution {
public:
    struct Node {
        int val, smaller;
        Node *left, *right;
        Node(int v, int s) : val(v), smaller(s), left(NULL), right(NULL) {}
    };
    int insert(Node *&root, int v) {
        if (!root) return (root = new Node(v, 0)), 0;
        if (root->val > v) return root->smaller++, insert(root->left, v);
        else return insert(root->right, v) + root->smaller + (root->val < v ? 1 : 0);//only adding 1 on preSum if root.val is only smaller than val
    }
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res(nums.size());
        Node *root = NULL;
        for (int i = nums.size() - 1; i >= 0; --i) {
            res[i] = insert(root, nums[i]);
        }
        return res;
    }
};