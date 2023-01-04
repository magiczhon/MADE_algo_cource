#include <iostream>
#include <vector>
#include <set>

struct Edge {
    int from;
    int to;
    int w;

    Edge(int from, int to, int w): from(from), to(to), w(w)
    {}
};

class Graph {
public:
    std::vector<std::vector<std::pair<int, int>>> adjacency;
    std::vector<int> color;
    int size;

    Graph(int vertice_count) {
        size = vertice_count;
        adjacency.resize(vertice_count);
        color.resize(vertice_count);
    }

    void add_edge(int begin, int end, int weight) {
        adjacency[begin - 1].push_back(std::make_pair(end - 1, weight));
        adjacency[end - 1].push_back(std::make_pair(begin - 1, weight));
    }

    void print_distance() {
        std::vector<int> distance = dijkstras_algorithm(0);
        for (int i : distance) {
            std::cout << i << ' ';
        }
    }

    std::vector<int> dijkstras_algorithm(int start) {
        std::vector<int> d(size, INT32_MAX);
        d[start] = 0;
        std::set <std::pair<int, int>> q;
        q.insert(std::make_pair(start, d[start]));
        while (!q.empty()) {
            int v = q.begin()->first;
            q.erase(q.begin());
            for (const auto j : adjacency[v]) {
                int	len = j.second;
                int to = j.first;
                if (d[v] + len < d[to]) {
                    q.erase(std::make_pair(to, d[to]));
                    d[to] = d[v] + len;
                    q.insert(std::make_pair(to, d[to]));
                }
            }
        }
        return d;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n);
    int b, e, w;
    for (int i = 0; i < m; i++) {
        std::cin >> b >> e >> w;
        graph.add_edge(b, e, w);
    }
    graph.print_distance();
    return 0;
}