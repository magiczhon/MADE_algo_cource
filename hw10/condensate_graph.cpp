#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Graph {
public:
    std::vector<std::vector<int32_t>> adjacency;
    std::vector<int32_t> color;

    Graph(int32_t vertice_count) {
        adjacency.resize(vertice_count);
        color.resize(vertice_count);
    }

    void add_edge(int32_t begin, int32_t end) {
        adjacency[begin - 1].push_back(end - 1);
    }

    std::vector<int32_t> get_color() {
        return color;
    }

    void dfs_for_top_sort(int32_t vertice, std::vector<int32_t>& ans) {
        color[vertice] = 1;
        for (int32_t i : adjacency[vertice]) {
            if (color[i] == 0) {
                dfs_for_top_sort(i, ans);
            }
        }
        ans.push_back(vertice);
    }

    void dfs_for_linked_comp(int32_t vertice, int32_t current_colour) {
        color[vertice] = current_colour;
        for (int32_t i : adjacency[vertice]) {
            if (color[i] == 0) {
                dfs_for_linked_comp(i, current_colour);
            }
        }
    }

    std::vector<int32_t> topology_sort() {
        std::vector<int32_t> ans;
        for (int32_t i = 0; i < adjacency.size(); i++) {
            if (color[i] == 0) {
                dfs_for_top_sort(i, ans);
            }
        }
        for (int32_t i = 0; i < color.size(); i++) {
            color[i] = 0;
        }
        std::reverse(std::begin(ans), std::end(ans));
        return ans;
    }

    Graph get_added_graph() {
        Graph added_graph(adjacency.size());
        for (int32_t i = 0; i < adjacency.size(); i++) {
            for (int32_t j : adjacency[i]) {
                added_graph.add_edge(j + 1, i + 1);
            }
        }
        return added_graph;
    }

    int32_t linked_comp_count(const std::vector<int32_t>& order) {
        int32_t count = 0;
        for (int32_t i : order) {
            if (color[i] == 0) {
                ++count;
                dfs_for_linked_comp(i, count);
            }
        }
        return count;
    }

    int32_t condensate_count_edges() {
        std::vector<int32_t> order = topology_sort();
        Graph added_graph = get_added_graph();
        added_graph.linked_comp_count(order);
        color = added_graph.get_color();
        std::set<std::pair<int32_t, int32_t>> edges;
        for (int32_t i = 0; i < adjacency.size(); i++) {
            for (int32_t j : adjacency[i]) {
                if (color[i] != color[j]) {
                    edges.insert(std::make_pair(color[i], color[j]));
                }
            }
        }
        return edges.size();
    }
};

int32_t main() {
    int32_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    int32_t b, e;
    for (int32_t i = 0; i < m; i++) {
        std::cin >> b >> e;
        graph.add_edge(b, e);
    }
    std::cout << graph.condensate_count_edges();
}
