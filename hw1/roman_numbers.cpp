#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

std::map<char, int> ROMAN_NUMS {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50}
};

int roman_to_int(std::string s_dig) {
    int dig = 0;
    for (int i = 0; i < s_dig.size() - 1; i++) {
        if (ROMAN_NUMS[s_dig[i]] < ROMAN_NUMS[s_dig[i + 1]]) {
            dig -= ROMAN_NUMS[s_dig[i]];
        }
        else {
            dig += ROMAN_NUMS[s_dig[i]];
        }
    }
    dig += ROMAN_NUMS[s_dig[s_dig.size() - 1]];
    return dig;
}

std::string int_to_roman(int dig) {
    std::string res_dig;
    std::map<int, std::string> roman_data {
            {0, ""},
            {1, "I"},
            {2, "II"},
            {3, "III"},
            {4, "IV"},
            {5, "V"},
            {6, "VI"},
            {7, "VII"},
            {8, "VIII"},
            {9, "IX"},
            {10, "X"},
            {20, "XX"},
            {30, "XXX"},
            {40, "XL"},
            {50, "L"}
    };
    int f_dig = dig / 10;
    int s_dig = dig % 10;
    return roman_data[f_dig * 10] + roman_data[s_dig];
}

void get_sorted_kings(std::vector<std::string> &kings) {
    std::vector<std::pair<std::string, int>> sort_kings;
    std::string name;
    int num;
    std::string roman_num;
    int last_space_pos;
    for (auto & king : kings) {
        last_space_pos = king.find_last_of(' ');
        name = king.substr(0, last_space_pos);
        num = roman_to_int(king.substr(last_space_pos + 1));
        sort_kings.emplace_back(name, num);
    }

    std::sort(sort_kings.begin(), sort_kings.end());

    for (int i = 0; i < sort_kings.size(); i++) {
        name = sort_kings[i].first;
        roman_num = int_to_roman(sort_kings[i].second);
        kings[i] = name + " " + roman_num;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector<std::string> kings;
    std::string king;
    std::getline(std::cin, king);
    for (int i = 0; i < n; i++) {
        std::getline(std::cin, king);
        kings.push_back(king);
    }

    get_sorted_kings(kings);

    for (auto king : kings) {
        std::cout << king << '\n';
    }

    return 0;
}