#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string get_backward_way(
        std::vector<std::vector<int64_t>> dp, int32_t n, int32_t m
        ) {
    size_t i = n - 1;
    size_t j = m - 1;
    std::string way;
    while(i != 1 or j != 1) {
        if (dp[i - 1][j] > dp[i][j - 1]) {
            way += "D";
            i--;
        }
        else {
            way += "R";
            j--;
        }
    }
    way += "\n";
    std::reverse(way.begin(), way.end());
    return way;
}

std::pair<int64_t, std::string> print_optimal_way(
        std::vector<std::vector<int16_t>> coins, int32_t n, int32_t m
        ) {
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(m));
    for (size_t i = 1; i < n; i++) {
        dp[i][0] = INT16_MIN;
    }
    for (size_t j = 1; j < m; j++) {
        dp[0][j] = INT16_MIN;
    }
    dp[1][1] = coins[1][1];
    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < m; j++) {
            if (i > 1 or j > 1) {
                if(dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] += dp[i - 1][j] + coins[i][j];
                }
                else {
                    dp[i][j] += dp[i][j - 1] + coins[i][j];
                }
            }
        }
    }
    std::string way = get_backward_way(dp, n, m);
    return {dp[n - 1][m - 1], way};
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int32_t n;
    int32_t m;
    std::cin >> n >> m;
    n++;
    m++;
    std::vector<
            std::vector<int16_t>
            > coins(n, std::vector<int16_t>(m, INT16_MIN));
    int16_t coin;
    for(size_t i = 1; i < n; i++) {
        for(size_t j = 1; j < m; j++) {
            std::cin >> coin;
            coins[i][j] = coin;
        }
    }

    std::pair<int64_t, std::string> res = print_optimal_way(coins, n, m);

    std::cout << res.first << res.second;
    return 0;
}
