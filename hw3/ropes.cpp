#include <iostream>
#include <vector>

bool funct(int d, std::vector<int>& ropes, int k, int n) {
    int home_count = 0;
    for (int i = 0; i < n; i++) {
        home_count += ropes[i] / d;
        if (home_count >= k) {
            return true;
        }
    }
    return false;
}

int get_max_rope(int l, int r, std::vector<int> ropes,int k, int n) {
    while (l < r - 1) {
        int d = (l + r) / 2;
        if (funct(d, ropes, k, n)) {
            l = d;
        } else {
            r = d;
        }
    }
    return l;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    int k;
    std::cin >> n;
    std::cin >> k;

    std::vector<int> ropes(n);
    int tmp;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        ropes[i] = tmp;
    }

    int res = get_max_rope(0, 10000001, ropes, k, n);
    std::cout << res;

    return 0;
}