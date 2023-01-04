#include <iostream>
#include <vector>

void merge(std::vector<int> l, std::vector<int> r, std::vector<int> &nums) {
    int size_l = l.size();
    int size_r = r.size();
    int i = 0;
    int j = 0;

    while (i + j < size_l + size_r) {
        if (j == size_r || (i < size_l && l[i] < r[j])) {
            nums[i + j] = l[i];
            i++;
        }
        else{
            nums[i + j] = r[j];
            j++;
        }
    }
}

void merge_sort(std::vector<int> &nums) {
    if (nums.size() == 1) {
        return;
    }
    int centre_index = nums.size() / 2;
    auto l = std::vector<int>(nums.begin(), nums.begin() + centre_index);
    auto r = std::vector<int>(nums.begin() + centre_index, nums.end());

    merge_sort(l);
    merge_sort(r);

    merge(l, r, nums);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector<int> nums;
    int num;
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        nums.push_back(num);
    }

    merge_sort(nums);

    for (auto x : nums) {
        std::cout << x << '\n';
    }
    return 0;
}