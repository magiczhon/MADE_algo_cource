#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int32_t levenshtein_distance(std::string str1, std::string str2) {
    int32_t n = str1.size() + 1;
    int32_t m = str2.size() + 1;
    std::vector<std::vector<int32_t>> dp(n, std::vector<int32_t>(m));
    for (size_t i = 0; i < n; i++) {
        dp[i][0] = i;
    }
    for (size_t j = 0; j < m; j++) {
        dp[0][j] = j;
    }
    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < m; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = std::min(
                        std::min(dp[i - 1][j], dp[i][j - 1]),
                        dp[i - 1][j - 1]) + 1;
            }
        }
    }
    return dp[n - 1][m - 1];
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string str1, str2;
    std::cin >> str1 >> str2;

    int32_t result = levenshtein_distance(str1, str2);
    std::cout << result;

    return 0;
}
