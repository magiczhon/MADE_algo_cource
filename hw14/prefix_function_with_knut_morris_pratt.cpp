#include <iostream>
#include <string>
#include <vector>

std::vector<int> p_funct(const std::string& s) {
    std::vector<int> p(s.size());
    for (int i = 1; i < s.size(); i++) {
        int k = p[i - 1];
        while (k > 0 and s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

void knut_morris_pratt(const std::string& p, const std::string& t) {
    std::string s = p + "#" + t;
    auto p_funct_array = p_funct(s);
    int p_len = p.size();
    int offset = 2 * p_len - 1;
    int count_p_substr = 0;
    std::vector<int> begin_position_of_p_substr;

    for (int i = 1; i < p_funct_array.size(); i++) {
        if (p_funct_array[i] == p_len) {
            count_p_substr++;
            begin_position_of_p_substr.push_back(i - offset);
        }
    }

    std::cout << count_p_substr << '\n';
    for (const auto& position : begin_position_of_p_substr) {
        std::cout << position << ' ';
    }
}

int main() {
    std::string p, t;
    std::cin >> p >> t;
    knut_morris_pratt(p, t);
    return 0;
}