class Solution {
    public int numOfMinutes(int n, int headID, int[] manager, int[] informTime) {
        int res = 0;
        for (int i = 0; i < n; ++i)
            res = Math.max(res, dfs(i, manager, informTime));
        return res;
    }
    
    public int dfs(int i, int[] manager, int[] informTime) {
        if (manager[i] != -1) {
            informTime[i] += dfs(manager[i], manager, informTime);
            manager[i] = -1;
        }
        return informTime[i];
    }
}


class Solution {
    public int numOfMinutes(final int n, final int headID, final int[] manager, final int[] informTime) {
        final Map<Integer, List<Integer>> graph = new HashMap<>();
        int total = 0;
        for (int i = 0; i < manager.length; i++) {
            int j = manager[i];
            if (!graph.containsKey(j))
                graph.put(j, new ArrayList<>());
            graph.get(j).add(i);
        }
        return dfs(graph, informTime, headID);
    }

    private int dfs(final Map<Integer, List<Integer>> graph, final int[] informTime, final int cur) {
        int max = 0;
        if (!graph.containsKey(cur))
            return max;
        for (int i = 0; i < graph.get(cur).size(); i++)
            max = Math.max(max, dfs(graph, informTime, graph.get(cur).get(i)));
        return max + informTime[cur];
    }
}


class Solution {
    public int numOfMinutes(int n, int headID, int[] manager, int[] informTime) {
        List<Integer>[] graph = new List[n];
        for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();
        for (int i = 0; i < n; i++) if (manager[i] != -1) graph[manager[i]].add(i);
        Queue<int[]> q = new LinkedList<>(); // Since it's a tree, we don't need `visited` array
        q.offer(new int[]{headID, 0});
        int ans = 0;
        while (!q.isEmpty()) {
            int[] top = q.poll();
            int u = top[0], w = top[1];
            ans = Math.max(w, ans);
            for (int v : graph[u]) q.offer(new int[]{v, w + informTime[u]});
        }
        return ans;
    }
}