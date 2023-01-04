#include <iostream>
#include <cmath>

bool func(int n, int first_printer, int second_printer, int64_t time) {
    int faster_printer = std::min(first_printer, second_printer);
    time = time - faster_printer;

    int64_t first_scan = floor((double)time / first_printer);
    int64_t second_scan = floor((double)time / second_printer);

    return first_scan + second_scan + 1 >= n;
}

int64_t get_min_time(int n, int x, int y) {
    int64_t l = 0;
    int64_t r = (int64_t)n * (x + y);
    int64_t mid;
    while(l < r - 1) {
        mid = (l + r) / 2;
        if (func(n, x, y, mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, x, y;
    std::cin >> n >> x >> y;

    int res = get_min_time(n, x, y);
    std:: cout << res;

    return 0;
}