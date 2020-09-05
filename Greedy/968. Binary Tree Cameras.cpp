
/*

root->val = 2, 表示 可以cover itself, parent,  可以向上移动一位,
root->val = 1, 表示 可以cover children, itself, parent, 点不能移动

比如  step         1  2  3   4
         0                  0  
        / 
        0                   1 
          \  
          0               2  0
          /
         0             0  0   0
          \                 
           0         1  1  1  1
          /  
         0        2  0  0  0  0


 */

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        auto tree = prune(root);
        return count(tree);
    }
    
    TreeNode* prune(TreeNode* root){
        if(!root) return root;
        if(!root->left && !root->right){
            root->val = 2;
            return root;
        }

        auto l = prune(root->left);
        auto r = prune(root->right);
        
        if(l && l->val == 2 || r && r->val == 2){
            root->val = 1;
            if(l && l->val == 2)
                root->left->val = 0;
            if(r && r->val == 2)
                root->right->val = 0;
        }
        else if((!l || l->val == 0) && (!r || r->val == 0)){
            root->val = 2;
        }
        return root;
    }
    
    int count(TreeNode* t){
        if(!t) return 0;
        auto l = count(t->left);
        auto r = count(t->right);
        return l + r + (t->val > 0);
    }
};


/*
Return 0 if it's a leaf.
Return 1 if it's a parent of a leaf, with a camera on this node.
Return 2 if it's coverd, without a camera on this node.

For each node,
if it has a child, which is leaf (node 0), then it needs camera.
if it has a child, which is the parent of a leaf (node 1), then it's covered.

If it needs camera, then res++ and we return 1.
If it's covered, we return 2.
Otherwise, we return 0.


比如  括号里是返回值

         0 (2)
       /   \
      0(1)   0 (2)
     /        \ 
    0(0)        0 (1)
                  \ 
                   0(0)

 */

class Solution {
public:
    
   int res = 0;
    int minCameraCover(TreeNode* root) {
        return (dfs(root) < 1 ? 1 : 0) + res;
    }

    int dfs(TreeNode* root) {
        if (!root) return 2;
        int left = dfs(root->left), right = dfs(root->right);
        if (left == 0 || right == 0) {
            res++;
            return 1;
        }
        return left == 1 || right == 1 ? 2 : 0; // 返回0是两边都是2
    }
};


//-1: null;
//0: no camera, no cover;
//1: no camera, covered;
//2: has camera, covered;
class Solution {

    int result = 0;
    public int minCameraCover(TreeNode root) {
        int state = helper(root);
        //如果根节点没有被cover则应该再放置一个camera
		//if root isn't covered, should place one more camera.
        return state == 0 ? result + 1 : result;
    }

    private int helper(TreeNode root) {
        //null的情况 (null case)
        if (root == null)
            return -1;

        //叶子节点 (leaf node case)
        if (root.left == null && root.right == null) 
            return 0;

        int leftState = helper(root.left), rightState = helper(root.right);

        //如果任意一child为no camera, no cover, 则放置camera, return 2
		//if one of left or right child is no camera, no cover, then place a camera, return 2
        if (leftState == 0 || rightState == 0) {
            result++;
            return 2;
        }

        //如果两child都为no camera, covered, 或者一边为空一边为no camera, covered, 则return no camera, no cover 即 0
		//if two child are no camera, covered, or one child is null and other child is no camera, covered, then return 0
        if ((leftState == 1 || leftState == -1) && (rightState == 1 || rightState == -1))
            return 0;

        //other case
        return 1;
    }
}

/*
For any Node:

 we can be in one of these situations:

1. There is a camera;
2. Node is monitored;
3. Node is not monitored.


First case is simple.

For the second case, we can either install or not an additional camera. 
For the third case, we must install the camera to the node itself, 
        or to either of the children. We track the minimum number of cameras of all these choices.

 */

class Solution {
public:
    int minCameraCover(TreeNode* root, bool hasCamera = false, bool isMonitored = false) {
        if (root == nullptr) return 0;
        if (hasCamera) return 1 + minCameraCover(root->left, false, true) + minCameraCover(root->right, false, true);
        if (isMonitored) {
            auto noCam = minCameraCover(root->left, false, false) + minCameraCover(root->right, false, false);
            auto rootCam = 1 + minCameraCover(root->left, false, true) + minCameraCover(root->right, false, true);
            return min(noCam, rootCam);
        }

        if (root->val != 0) return root->val;
        auto rootCam = 1 + minCameraCover(root->left, false, true) + minCameraCover(root->right, false, true);
        auto leftCam = root->left == nullptr ? INT_MAX : minCameraCover(root->left, true, true)
            + minCameraCover(root->right, false, false);
        auto rightCam = root->right == nullptr ? INT_MAX : minCameraCover(root->left, false, false)
            + minCameraCover(root->right, true, true);

        return root->val = min({ rootCam, leftCam, rightCam });
    }
};




class Solution {
public:
    int minCameraCover(TreeNode* root) {
        auto t = helper(root);
        return min(get<1>(t), get<2>(t));
    }
	
    tuple<int, int, int> helper(TreeNode *root) {
        if (!root) {
            return {0, 0, 1}; 
            //not_covered 表示当前前没有cover, 但是它的children 都cover
             //covered 表示这个点cover 可能 2222没有camera, 
            //parent_covered 表示node 被cover, 且有camera
        }
        int left_not_covered, left_covered, left_parent_covered;
        tie(left_not_covered, left_covered, left_parent_covered) = helper(root->left);
        int right_not_covered, right_covered, right_parent_covered;
        tie(right_not_covered, right_covered, right_parent_covered) = helper(root->right);
        return {left_covered + right_covered, 
                min(left_not_covered + right_not_covered + 1,
                    min(left_parent_covered + right_covered, left_covered + right_parent_covered)), 

                min(left_not_covered, left_covered) + min(right_not_covered, right_covered) + 1};
    }
};





/*


        比如  括号里(第一个是subNodesCovered, 第二个是coveredNoCamera, 第三个是coveredCamera)

              0 (2, 2, 3)
          /         \
        0(MAX,1, 1)   0 (1, 1 ,2)
     /                  \ 
    0(0,MAX,1)            0 (MAX,1,1)
 max noCamera 不可以          \ 
                             0(0,MAX, 1)


 */
class Solution {
public:
    
   int res = 0;
    int minCameraCover(TreeNode* root) {
        auto t = dfs(root);
        return min(get<1>(t), get<2>(t));
    }

    tuple<int,int,int> dfs(TreeNode* root) {
        if (!root) return {0,0,9999999};// using Integer.MAX will overflow, 表示不可能的情况
        int left_subNodesCovered, left_coveredNoCamera, left_coveredCamera;
        tie(left_subNodesCovered, left_coveredNoCamera, left_coveredCamera) =
            dfs(root->left);
        
        
        int right_subNodesCovered, right_coveredNoCamera, right_coveredCamera;
        tie(right_subNodesCovered, right_coveredNoCamera, right_coveredCamera) =
            dfs(root->right);
        
        int lMin = min(left_coveredNoCamera, left_coveredCamera);
        int rMin = min(right_coveredNoCamera, right_coveredCamera);
        
        
        int subNodesCovered = left_coveredNoCamera + right_coveredNoCamera;
        int coveredNoCamera = min(left_coveredCamera + rMin,
                                  right_coveredCamera + lMin);
        int coveredCamera = 
                 min({left_subNodesCovered, left_coveredNoCamera, left_coveredCamera}) 
                + min({right_subNodesCovered, right_coveredNoCamera, right_coveredCamera}) + 1;
        return {subNodesCovered, coveredNoCamera, coveredCamera};
    }
};