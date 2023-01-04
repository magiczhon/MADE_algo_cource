struct Edge {
    int from, to; // ребро из from в to
    int next; // номер следующего ребра из вершины from int f; // flow (поток)
    i n t c ; / / capacity (пропускная способность)
};

int n, m;
vector<Edge> edges;
vector<int> head; // для каждой вершины номер первого ребра, начало списка

void add_edge( int a, int b, int capacity ) {
    edges.push_back(Edge {a, b, head[a], 0, capacity});
    head[a] = edges.size() - 1; }

void read () {
    cin >> n >> m; // количество вершин, количество рёбер edges.reserve(2 * m); // каждому ребру нужно обратное
    head = vector<int>(n, -1); // -1 обозначает пустой список while (m--) {
    int a, b, c;
    cin >> a >> b >> c, a--, b--; // во входных данных вершины обычно нумеруются с 1 add_edge(a, b, c); // прямое ребро
    add_edge(b, a, 0); // обратное ребро
}

int cc;

vector<int> u; // Если u[i] = cc, вершина помечена, иначе не помечена

int dfs( int v, int flow ) { if (v == t)
        return flow;
    u [ v ] = c c ; / / dfs должен работать за линейное время, каждую вершину посещаем один раз for (int x, i = head[v]; i != -1; i = edges[e].next) {
        Edge &e = edges[i];
        if (e.f < e.c && u[e.to] != cc && (x = dfs(e.to, min(flow, e.c-e.f))) > 0) {
            e.f += x, edges[i ^ 1].f -= x; // увеличили по прямому, уменьшили по обратному
            return x; }
    }
    return 0; }

int maxFlow () {
    read();
    cc = 1, u = vector <int>(n, 0);
    int f = 0, add;
    while ((add = dfs(s, INT_MAX)) > 0)
        f += add, cc++; // cc++ делает все вершины не помеченными return f;
}

int getPath( int v, int flow ) {
    if (v == t) return flow;
    u[v] = cc;
    for (int x, i = head[v]; i != -1; i = edges[e].next) {
        Edge &e = edges[i];
        if (e.f > 0 && u[e.to] != cc && (x = getPath(e.to, min(flow, e.f))) > 0) {
            e.f -= x, edges[i ^ 1].f += x; // отщепили путь
            return x;
        }
    }
    return 0; }