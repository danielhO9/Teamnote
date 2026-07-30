/**
 * Description: Bipartite Matching using DFS-based augmenting path algorithm.
 *  Finds the maximum matching in a bipartite graph.
 * Time: $O(V \cdot E)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
const int MAX_N = 501;
const int MAX_M = 501;

int aMatch[MAX_N], bMatch[MAX_M];
bool vis[MAX_N];
vector<int> adj[MAX_N];

bool dfs(int a) {
	if (vis[a]) return false;
	vis[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b])) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch(int N, int M) {
	for (int i = 0; i < N; ++i) aMatch[i] = -1;
	for (int i = 0; i < M; ++i) bMatch[i] = -1;
	int size = 0;
	for (int i = 0; i < N; ++i) vis[i] = false;
	for (int start = 0; start < MAX_N; ++start) {
		if (dfs(start)) {
			++size;
			for (int i = 0; i < N; ++i) vis[i] = false;
		}
	}
	return size;
}