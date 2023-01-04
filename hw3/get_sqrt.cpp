#include <iostream>
#include <cmath>

const double EPS = 1e-6;

double funct(double x) {
    return sqrt(x) + x * x;
}

double bin_search(double c) {
    double l = 0.0;
    double r = 1e10;

    int steps = log2(double(r - l) / EPS);
    for (int _ = 0; _ < steps; _++) {
        double m = double(l + r) / 2;
        if (funct(m) < c) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    double c;
    std::cin >> c;
    double res = bin_search(c);

    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << res;

    return 0;
}



