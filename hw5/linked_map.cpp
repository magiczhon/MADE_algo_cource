#include <iostream>
#include <string>
#include <ctime>
#include <vector>

const int64_t PRIME = 1e9 + 7;
const char ALPHABET_OFFSET = 'a' - 1;

class Node {
public:
    std::string key;
    std::string value;
    Node* prev{};
    Node* next{};

    Node() {
        key = "";
        value = "";
        prev = nullptr;
        next = nullptr;
    }

    Node(std::string set_key, std::string set_value,
            Node* set_next, Node* set_prev) {
        key = std::move(set_key);
        value = std::move(set_value);
        prev = set_prev;
        next = set_next;
    }
};

class Map {
    int64_t size;
    int64_t a;
    Node* last;
    std::vector<std::vector<Node*>> elements;

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
        elements = std::vector<std::vector<Node*>> (size);
        srand(time(nullptr));
        a = rand() + 10007;
        last = nullptr;
    }

    void put(const std::string& key, const std::string& x) {
        int64_t index = hash(key);
        for (auto & it : elements[index]) {
            if (it->key == key) {
                it->value = x;
                return;
            }
        }
        Node* new_node = new Node(key, x, nullptr, last);
        elements[index].push_back(new_node);
        if (last != nullptr) {
            last->next = elements[index].back();
        }
        last = elements[index].back();
    }

    std::string get(const std::string& key) {
        int64_t index = hash(key);
        for (auto & it : elements[index]) {
            if (it->key == key) {
                return it->value;
            }
        }
        return "none";
    }

    std::string get_cur_or_prev_or_next_node(
            const std::string& key, const std::string& type_node
            ) {
        int64_t index = hash(key);
        for (auto & it : elements[index]) {
            if (it->key == key) {
                if (type_node == "get") {
                    return it->value;
                }
                if (type_node == "next" and it->next != nullptr) {
                    return it->next->value;
                }
                if (type_node == "prev" and it->prev != nullptr) {
                    return it->prev->value;
                }
            }
        }
        return "none";
    }

    void drop(const std::string& key) {
        int64_t index = hash(key);
        Node* tmp_prev;
        Node* tmp_next;
        for (auto it = elements[index].begin();
             it != elements[index].end(); ++it) {

            if (it[0]->key == key) {
                if (it[0]->prev == nullptr and it[0]->next == nullptr) {
                    last = nullptr;
                }
                else if (it[0]->prev == nullptr) {
                    it[0]->next->prev = nullptr;
                }
                else if (it[0]->next == nullptr) {
                    it[0]->prev->next = nullptr;
                    last = last->prev;
                }
                else {
                    tmp_prev = it[0]->prev;
                    tmp_next = it[0]->next;
                    it[0]->prev->next = tmp_next;
                    it[0]->next->prev = tmp_prev;
                }
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
        if (command == "get" or command == "prev" or command == "next") {
            std::cin >> key;
            res = map.get_cur_or_prev_or_next_node(key, command);
            std::cout << res << '\n';
        }
        if (command == "delete") {
            std::cin >> key;
            map.drop(key);
        }
    }

    return 0;
}
