#include <iostream>
#include <vector>

std::vector<int> get_cnt(std::string str) {
    std::vector<int> cnt(26);
    for (int i = 0; i < str.size(); i++) {
        cnt[str[i] - 'a']++;
    }
    return cnt;
}

bool le_cnt(std::vector<int> cnt1, std::vector<int> cnt2) {
    for (int i = 0; i < cnt1.size(); i++) {
        if (cnt1[i] > cnt2[i]) {
            return false;
        }
    }
    return true;
}

long long int get_count_substr(std::string main_str, std::string cards, int count_cards) {
    auto cards_cnt = get_cnt(cards);
    auto main_str_cnt = get_cnt(main_str);
    int it1 = 0;
    int it2 = 0;
    long long int res = 0;
    auto size_main_line = main_str.size();

    auto substr_cnt = std::vector<int>(26);
    substr_cnt[main_str[it2] - 'a']++;
    while (it2 < size_main_line) {
        if (le_cnt(substr_cnt, cards_cnt)) {
            res += it2 - it1 + 1;
            if (it2 - it1 < count_cards) {
                it2++;
                if (it2 < size_main_line) {
                    substr_cnt[main_str[it2] - 'a']++;
                }
            }
            else {
                substr_cnt[main_str[it1] - 'a']--;
                it1++;
            }
        }
        else {
            if (it2 - it1 > 0) {
                substr_cnt[main_str[it1] - 'a']--;
                it1++;
            }
            else {
                substr_cnt[main_str[it1] - 'a']--;
                it1++;
                it2++;
                if (it2 < size_main_line) {
                    substr_cnt[main_str[it2] - 'a']++;
                }
            }
        }
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    int m;
    std::string main_str;
    std::string substr;
    std::cin>> n;
    std::cin >> m;
    std::cin >> main_str;
    std::cin >> substr;

    long long int res = get_count_substr(main_str, substr, m);
    std::cout << res;

    return 0;
}