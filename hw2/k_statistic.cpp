#include <iostream>
#include <ctime>
#include <vector>

void split(std::vector<int> &unsort_nums,
           std::vector<int> &left, std::vector<int> &middle, std::vector<int> &right, int median) {
    for (int i = 0; i < unsort_nums.size(); i++) {
        if (unsort_nums[i] < median)
            left.push_back(unsort_nums[i]);
        else if (unsort_nums[i] == median)
            middle.push_back(unsort_nums[i]);
        else if (unsort_nums[i] > median)
            right.push_back(unsort_nums[i]);
    }
}

int find(int k, std::vector<int> &nums) {
    if (nums.size() == 1) {
        int res = nums[0];
        std::cout << res << '\n';
        return res;
    }

    srand(time(NULL));
    int median = nums[rand() % nums.size()];
    std::vector<int> left;
    std::vector<int> middle;
    std::vector<int> right;

    split(nums, left, middle, right, median);

    int m1 = left.size();
    int m2 = left.size() + middle.size();

    if (k < m1) {
        find(k, left);
    }
    else if (k >= m2) {
        find(k - m2, right);
    }
    else {
        int res = middle[0];
        std::cout << res << '\n';
        return res;
    }
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

    int m;
    int i;
    int j;
    int k;
    std::cin >> m;
    for (int _ = 0; _ < m; _++) {
        std::cin >> i;
        std::cin >> j;
        std::cin >> k;
        auto cur_slice_nums = std::vector<int>(nums.begin() + i - 1, nums.begin() + j);
        find(k - 1, cur_slice_nums);
    }

    return 0;
}