#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int32_t get_index_max_num(std::vector<int32_t> const& nums) {
    int32_t max = INT32_MIN;
    size_t end = nums.size();
    int32_t index_max_num = 0;
    for (size_t i = 0; i < end; i++) {
        if (nums[i] > max) {
            max = nums[i];
            index_max_num = i;
        }
    }
    return index_max_num;
}

std::vector<int32_t> get_subseq(
        std::vector<int32_t> const& nums,
        std::vector<int32_t> const& count_gr_subseq
        ) {
    std::vector<int32_t> gr_subseq;

    int32_t index_count_gr_subseq = get_index_max_num(count_gr_subseq);
    gr_subseq.push_back(nums[index_count_gr_subseq]);

    int32_t value_count_gr_subseq = count_gr_subseq[index_count_gr_subseq];
    while (value_count_gr_subseq != 1) {
        value_count_gr_subseq--;
        for(size_t i = index_count_gr_subseq; i >= 0; i--) {
            if (value_count_gr_subseq == count_gr_subseq[i]) {
                index_count_gr_subseq = i;
                break;
            }
        }
        gr_subseq.push_back(nums[index_count_gr_subseq]);
    }
    std::reverse(gr_subseq.begin(), gr_subseq.end());
    return gr_subseq;
}

int32_t get_max_len_subseq(
        std::vector<int32_t> const& nums,
        std::vector<int32_t> const& count_gr_subseq,
        size_t end
        ) {
    int32_t len_subseq = 0;
    for (size_t i = 0; i < end; i++) {
        if (nums[i] < nums[end] and count_gr_subseq[i] > len_subseq)
            len_subseq = count_gr_subseq[i];
    }
    return len_subseq + 1;
}

std::vector<int32_t> greatest_increasing_subsequence(
        std::vector<int32_t> const& nums,
        int32_t n
        ) {
    std::vector<int32_t> count_gr_subseq(n);
    count_gr_subseq[0] = 1;
    for (size_t i = 1; i < n; i++) {
        count_gr_subseq[i] = get_max_len_subseq(nums, count_gr_subseq, i);
    }
    std::vector<int32_t> gr_subseq = get_subseq(nums, count_gr_subseq);
    return gr_subseq;
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int32_t n;
    std::cin >> n;
    std::vector<int32_t> nums(n);
    int32_t num;
    for (size_t i = 0; i < n; i++) {
        std::cin >> num;
        nums[i] = num;
    }

    std::vector<int32_t> gr_subseq = greatest_increasing_subsequence(nums, n);

    std::cout << gr_subseq.size() << '\n';
    for (auto const& el : gr_subseq) {
        std::cout << el << ' ';
    }
    return 0;
}
