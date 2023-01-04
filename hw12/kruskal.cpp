#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int from;
    int to;
    int w;

    Node(int w, int from, int to): from(from), to(to), w(w)
    {}
};

bool comp(const Node &l, const Node &r) {
    return l.w < r.w;
}

class MST {
public:
    std::vector<int> parent;
    std::vector<int> rank;


    MST (int n) {
        for (int i = 0; i < n; i++) {
            parent.emplace_back(i);
        }
        rank = std::vector<int> (n, 0);
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
        else {
            if (rank[x] > rank[y]) {
                std::swap(x, y);
            }
            if (rank[x] == rank[y]) {
                ++rank[y];
            }
            parent[x] = y;
        }
    }

    int64_t kruskal_algorithm(std::vector<Node> edges) {
        int64_t sum_w = 0;
        std::sort(edges.begin(), edges.end(), comp);
        for(auto const &edge: edges) {
            if(get(edge.from) != get(edge.to)) {
                sum_w += edge.w;
                join(edge.from, edge.to);
            }
        }
        return sum_w;
    }
};



int main() {
    int n, m, from, to, w;
    std::cin >> n >> m;
    std::vector<Node> edges;
    for (int _ = 0; _ < m; _++) {
        std::cin >> from >> to >> w;
        edges.push_back(Node(w, from, to));
    }

    MST tree(n + 1);
    int64_t sum_w = tree.kruskal_algorithm(edges);
    std::cout << sum_w;

    return 0;
}
