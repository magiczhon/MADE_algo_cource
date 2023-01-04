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

    Graph(int n) : n(n) {
        graph.resize(n);
    }

    void add_edge(int from, int to, int w, int link) {
        graph[from].push_back(Edge(to, w, link));
    }

    int push_flow(int v, int t, int cur_flow, std::vector<int>& used) {
        used[v] = 1;
        if (v == t) {
            return cur_flow;
        }
        for (Edge& u: graph[v]) {
            if (!used[u.to] && (u.f < u.c)) {
                int next_flow = std::min(cur_flow, u.c - u.f);
                int delta = push_flow(u.to, t, next_flow, used);
                if (delta > 0) {
                    u.f += delta;
                    graph[u.to][u.link].f -= delta;
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
    int n, m, a, b, c;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        std::cin >> a >> b >> c;
        a = a - 1;
        b = b - 1;
        g.add_edge(a, b, c, g.graph[b].size());
        g.add_edge(b, a, c, g.graph[a].size() - 1);
    }
    int ans = g.ford_falkerson(0, n - 1);
    std::cout << ans;
    return 0;
}
