class Solution {
    public int minTaps(int n, int[] ranges) {
        int []dp = new int[n+1];
        Arrays.fill(dp, n + 2);
        dp[0] = 0;

        for(int i = 0; i<=n; i++){
            int start = Math.max(i - ranges[i], 0);
            int end = Math.min(i + ranges[i], n);
            for(int j = start; j <= end; ++j){
                dp[j] = Math.min(dp[j], dp[start]+1);
            }  
        }
        return dp[n] > n ? -1: dp[n];
    }
}