#include <iostream>
#include <string>
#include <vector>

const int64_t SHIFT = 'a' - 1;
const int64_t M = 1e9 ;
const int64_t p = 77232917;

int64_t get_hash(std::vector<int64_t>& hash, std::vector<int64_t>& pow, int l, int r) {
    if (l == 0)
        return hash[r];
    return (M + hash[r] - (hash[l - 1] * pow[r - l + 1]) % M) % M;
}

std::string eq_substr(int l1, int r1,
                      int l2, int r2,
                      std::vector<int64_t>& hash,
                      std::vector<int64_t>& pow) {
    if (r1 - l1 != r2 - l2) {
        return "No\n";
    }

    int64_t hash_substr1 = get_hash(hash, pow, l1, r1);
    int64_t hash_substr2 = get_hash(hash, pow, l2, r2);

    if (hash_substr1 == hash_substr2) {
        return "Yes\n";
    }
    return "No\n";
}

int main() {
    std::string s;
    int m;
    std::cin >> s >> m;
    int l1, r1, l2, r2;
    std::string ans;
    std::vector<int64_t> hash(s.size());
    std::vector<int64_t> pow(s.size(), 1);
    hash[0] = s[0] - SHIFT;
    for (int i = 1; i < s.size(); i++) {
        hash[i] = ((hash[i - 1] * p) % M + s[i] - SHIFT) % M;
        pow[i] = (pow[i - 1] * p) % M;
    }
    for (int _ = 0; _ < m; _++) {
        std::cin >> l1 >> r1 >> l2 >> r2;
        ans = eq_substr(l1 - 1, r1 - 1, l2 - 1, r2 - 1, hash, pow);
        std::cout << ans;
    }
    return 0;
}