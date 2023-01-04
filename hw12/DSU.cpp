#include <iostream>
#include <vector>
#include <string>

class DSU {
public:
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<int> min;
    std::vector<int> max;

    DSU (int n) {
        for (int i = 0; i < n; i++) {
            parent.emplace_back(i);
            min.emplace_back(i);
            max.emplace_back(i);
        }
        rank = std::vector<int> (n, 1);
    }

    int get(int x) {
        if (parent[x] != x) {
            parent[x] = get(parent[x]);
        }
        return parent[x];
    }

    void join(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) {
            return;
        }

        if (rank[x] > rank[y])
            std::swap(x, y);

        rank[y] += rank[x];

        if (max[x] > max[y])
            max[y] = max[x];
        else
            max[x] = max[y];

        if (min[x] < min[y])
            min[y] = min[x];
        else
            min[x] = min[y];

        parent[x] = y;
    }
};

int main() {
    int n, x, y;
    std::string command;
    std::cin >> n;
    DSU tree(n + 1);
    int res;
    while (std::cin >> command) {
        if (command == "union") {
            std::cin >> x >> y;
            tree.join(x, y);
        }
        else if (command == "get") {
            std::cin >> x;
            res = tree.get(x);
            std::cout << tree.min[res]
                        << " " << tree.max[res]
                        << " " << tree.rank[res]
                        << '\n';
        }
    }
    return 0;
}
