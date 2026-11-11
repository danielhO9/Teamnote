/**
 * Description: Offline Dynamic Connectivity using a segment tree and rollbackable Union-Find.
 *  Supply N vertices, Q time steps, and bridges with inclusive active intervals.
 *  An edge added at s and removed at t has interval [s,t-1]; use Q-1 if never removed.
 *  Set queries[t] to a vertex pair or (-1,-1) for no query. After solve(),
 *  ans[t] is 1 if connected, 0 if disconnected, or -1 for no query.
 * Time: $O(N + (I \log(2Q) + Q)\log(2N))$ for $I$ active intervals.
 */

// 0-index
struct UF {
	vector<int> par, rk;
    vector<tuple<int, int, int>> st;

    UF() = default;
	UF(int sz) {
		par.resize(sz);
		rk.resize(sz);
		for (int i = 0; i < sz; ++i) par[i] = i;
	}
    int time() { return st.size(); }
    void rollback(int t) {
        while (st.size() > t) {
            auto [v, p, r] = st.back(); st.pop_back();
            par[v] = p;
            rk[v] = r;
        }
    }
	int find(int x) {
		if (par[x] == x) return x;
		return find(par[x]);
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
        st.push_back({x, par[x], rk[x]});
        st.push_back({y, par[y], rk[y]});
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
} uf;

struct Edge {
	int u, v, s, e;
};

vector<Edge> bridges;
vector<vector<Edge>> tree;
vector<pair<int, int>> queries;
vector<int> ans;

void update(int node, int start, int end, const Edge& e) {
    if (e.s > end || e.e < start) return;
    if (e.s <= start && end <= e.e) {
        tree[node].push_back(e);
        return;
    }
	int mid = (start + end) >> 1;
    update(node * 2, start, mid, e);
    update(node * 2 + 1, mid + 1, end, e);
}

void dnc(int node, int start, int end) {
    int t = uf.time();
	for (auto i: tree[node]) uf.merge(i.u, i.v);
	if (start == end) {
        auto [u, v] = queries[start];
        if (u >= 0) ans[start] = (uf.find(u) == uf.find(v));
	} else {
		int mid = (start + end) >> 1;
		dnc(node * 2, start, mid);
		dnc(node * 2 + 1, mid + 1, end);
	}
    uf.rollback(t);
}

int N, Q;

void solve() {
    assert(queries.size() == Q);
    uf = UF(N);
    ans.assign(Q, -1);
    tree.assign(4ULL * Q, {});
    if (Q == 0) return;
    for (const Edge& e : bridges) {
        if (e.s <= e.e) update(1, 0, Q - 1, e);
    }
    dnc(1, 0, Q - 1);
}
