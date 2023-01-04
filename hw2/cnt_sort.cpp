#include <iostream>
#include <vector>

int get_max(std::vector<int>& nums) {
    int max = nums[0];
    for (int i = 0; i < nums.size(); i++) {
        if (max < nums[i])
            max = nums[i];
    }
    return max;
}

void print_res(std::vector<int>& cnt) {
    for (int i = 0; i < cnt.size(); i++) {
        if (cnt[i] != 0) {
            for (int _ = 0; _ < cnt[i]; _++) {
                std::cout << i << ' ';
            }
        }
    }
}

void cnt_sort(std::vector<int>& nums) {
    int m = get_max(nums);
    std::vector<int> cnt(m + 1);

    for (int i = 0; i < nums.size(); i++) {
        cnt[nums[i]]++;
    }

    print_res(cnt);
}

int main() {
    int tmp;
    std::vector<int> nums;
    while (std::cin >> tmp) {
        nums.push_back(tmp);
    }

    cnt_sort(nums);

    return 0;
}