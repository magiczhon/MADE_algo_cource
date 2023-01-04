#include <iostream>
#include <vector>

const int32_t DEFAULT_COLOR = -1;

std::vector<std::vector<int32_t>> read(int32_t n, int32_t m) {
    std::vector<std::vector<int32_t>> graph(n);
    int32_t x, y;

    for (int32_t i = 0; i < m; i++) {
        std::cin >> x >> y;
        x--;
        y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    return graph;
}

void print_graph(std::vector<std::vector<int32_t>> &graph) {
    int32_t i = 1;
    for (auto const &line : graph ) {
        std::cout << i << ": [";
        for (auto el : line) { std::cout << el + 1 << " "; }
        std::cout << "]\n";
        i++;
    }
}

void dfs(
        std::vector<std::vector<int32_t>> &graph, int32_t cur_v,
        std::vector<int32_t>& color,
        int32_t cur_color
        ) {
    color[cur_v] = cur_color;
    for (auto const &u : graph[cur_v]) {
        if (color[u] == DEFAULT_COLOR) {
            dfs(graph, u, color, cur_color);
        }
    }
}

int main() {
    int32_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int32_t>> graph = read(n, m);
    std::vector<int32_t> color (n, -1);
    int cur_color = 1;
    for (int32_t i = 0; i < n; i++) {
        if (color[i] == DEFAULT_COLOR) {
            dfs(graph, i, color, cur_color);
            cur_color++;
        }

    }
    std::cout << cur_color - 1 << '\n';
    for (auto const &el : color) { std::cout << el << " "; }
    return 0;
}