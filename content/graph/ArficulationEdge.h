/**
 * Description: Finds all articulation edges (bridges) in an undirected graph.
 *  An articulation edge is an edge whose removal increases the number of connected components.
 * Time: $O(V + E)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
const int MAX_V = 10001;
vector<int> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
int cnt = 0;

void dfs(vector<pair<int, int>>& ret, int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    for (auto u: adj[v]) if (u != p) {
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(ret, u, v);
            if (low[u] > ord[v]) ret.push_back(make_pair(min(v, u), max(v, u)));
			low[v] = min(low[u], low[v]);
        }
    }
}

// V: maximum vertex + 1
// 1-index
vector<pair<int, int>> getEdge(int V) {
	vector<pair<int, int>> ret;
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(ret, i, 0);
	return ret;
}