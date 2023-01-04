#include <iostream>
#include <string>
#include <vector>

std::vector<int> z_funct(std::string s) {
    std::vector<int> z(s.size());
    int left = 0;
    int right = 0;
    for (int i = 1; i < s.size(); i++){
        z[i] = std::max(0, std::min(right - i, z[i - left]));
        while (i + z[i] < s.size() and s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}

int main() {
    std::string s;
    std::cin >> s;
    auto z = z_funct(s);
    for (int i = 1; i < z.size(); i++) {
        std::cout << z[i] << ' ';
    }
    return 0;
}