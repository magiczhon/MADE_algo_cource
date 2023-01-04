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

std::vector<int> qsort(std::vector<int> &unsort_nums) {
    if (unsort_nums.size() < 2)
        return unsort_nums;
    srand(time(NULL));
    int median = unsort_nums[rand() % unsort_nums.size()];
    std::vector<int> left;
    std::vector<int> middle;
    std::vector<int> right;

    split(unsort_nums, left, middle, right, median);

    left = qsort(left);
    right = qsort(right);

    std::vector<int> result;
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), middle.begin(), middle.end());
    result.insert(result.end(), right.begin(), right.end());

    return result;
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
    std::vector<int> result = qsort(nums);

    for (auto num : result) {
        std::cout << num << ' ';
    }
    return 0;
}

// 10
// 1 8 2 1 4 7 3 2 3 6

// 9
// 5 -4 3 2 -4 1 8 -6 9

// 6
// 1 3 2 4 -1 -9

// 5
// 5 3 4 1 2

// 7
// 5 1 2 3 4 6 8

//5
//-1 6 2 -1 -1

// 4
// -1 2 -1 -1

//int split(int l, int r, int x, std::vector<int> &nums) {
//    int m = l;
//    std::vector<int> tmp;
//    for (int i = l; i < r; i++) {
//        if (nums[i] < x) {
//            tmp.push_back(nums[i]);
//            std::swap(nums[i], nums[m]);
//            m++;
//
//        }
//    }
//    for (auto num : tmp) {
//        std::cout << num << ' ';
//    }
//    std::cout << std::endl;
//    return m;
//}
//
//void qsort(int l, int r, std::vector<int> &nums) {
//    if (r - l <= 1) {
//        return;
//    }
//    int x = 0;
//    if (r - l > 2) {
//        x = get_median(nums[l], nums[(l + r) / 2], nums[r - 1]);
//    }
//    else {
//        x = std::max(nums[l], nums[r - 1]);
//    }
//
//    int m = split(l, r, x, nums);
//
//    qsort(l, m, nums);
//    qsort(m, r, nums);
//}



//int split(int l, int r, std::vector<int> &nums) {
//    int index = (l + r) / 2;
//    int x = nums[index];
//    std::swap(nums[index], nums[r - 1]);
//    int m = l;
//    for (int i = l; i < r; i++) {
//        if (nums[i] < x) {
//            std::swap(nums[i], nums[m]);
//            m++;
//        }
//    }
//    std::swap(nums[m], nums[r - 1]);
//    return m;
//}
//
//void qsort(int l, int r, std::vector<int> &nums) {
//    if (r - l <= 1) {
//        return;
//    }
//    int m = split(l, r, nums);
//    qsort(l, m, nums);
//    qsort(m, r, nums);
//}