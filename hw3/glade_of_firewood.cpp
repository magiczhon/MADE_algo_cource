#include <iostream>
#include <cmath>

const double EPS = 1e-9;

double funct(double point, double bound,int v_field, int v_forest) {
    double dist_to_bound = sqrt(pow(1 - bound, 2) + pow(point, 2));
    double dist_to_firewood = sqrt(pow(bound, 2) + pow(1 - point, 2));
    return dist_to_bound / v_field + dist_to_firewood / v_forest;
}

double get_min_time(int v_field, int f_forest, double bound) {
    double l = 0.0;
    double r = 1.0;

    int steps = log2(double(r - l) / EPS);

    for (int _ = 0; _ < steps; _++) {
        double m1 = l + double(r - l) / 3;
        double m2 = l + 2 * double(r - l) / 3;

        if (funct(m1, bound, v_field, f_forest) <
            funct(m2, bound, v_field, f_forest)) {
            r = m2;
        }
        else {
            l = m1;
        }
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int v_field, v_forest;
    std::cin >> v_field >> v_forest;
    double bound;
    std::cin >> bound;
    double res = get_min_time(v_field, v_forest, bound);

    std::cout.setf(std::ios::fixed);
    std::cout.precision(5);
    std::cout << res;

    return 0;
}