#include <iostream>
#include <vector>

int bin_search(int l, int r, std::vector<int>& array, int query) {
    if (l == r - 1) {
        if (std::abs(query - array[l]) <= std::abs(query - array[r])) {
            return array[l];
        }
        else {
            return array[r];
        }
    }

    int m = (l + r) / 2;

    if (array[m] == query) {
        return array[m];
    }
    if (array[m] < query) {
        bin_search(m, r, array, query);
    }
    else {
        bin_search(l, m, array, query);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    int k;
    std::cin >> n;
    std::cin >> k;

    std::vector<int> array(n);

    int tmp;
    int res;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        array[i] = tmp;
    }

    int query;
    for (int i = 0; i < k; i++) {
        std::cin >> query;
        if (query <= array[0]) {
            res = array[0];
        }
        else if (query >= array[n - 1]) {
            res = array[n - 1];
        }
        else {
            res = bin_search(0, n, array, query);
        }
        std::cout << res << '\n';
    }
    return 0;
}