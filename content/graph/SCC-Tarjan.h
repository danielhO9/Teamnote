/**
 * Description: Strongly Connected Components (SCC) using Tarjan's Algorithm.
 *  Finds all SCCs in a directed graph.
 * Time: $O(V + E)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
const int MAX_V = 10001;
vector<int> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
bool inS[MAX_V];
int cnt = 0;

void dfs(vector<vector<int>>& ret, stack<int>& s, int v) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    s.push(v);
    inS[v] = true;
    for (auto u: adj[v]) {
        if (inS[u]) low[v] = min(low[v], ord[u]);
        else if (!ord[u]) {
            dfs(ret, s, u);
			low[v] = min(low[u], low[v]);
        }
    }
    if (low[v] == ord[v]) {
        vector<int> scc;
        while (true) {
            int cur = s.top(); s.pop();
            inS[cur] = false;
            scc.push_back(cur);
            if (cur == v) break;
        }
        ret.push_back(scc);
    }
}

// V: maximum vertex + 1
// 1-index
vector<vector<int>> getScc(int V) {
	vector<vector<int>> ret;
    stack<int> s;
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(ret, s, i);
	return ret;
}