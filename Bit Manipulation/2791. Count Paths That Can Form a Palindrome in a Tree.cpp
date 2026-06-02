/*

1. The Core Idea: Bitmasking for PalindromesA string can be rearranged into a palindrome 
if and only if at most one character has an odd count.

"aabb" 'a': 2, 'b': 2 (0 odd counts)   Valid ("abba")
"aabbc" 'a': 2, 'b': 2, 'c': 1 (1 odd count) Valid
"aabbcd" $\rightarrow$ 'a': 2, 'b': 2, 'c': 1, 'd': 1 Invalid
    - Since we only care whether a character's count is even or odd, 
    we can use a single integer as a bitmask of 26 bits (one for each lowercase letter).
    
A 0 bit means the character appears an even number of times.
A 1 bit means the character appears an odd number of times.
We toggle a bit using the XOR operator (^). If we encounter 'c' (the 2nd bit), we do mask ^ (1 << 2).



Finding the path between any two arbitrary nodes u and v in a tree is usually expensive. 

However, trees have a beautiful property: the path from u to v can be represented by 
combining the path from the root to u and the root to v.
When you go from the root to u and root to v, 
the overlapping edges (from the root to their Lowest Common Ancestor) are traversed twice.

Because x xor x = 0 (XORing something with itself cancels it out), 
the characters on the shared edges naturally erase themselves! 

Therefore:$ Mask(u, v) = Mask(root, u)  xor Mask(root, v), 

This is a massive shortcut. Instead of calculating masks between every pair, 
we only need to calculate the mask from the root to every individual node.


dp[i] stores the bitmask representing the path from the root (node 0) to node i.

It uses memoization (dynamic programming). 
If dp[i] isn't calculated yet, it recursively finds the mask of its parent, 
and then XORs it with the character on the edge connecting parent[i] and i




for (int i = 0; i < n; i++) {
    int mask = f(dp, parent, s, i);
    
    // Condition 1: Paths with exactly one odd-count character
    //mask ^ (1 << j) 表示只有第  i + 'a' 这个字符的奇偶性不同，其他字符的奇偶性都相同
    for (int j = 0; j < 26; j++)
        res += count.count(mask ^ (1 << j)) ? count[mask ^ (1 << j)] : 0;
        
    // Condition 2: Paths with zero odd-count characters
    res += count[mask]++;
}
As we iterate through each node i, we treat it as the second node v in our (u, v) pair. 

We look backward at all previously processed nodes u to see if they form a valid palindrome path with i.

For the path to be a palindrome, Mask(u, v) must have either all 0s, or exactly one 1

1. Exactly one odd character: We look for a previously seen node u whose mask differs from mask 
    by exactly one bit. We simulate flipping each of the 26 bits (mask ^ (1 << j)) 
    and check our count map to see how many previous nodes had that exact mask.
    
2. Zero odd characters (all even): We look for a previously seen node u that has the exact same mask as 
mask (mask ^ mask = 0). We add count[mask] to our result.

3. Update Map: Finally, 
    count[mask]++ registers the current node's mask into the map so future nodes can pair up with i


*/



class Solution {
public:
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        vector<long>dp(n);
        unordered_map<long, int> cnt; 

        auto dfs = [&](this auto&& dfs, int i) -> long {
            if(i > 0 && dp[i] == 0) {
                dp[i] = dfs(parent[i]) ^ (1<<(s[i]-'a'));
            }
            return dp[i];
        };
        long res = 0;
        for(int i = 0; i < n; ++i){
            long mask = dfs(i);

            // Condition 1: Paths with exactly one odd-count character
            for(int j = 0; j < 26; ++j) {
                res += cnt.count(mask ^ (1 << j)) ? cnt[mask ^ (1 << j)] : 0;
            }

            // Condition 2: Paths with zero odd-count characters
            res += cnt[mask]++;
        }
        return res;
    }
};