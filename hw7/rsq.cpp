#include <iostream>
#include <vector>
#include <algorithm>

int64_t f(int64_t i) {
    return i & (i + 1);
}

int64_t s(int64_t i) {
    return i | (i + 1);
}

int64_t get(int64_t i, std::vector<int64_t> const& T) {
    int64_t res = 0;
    for (int64_t j = i; j >= 0; j = f(j) - 1) {
        res += T[j];
    }
    return res;
}

int64_t rsq(int64_t l, int64_t r, std::vector<int64_t> const& T) {
    if (l == 0) {
        return get(r, T);
    }
    return get(r, T) - get(l - 1, T);

}

void add(int64_t i,
         int64_t d,
         std::vector<int64_t>& nums,
         std::vector<int64_t>& T
         ) {
    //=============================
//    if (nums.size() == 1)
//        nums[i] += d;
    //=============================
    for (int64_t j = i; j < nums.size(); j = s(j)) {
        T[j] += d;
    }
}

void set(int64_t i,
         int64_t x,
         std::vector<int64_t>& nums,
         std::vector<int64_t>& T
         ) {
    int64_t d = x - nums[i];
    nums[i] = x;
    add(i, d, nums, T);
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n;
    std::cin >> n;
    int64_t tmp;
    std::vector<int64_t> nums(n);
    std::vector<int64_t> T(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> tmp;
        nums[i] = tmp;
    }

    for (size_t i = 0; i < n; i++) {
        add(i, nums[i], nums, T);
    }

    std::string operation;
    int64_t res;
    int64_t val1, val2;


    while(std::cin >> operation >> val1 >> val2) {
        if (operation == "/")
            break;
        if (operation == "sum") {
            res = rsq(val1 - 1, val2 - 1, T);
            std::cout << res << '\n';
        }
        if (operation == "set") {
            set(val1 - 1, val2, nums, T);
        }
    }
    return 0;
}

// 5
// 1 2 3 4 5
// sum 2 5
// sum 1 5
// sum 1 4
// sum 2 4
// set 1 10
// set 2 3
// set 5 2
// sum 2 5
// sum 1 5
// sum 1 4
// sum 2 4
// / 2 3

