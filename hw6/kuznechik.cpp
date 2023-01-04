#include <iostream>
#include <vector>

std::pair<int32_t, int32_t> get_next_jump(
        std::vector<int32_t>& coins, int32_t beg, int32_t end
        ) {
    std::pair<int32_t, int32_t> positive(beg, INT32_MAX);
    std::pair<int32_t, int32_t> max_negative(beg, INT32_MIN);
    for (int i = beg; i < end; i++) {
        if (coins[i] > 0) {
            positive.first = i;
            positive.second = coins[i];
            return positive;
        }
        if (coins[i] <= 0 and coins[i] >= max_negative.second) {
            max_negative.first = i;
            max_negative.second = coins[i];
        }
    }
    return (positive.second != INT32_MAX) ? positive : max_negative;
}

void print_optimal_way(std::vector<int32_t>& coins, int32_t k, int32_t n) {
    int64_t sum_coins = coins[0];
    std::vector<int32_t> way;
    std::pair<int32_t, int32_t> cur_pair;
    int i = 1;
    way.push_back(i);

    while (i < n) {
        if (i + k < n) {
            cur_pair = get_next_jump(coins, i, i + k);
        }
        else {
            cur_pair = get_next_jump(coins, i, n);
        }

        i = cur_pair.first + 1;
        way.push_back(i);
        sum_coins += cur_pair.second;
    }

    std::cout << sum_coins << '\n';
    std::cout << way.size() - 1 << '\n';
    for (auto const & el : way) {
        std::cout << el << ' ';
    }
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int32_t n;
    int32_t k;
    int32_t tmp;
    std::cin >> n >> k;
    std::vector<int32_t> coins(n);

    for(size_t i = 1; i < n - 1; i++) {
        std::cin >> tmp;
        coins[i] = tmp;
    }

    print_optimal_way(coins, k, n);

    return 0;
}
