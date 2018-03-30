"""
This is equal to find nodes which doesn’t lead to a circle in any path.
We can solve it by walking along the path reversely.

Find nodes with out degree 0, they are terminal nodes, we remove them from graph and they are added to result
For nodes who are connected terminal nodes, since terminal nodes are removed, we decrease in-nodes’ out degree by 1 and if its out degree equals to 0, it become new terminal nodes
Repeat 2 until no terminal nodes can be found.


"""

class Solution:
    def eventualSafeNodes(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: List[int]
        """
        n = len(graph)
        out_degrees = [0]*n
        in_nodes = collections.defaultdict(list)
        queue = []
        for i in range(n):
            out_degrees[i] = len(graph[i])
            if len(graph[i]) == 0 : queue.append(i)
            for j in graph[i]: in_nodes[j].append(i)
        for term_node in queue:
            for in_node in in_nodes[term_node]:
                out_degrees[in_node]-=1
                if out_degrees[in_node] == 0: queue.append(in_node)
        return sorted(queue)
