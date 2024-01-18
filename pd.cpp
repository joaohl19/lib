
// Memoization
// TIME -> O(N)
// SPACE -> O(N)(STACK) + O(N)(ARRAY)
int dp_frog_k_Jump_memoization(int n, int dp[], int weights[], int k){
    if(n == 0) return 0;
    if(dp[n] != -1) return dp[n];
    int ans = INT_MAX;
    for(int i = 1; i <= k; i++){
        if(n - i >= 0){
            int jump = abs(weights[n] - weights[n - i]) +  dp_frog_k_Jump_memoization(n - i, dp, weights, k);
            ans = min(ans, jump);
        }
    }
    return dp[n] = ans;
}

// Tabulation
int dp_frog_k_Jump_tabulation(int n, int dp[], int weights[], int k){
    dp[0] = 0;
    for(int i = 1; i <= n; i++){
        int ans = INT_MAX;
        for(int j = 1; j <= k; j++){
            if(i - j >= 0){
                int jump = dp[i - j] + abs(weights[i] - weights[i - j]);
                ans = min(ans, jump);
            }
            dp[i] = ans;
        }
    }
    return dp[n];
}
