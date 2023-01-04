#include <iostream>
#include <vector>
#include <string>

const int ALPHABET = 26;
const int SHIFT = 'a';

class Trie {
public:
    int size;
    std::vector<std::vector<int>> next;
    std::vector<bool> is_terminal;

    Trie () {
        size = 1;
        next.push_back(std::vector<int>(26, -1));
        is_terminal.push_back(false);
    };

    void insert(const std::string& s) {
        int v = 0;
        for (char c : s) {
            c -= SHIFT;
            if (next[v][c] == -1) {
                next[v][c] = size;
                size += 1;
                next.push_back(std::vector<int>(26, -1));
                is_terminal.push_back(true);
            }
            v = next[v][c];
        }
        is_terminal[v] = true;

    }

    bool contains(const std::string& s) {
        int v = 0;
        for (char c : s) {
            c -= SHIFT;
            if (next[v][c] == -1) {
                return false;
            }
            v = next[v][c];
        }
        if (is_terminal[v]) {
            return true;
        }
        return false;
    }

    bool search(const std::string& s) {
        int v = 0;
        for (char c : s) {
            c -= SHIFT;
            while(v < size) {
                if (next[v][c] == -1) {
                    return false;
                }
                v = next[v][c];
            }
        }
        if (is_terminal[v]) {
            return true;
        }
        return false;
    }
};

int main() {
    std::string text, s;
    int n;
    std::cin >> text >> n;
    Trie trie;
//    for (int i = 0; i < text.size(); i++) {
//        trie.insert(text.substr(i));
//    }
    trie.insert(text);
    for (int _ = 0; _ < n; _++) {
        std::cin >> s;
        if(trie.search(s)) {
            std::cout << "Yes" << '\n';
        }
        else {
            std::cout << "No" << '\n';
        }
    }
}

// trololo
// 1
// trol
