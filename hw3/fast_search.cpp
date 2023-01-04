#include <iostream>
#include <vector>
#include <algorithm>

int lower_bound(int l, int r, std::vector<int>& array, int x) {
    if (l == r - 1) {
        return r;
    }
    int m = (l + r) / 2;
    if (x <= array[m]) {
        return lower_bound(l, m, array, x);
    }
    else {
        return lower_bound(m, r, array, x);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector<int> array(n);
    int tmp;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        array[i] = tmp;
    }

    std::sort(array.begin(), array.end());

    int k;
    std::cin >> k;
    int r;
    int l;
    for (int i = 0; i < k; i++) {
        std::cin >> l;
        std::cin >> r;
        int l_index = lower_bound(-1, n, array, l);
        int r_index = lower_bound(-1, n, array, r + 1);
        int res = r_index - l_index;
        std::cout << res << '\n';
    }
    return 0;
}