#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
public:
    std::vector<std::vector<int32_t>> adjacency;
    std::vector<int32_t> color;

    void dfs(int32_t vertice, std::vector<int32_t>& ans) {
        color[vertice] = 1;
        for (int32_t i : adjacengcy[vertice]) {
            if (color[i] == 0) {
                dfs(i, ans);
            }
            else if (color[i] == 1) {
                std::cout << -1;
                exit(0);
            }
        }
        color[vertice] = 2;
        ans.push_back(vertice);
    }

    Graph(int32_t vertice_count) {
        adjacency.resize(vertice_count);
        color.resize(vertice_count);
    }

    void add_edge(int32_t begin, int32_t end) {
        adjacency[begin - 1].push_back(end - 1);
    }

    std::vector<int32_t> topology_sort() {
        std::vector<int32_t> ans;
        for (int32_t i = 0; i < adjacency.size(); i++) {
            if (color[i] == 0) {
                dfs(i, ans);
            }
        }
        std::reverse(std::begin(ans), std::end(ans));
        return ans;
    }
};

int32_t main() {
    int32_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    int32_t begin, end;
    for (int32_t i = 0; i < m; i++) {
        std::cin >> begin >> end;
        graph.add_edge(begin, end);
    }
    std::vector<int32_t> ans = graph.topology_sort();
    for (int32_t i = 0; i < ans.size(); i++) {
        std::cout << ans[i] + 1 << ' ';
    }
    return 0;
}