#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int32_t MOD = 16714589;
const uint32_t A1 = 23;
const uint32_t B1 = 21563;

const uint32_t A2 = 17;
const uint32_t B2 = 751;
const uint32_t C2 = 2;

const uint32_t A3 = 13;
const uint32_t B3 = 593;
const uint32_t C3 = 5;

std::vector<int32_t> build_array(int32_t n, int32_t seed) {
    std::vector<int32_t> array(n);
    array[0] = seed % MOD;
    for (size_t i = 1; i < n; i++) {
        array[i] = (A1 * array[i - 1] + B1 + MOD) % MOD;
    }
    return array;
}

std::vector<std::vector<int32_t>> build_sparse_table(
        std::vector<int32_t>const& a,
        uint32_t n
        ) {
    uint32_t lg_n = (uint32_t)std::log2(n) + 1;
    std::vector<std::vector<int32_t>> sparse_table(n, std::vector<int32_t> (lg_n));
    for (size_t i = 0; i < n; i++) {
        sparse_table[i][0] = a[i];
    }

    for (size_t k = 1; k < lg_n; k++) {
        for (size_t l = 0; l < n; l++) {
            sparse_table[l][k] = std::min(
                    sparse_table[l][k - 1],
                    sparse_table[std::min(l + (1 << (k - 1)), n - 1)][k - 1]);
        }
    }

    return sparse_table;
}

uint32_t rmq(
        std::vector<std::vector<int32_t>>const& sparse_table,
        std::vector<int32_t>const& k_vec,
        int32_t u,
        int32_t v
        ) {
    if (u > v) {
        std::swap(u, v);
    }
    uint32_t k;
    k = k_vec[v - u];
    return std::min(sparse_table[u][k], sparse_table[v - (1 << k) + 1][k]);
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int32_t n;
    int32_t m;
    int32_t a;
    std::cin >> n >> m >> a;

    int32_t u;
    int32_t v;
    std::cin >> u >> v;

    std::vector<int32_t> a_array = build_array(n, a);

    auto sparse_table = build_sparse_table(a_array, n);

    std::vector<int32_t> k(n);
    k[0] = 0;
    for (size_t i = 1; i < n; i++) {
        k[i] = k[i - 1];
        if ((1 << (k[i] + 1)) <= i) {
            k[i]++;
        }
    }

    uint32_t result = rmq(sparse_table, k, u - 1, v - 1);
    for (size_t i = 1; i < m; i++) {
        u = ((A2 * u + B2 + result + C2 * i + n) % n) + 1;
        v = ((A3 * v + B3 + result + C3 * i + n) % n) + 1;
        result = rmq(sparse_table, k, u - 1, v - 1);
    }
    std::cout << u << ' ' << v << ' ' << result;

    return 0;
}
