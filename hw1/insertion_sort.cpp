#include <iostream>
#include <vector>

std::vector<int> insertion_sort(std::vector<int> nums) {
    for (int i = 1; i < nums.size(); i++) {
        int j = i;
        while (j > 0 && nums[j - 1] > nums[j]) {
            std::swap(nums[j - 1], nums[j]);
            j--;
        }
    }
    return nums;
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

    nums = insertion_sort(nums);

    for (auto x : nums) {
        std::cout << x << '\n';
    }
    return 0;
}