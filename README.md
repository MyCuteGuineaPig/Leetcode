

## Depth-First Search

|Title | Time | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [112. Path Sum](https://leetcode.com/problems/path-sum/description/) | O(n) |	O(h)	| Easy |  write in one function |
| [113	Path Sum II](https://leetcode.com/problems/path-sum-ii/) |	O(n)	| O(h) |	Medium |	|
| [199	Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)	| O(n)	| O(h)	| Medium		 |  |
| [200	Number of Islands](https://leetcode.com/problems/binary-tree-right-side-view/description/)	| O(m * n) |	O(m * n) |	Medium		|   |
| [236	Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/)	|	O(n) |	O(h) |	Medium	| DFS left, right 如果left，right 各含有p,q 返回 current root， 否则返回left or right 同时含有p,q的那个 |
| [257	Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/description/) | 	O(n * h) | O(h) | Easy 	| <ul><li>可以用queue，BFS 扫每个level，返回最右侧的 </li> <li>也可以用加上一个null pointer在 每个levle queue 最后面，一旦返回null，知道这层扫完了，append last number </li></ul>|
| [282	Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)	| O(4^n) | O(n) | Hard | DFS，需要cv (cumulative sum), pv(previous sum), pos 到现在process的index，注意: <ul><li>现在是'\*', cv = cv - pv + p\*n, pv = pv\*n </li> <li>现在是'-', cv = cv - pv + n, pv = -n </li></ul>|
| [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/description/)	| O(C(n, c))	| O(c) | Hard | <ul><li> DFS: 开始DFS前记录left_removed，right_removed, 这样可以保证删除的parenthese 最短，再记录pair，'(' 时候pair+1, ')'时候pair-1， pair最后等于0， 表示valid</li> <li>BFS: 用unordered_set 记录所有被visited的string，每次取一次char修改 push到queue</li></ul>|
| [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/)	| O(m * n) | O(m * n) | Hard | DFS: 历遍上下左右四个点，避免到重复点的方法: memoization 记录到这点最多increase path element数 |
