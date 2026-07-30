/**
 * Description: Strongly Connected Components (SCC) using Kosaraju's Algorithm.
 *  Finds all SCCs in a directed graph.
 * Time: $O(V + E)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
const int MAX_V = 10001;
vector<int> adj[MAX_V];

vector<int> iadj[MAX_V];
bool vis[MAX_V];

void dfs(vector<int>& ord, int v) {
	vis[v] = true;
	for (auto u: adj[v]) if (!vis[u]) dfs(ord, u);
	ord.push_back(v);
}

void idfs(vector<vector<int>>& ret, int v) {
	vis[v] = true;
	ret.back().push_back(v);
	for (auto u: iadj[v]) if (!vis[u]) idfs(ret, u);
}

// V: maximum vertex + 1
vector<vector<int>> getScc(int V) {
	const int s = 1; // 1-index
	for (int u = s; u < V; ++u) for (auto v: adj[u]) iadj[v].push_back(u);
	vector<int> ord;
	for (int i = s; i < V; ++i) if (!vis[i]) dfs(ord, i);
	reverse(ord.begin(), ord.end());
	for (int i = s; i < V; ++i) vis[i] = false;
	vector<vector<int>> ret;
	for (auto v: ord) if (!vis[v]) {
		ret.push_back({});
		idfs(ret, v);
	}
	return ret;
}