#include <iostream>
#include <string>
#include <ctime>
#include <vector>

const int64_t PRIME = 1e9 + 7;
const std::pair<int64_t , int64_t> EMPTY = std::make_pair(INT32_MAX, INT32_MAX);
const std::pair<int64_t , int64_t> RIP = std::make_pair(INT32_MIN, INT32_MIN);

class Set {
    int64_t size;
    int64_t count_elements;
    int64_t count_rip;
    int64_t a;
    std::vector<std::pair<int64_t, int64_t>> elements;

    int64_t hash(int64_t x) {
        return ((a * abs(x) + 7) % PRIME) % size;
    }

    int64_t next(int64_t i) {
        return (i + 1) % size;
    }

public:

    Set() {
        size = 4;
        count_elements = 0;
        count_rip = 0;
        srand(time(NULL));
        a = rand() + 1;
        elements = std::vector<std::pair<int64_t, int64_t>> (size, EMPTY);
    }

    void do_rehashing() {
        size *= 2;
        std::vector<std::pair<int64_t, int64_t>> new_table(size, EMPTY);
        int64_t new_count_elements = 0;
        a = rand() + 1;
        int64_t index;
        for (auto const el : elements) {
            if (el != EMPTY and el != RIP) {
                index = hash(el.first);
                while (new_table[index] != EMPTY) {
                    index = next(index);
                }
                new_table[index] = el;
                new_count_elements++;
            }
        }
        elements = new_table;
        count_elements = new_count_elements;
        count_rip = 0;
    }

    void insert(int64_t key, int64_t x) {
        if(exist(key)) {
            return;
        }
        int64_t index = hash(key);
        while(elements[index] != EMPTY) {
            if (elements[index] == RIP) {
                count_rip--;
                break;
            }
            index = next(index);
        }
        elements[index] = std::make_pair(key, x);
        count_elements++;
        if (count_elements + count_rip > size / 2) {
            do_rehashing();
        }
    }

    bool exist(int64_t key) {
        int64_t index = hash(key);
        while(elements[index] != EMPTY) {
            if (elements[index].first == key) {
                return true;
            }
            index = next(index);
        }
        return false;
    }

    void drop(int64_t key) {
        int64_t index = hash(key);
        while(elements[index] != EMPTY) {
            if (elements[index].first == key) {
                elements[index] = RIP;
                count_rip++;
                count_elements--;
                break;
            }
            index = next(index);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string command;
    int64_t x;
    Set set;
    int64_t res;

    while(std::cin >> command) {
        if (command == "insert") {
            std::cin >> x;
            set.insert(x, x);
        }
        if (command == "exists") {
            std::cin >> x;
            res = set.exist(x);

            if (res) {
                std::cout << "true" << '\n';
            }
            else {
                std::cout << "false" << '\n';
            }
        }
        if (command == "delete") {
            std:: cin >> x;
            set.drop(x);
        }
    }
    return 0;
}

