#include <iostream>
#include <vector>

std::vector<std::pair<std::string, int>> cnt_sort(std::vector<std::pair<std::string, int>> lines, int radix) {
    std::vector<int> cnt(26);
    for (int i = 0; i < lines.size(); i++) {
        cnt[lines[i].first[radix] - 'a']++;
    }

    std::vector<int> p(26);
    for(int i = 1; i < 26; i++) {
        p[i] = p[i - 1] + cnt[i - 1];
    }

    std::vector<std::pair<std::string, int>> sort_lines(lines.size());
    for (int i = 0; i < lines.size(); i++) {
        sort_lines[p[lines[i].first[radix] - 'a']++] = lines[i];
    }

    return sort_lines;
}

void radix_sort(std::vector<std::pair<std::string, int>> &lines, int k, int m) {
    for (int i = 0; i < k; i++) {
        lines = cnt_sort(lines, m - i);
    }

    for (const auto &line : lines) {
        std::cout << line.first << '\n';
    }
}

int main()
{
    int n;
    int m;
    int k;
    std::cin >> n;
    std::cin >> m;
    std::cin >> k;
    std::string tmp;
    std::vector<std::pair<std::string, int>> lines;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        lines.emplace_back(std::make_pair(tmp, i));
    }

    radix_sort(lines, k, m - 1);

    return 0;
}