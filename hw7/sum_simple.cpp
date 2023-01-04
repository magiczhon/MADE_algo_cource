#include <iostream>
#include <vector>
#include <algorithm>

const int32_t MOD_A = (1 << 16);
const int32_t MOD_B = (1 << 30);

std::vector<uint32_t> build_array(
        int32_t n, int32_t x, int32_t y, int32_t seed, int32_t mod) {
    std::vector<uint32_t> array(n);
    array[0] = seed % mod;
    for (size_t i = 1; i < n; i++) {
        array[i] = (x * array[i - 1] + y + mod) % mod;
    }
    return array;
}

std::vector<uint64_t> build_sum_array(int32_t n, std::vector<uint32_t>& array) {
    std::vector<uint64_t> sum_array(n);
    sum_array[0] = array[0];
    for (size_t i = 1; i < n; i++) {
        sum_array[i] = sum_array[i - 1] + array[i];
    }
    return sum_array;
}

uint64_t rsq(int32_t l, int32_t r, std::vector<uint64_t>& sum_array, int32_t n) {
    if (l == 0) {
        return sum_array[r];
    }
    return sum_array[r] - sum_array[l - 1];
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int32_t n;
    int32_t x;
    int32_t y;
    int32_t a0;
    std::cin >> n >> x >> y >> a0;
    std::vector<uint32_t> a_array = build_array(n, x, y, a0, MOD_A);

    int32_t m;
    int32_t z;
    int32_t t;
    int32_t b0;
    std::cin >> m >> z >> t >> b0;

    if (m == 0) {
        std::cout << 0;
        return 0;
    }

    int32_t size_m = 2 * m;
    std::vector<uint32_t> b_array = build_array(size_m, z, t, b0, MOD_B);
    std::vector<uint32_t> c_array(size_m);
    for (size_t i = 0; i < size_m; i++) {
        c_array[i] = (b_array[i] + n) % n;
    }

    int32_t l;
    int32_t r;
    std::vector<uint64_t> sum_array = build_sum_array(n, a_array);
    uint64_t sum = 0;
    for (size_t i = 0; i < m; i++) {
        l = std::min(c_array[2 * i], c_array[2 * i + 1]);
        r = std::max(c_array[2 * i], c_array[2 * i + 1]);
        sum += rsq(l, r, sum_array, n);
    }
    std::cout << sum;

    return 0;
}
