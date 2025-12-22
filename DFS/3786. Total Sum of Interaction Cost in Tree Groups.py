class Solution:
    def interactionCosts(self, n: int, edges: List[List[int]], group: List[int]) -> int:
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        group_dic = defaultdict(list)
        for i, g in enumerate(group):
            group_dic[g].append(i)

        tot = 0 

        for g, node_list in group_dic.items():
            in_group = [0 for i in range(n)]

            for node in node_list:
                in_group[node] = 1 

            total_in = len(node_list)

            def dfs(cur, par):
                count = in_group[cur]
                for nxt in tree[cur]:
                    if nxt == par:
                        continue 
                    nxt_count = dfs(nxt, cur)
                    nonlocal tot
                    tot += nxt_count * (total_in - nxt_count)
                    
                    count += nxt_count 
                return count 

            dfs(node_list[0], -1)
        return tot

                