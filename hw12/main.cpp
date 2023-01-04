#include <iostream>
#include <vector>
#include "string"

struct Edge {
    int index;
    int max;
    int min;
    int size;

    Edge() {
        index = 0;
        max = INT32_MIN;
        min = INT32_MAX;
        size = 0;
    }

    Edge(int index): index(index) {
        max = index;
        min = index;
        size = 1;
    }

    Edge& operator=(const Edge& right) {
        if (this == &right) {
            return *this;
        }
        index = right.index;
        max = right.max;
        min = right.min;
        size = right.size;
        return *this;
    }
};

class DSU {
public:
    std::vector<Edge> p;
    std::vector<int> r;

    DSU (int n) {
        for (int i = 0; i < n; i++) {
            p.emplace_back(i);
        }
        r = std::vector<int> (n);
    }

    Edge get(Edge x) {
        if (p[x.index].index != x.index) {
            p[x.index] = get(p[x.index]);
        }
        return p[x.index];
    }

    void join(Edge x, Edge y) {
        x = get(x);
        y = get(y);
        if (x.index == y.index) {
            return;
        }
        if (x.size > y.size) {
            Edge tmp = x;
            x = y;
            y = tmp;
        }

        if (x.size == y.size) {
            y.size += 1;
        }


        p[x.index].index = y.index;
    }
};


int main() {
    int n, x, y;
    std::string command;
    std::cin >> n;
    DSU tree(n);
    Edge res;
    while (std::cin >> command) {
        if (command == "#") break;
        if (command == "union") {
            std::cin >> x >> y;
            tree.join(x, y);
        }
        else if (command == "get") {
            std::cin >> x;
            res = tree.get(x);
            std::cout << res.min << " " << res.max << " " << res.size << '\n';
        }
    }
    return 0;
}


//5
//union 1 2
//get 3
//get 2
//union 2 3
//get 2
//union 1 3
//get 5
//union 4 5
//get 5
//union 4 1
//get 5
//#
