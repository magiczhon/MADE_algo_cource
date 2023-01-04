#include <iostream>
#include <vector>

uint64_t count_of_inv = 0;

void merge(std::vector<uint32_t> l, std::vector<uint32_t> r, std::vector<uint32_t> &nums) {
    uint32_t size_l = l.size();
    uint32_t size_r = r.size();
    uint32_t i = 0;
    uint32_t j = 0;

    while (i + j < size_l + size_r) {
        if (j == size_r || (i < size_l && l[i] <= r[j])) {
            nums[i + j] = l[i];
            i++;
        }
        else {
            count_of_inv += size_l - i;
            nums[i + j] = r[j];
            j++;
        }
    }
}

void merge_sort(std::vector<uint32_t> &nums) {
    if (nums.size() == 1) {
        return;
    }
    int centre_index = nums.size() / 2;
    auto l = std::vector<uint32_t>(nums.begin(), nums.begin() + centre_index);
    auto r = std::vector<uint32_t>(nums.begin() + centre_index, nums.end());

    merge_sort(l);
    merge_sort(r);

    merge(l, r, nums);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint32_t n;
    std::cin >> n;

    std::vector<uint32_t> nums;
    uint32_t num;
    for (uint32_t i = 0; i < n; i++) {
        std::cin >> num;
        nums.push_back(num);
    }

    merge_sort(nums);

    std::cout << count_of_inv;

    return 0;
}
