/**
 * Description: Heavy-Light Decomposition for path queries and updates in trees.
 *  Decomposes a tree into heavy and light paths for efficient segment tree operations.
 * Time: $O(N \log N)$, where $N$ is the number of vertices in the tree.
 */
const int MAX_V = 100001;
vector<int> adj[MAX_V];

template <class T>
struct HLD {
	T seg;
	vector<int> sz, dep, par, top, in, out;
	int cnt;

    HLD() = default;
	HLD(const vector<ll>& a): cnt(0) {
		int n = a.size();
		sz.resize(n); dep.resize(n);
		par.resize(n); top.resize(n);
		in.resize(n); out.resize(n);
		for (int i = 1; i < n; ++i) if (in[i] == 0) {
			top[i] = i;
			dfs1(i, -1);
			dfs2(i, -1);
		}
		vector<ll> arr(n);
        for (int i = 1; i < n; ++i) arr[in[i]] = a[i];
        seg = T {arr};
	}
	void dfs1(int v, int p) {
		sz[v] = 1;
		for (auto& u: adj[v]) if (u != p) {
			dep[u] = dep[v] + 1;
			par[u] = v;
			dfs1(u, v);
			sz[v] += sz[u];
			if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfs2(int v, int p) {
		in[v] = ++cnt;
		for (auto u: adj[v]) if (u != p) {
			top[u] = (u == adj[v][0] ? top[v] : u);
			dfs2(u, v);
		}
		out[v] = cnt;
	}
	void update(int v, ll val) { seg.update(in[v], val); }
	ll query(int a, int b) {
		ll ret = 0;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			int st = top[a];
			ret = seg.merge(ret, seg.query(in[st], in[a]));
			a = par[st];
		}
		if (dep[a] > dep[b]) swap(a, b);
		ret = seg.merge(ret, seg.query(in[a], in[b]));
		return ret;
	}
};