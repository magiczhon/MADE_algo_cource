#include <iostream>
#include <string>
#include <ctime>
#include <vector>

const int64_t PRIME = 1e9 + 7;
const char ALPHABET_OFFSET = 'a' - 1;

class Map {
    int64_t size;
    int64_t a;
    std::vector<std::vector<std::pair<std::string, std::string>>> elements;

    int64_t hash(const std::string& s) {
        int64_t res = 0;
        int64_t cur_a = 1;
        for(const char sym : s) {
            res = std::abs(res  +  cur_a *(sym - ALPHABET_OFFSET)) % PRIME;
            cur_a *= a;
        }
        return res % size;
    }

public:

    Map() {
        size = 2 * 1e5;
        elements = std::vector<
                   std::vector<std::pair<std::string, std::string>>
                              > (size);
        srand(time(nullptr));
        a = rand() + 10007;
    }

    void put(const std::string& key, const std::string& x) {
        int64_t index = hash(key);
        for (auto & it : elements[index]) {
            if (it.first == key) {
                it.second = x;
                return;
            }
        }
        elements[index].push_back(std::make_pair(key, x));
    }

    std::string get(const std::string& key) {
         int64_t index = hash(key);
         for (auto & it : elements[index]) {
             if (it.first == key) {
                 return it.second;
             }
         }
         return "none";
    }

    void drop(const std::string& key) {
        int64_t index = hash(key);
        for (auto it = elements[index].begin();
             it != elements[index].end(); ++it) {
            if (it->first == key) {
                elements[index].erase(it);
                break;
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string command;
    std::string key;
    std::string value;
    std::string res;
    Map map;

    while(std::cin >> command) {
        if (command == "put") {
            std::cin >> key;
            std::cin >> value;
            map.put(key, value);
        }
        if (command == "get") {
            std::cin >> key;
            res = map.get(key);
            std::cout << res << '\n';
        }
        if (command == "delete") {
            std::cin >> key;
            map.drop(key);
        }
    }

    return 0;
}
