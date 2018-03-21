# Leetcode


# Depth-First Search

|Title | Time | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [112. Path Sum](https://leetcode.com/problems/path-sum/description/) | O(n) |	O(h)	| Easy |  write in one function |
| 113	Path Sum II |	O(n)	| O(h) |	Medium |	|
| 199	Binary Tree Right Side View	| O(n)	| O(h)	| Medium		 |  |
| 200	Number of Islands	| O(m * n) |	O(m * n) |	Medium		|   |
| 236	Lowest Common Ancestor of a Binary Tree	|	O(n) |	O(h) |	Medium	| DFS left, right 如果left，right 各含有p,q 返回 current root， 否则返回left or right 同时含有p,q的那个 |
| 257	Binary Tree Paths | 	O(n * h) | O(h) | Easy 	| 可以用queue，BFS 扫每个level，返回最右侧的，也可以用加上一个null pointer在 每个levle queue 最后面，一旦返回null，知道这层扫完了，append last number |
| 282	Expression Add Operators	| O(4^n) | O(n) | Hard | DFS，需要cv (cumulative sum), pv(previous sum), pos 到现在process的index，注意如果是乘号的话, cv = cv - pv + p*vn, pv = pv*n |

