#include <iostream>
#include <vector>

class Edge {
public:
    int to;
    int f;
    int c;
    int link;

    Edge(int to, int w, int link): to(to), c(w), link(link){
        f = 0;
    }

    Edge() {
        to = 0;
        f = 0;
        c = 0;
        link = 0;
    }
};

class Graph {
public:
    std::vector<std::vector<Edge>> graph;
    int n;

    Graph(int n, int begin, int end) : n(n) {
        graph.resize(n);
        graph[0].push_back(Edge(2 * begin - 1, 2, graph[2 * begin - 1].size()));
        graph[2 * begin - 1].push_back(Edge(0, 0, graph[0].size() - 1));

        graph[2 * end].push_back(Edge(n - 1, 2, graph[n - 1].size()));
        graph[n - 1].push_back(Edge(2 * end, 0, graph[2 * end].size() - 1));
    }

    void add_edge(int from, int to, int w, int link) {
        graph[2 * from].push_back(Edge(2 * to - 1, w, link));
    }

    int push_flow(int v, int t, int cur_flow, std::vector<int>& used) {
        used[v] = 1;
        if (v == t) {
            std::cout << v / 2 << ' ';
            return cur_flow;
        }
        for (Edge& u: graph[v]) {

            if (!used[u.to] && (u.f < u.c)) {

                int next_flow = std::min(cur_flow, u.c - u.f);
                int delta = push_flow(u.to, t, next_flow, used);
                if (delta > 0) {
                    u.f += delta;
                    graph[u.to][u.link].f -= delta;
                    //std::cout << v / 2 << " --> " << (u.to + 1) / 2 << '\n';
                    return delta;
                }
            }
        }
        return 0;
    }

    int ford_falkerson(int start, int finish) {
        int ans = 0;
        while (true) {
            std::vector<int> used (n, 0);
            int delta = push_flow(start, finish, INT32_MAX, used);
            if (delta > 0) {
                ans += delta;
            }
            else {
                break;
            }
        }
        return ans;
    }
};

int main() {
    int n, m, s, t, x, y;
    std::cin >> n >> m >> s >> t;
    Graph g(2 * n + 2, s, t);
    for (int i = 0; i < m; i++) {
        std::cin >> x >> y;
        g.add_edge(x, y, 1, g.graph[y].size());
        g.add_edge(y, x, 0, g.graph[x].size() - 1);
    }
    for (int i = 1; i <= n; i++) {
        g.graph[2 * i - 1].push_back(Edge(2 * i, 1, g.graph[2 * i].size()));
        g.graph[2 * i].push_back(Edge(2 * i - 1, 0, g.graph[2 * i - 1].size() - 1));
    }

    int ans = g.ford_falkerson(0, 2 * n + 1);
    std::cout << ans;
    return 0;
}
