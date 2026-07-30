/**
 * Description: Finds all biconnected components (BCCs) in an undirected graph.
 *  A BCC is a maximal subgraph where any two vertices are connected by at least two disjoint paths.
 * Time: $O(V + E)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
struct Edge {
    int v, c, rev;
};

const int MAX_V = 300001;
vector<Edge> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
bool vis[MAX_V];
int cnt = 0, col = 0;
vector<int> bcc[MAX_V];

void dfs(int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    for (const auto& edge: adj[v]) if (edge.v != p) {
        int u = edge.v;
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(u, v);
			low[v] = min(low[u], low[v]);
        }
    }
}

void color(int v, int c, int p) {
    if (c > 0) bcc[v].push_back(c);
    vis[v] = true;
    for (auto& edge: adj[v]) {
        int u = edge.v;
        if (low[u] >= ord[v]) {
            if (!vis[u]) bcc[v].push_back(++col);

            if (edge.c == 0) {
                edge.c = col;
                adj[u][edge.rev].c = col;
            }

            if (!vis[u]) color(u, col, v);
        } else {
            if (c > 0 && edge.c == 0) {
                edge.c = c;
                adj[u][edge.rev].c = c;
            }
            if (!vis[u]) color(u, c, v);
        }
    }
}

// V: maximum vertex + 1
// 1-index
void getBcc(int V) {
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(i, 0);
    for (int i = 1; i < V; ++i) if (!vis[i]) color(i, 0, 0);
}

void addEdge(int u, int v) {
    adj[u].push_back(Edge {v, 0, (int) adj[v].size()});
    adj[v].push_back(Edge {u, 0, (int) adj[u].size() - 1});
}