/**
 * Description: Offline Dynamic Connectivity using a segment tree and rollbackable Union-Find.
 *  Handles edge additions/removals and connectivity queries offline.
 *  The timeline of queries and edge updates is divided using a segment tree.
 *  A rollbackable Union-Find data structure is used to maintain connectivity information.
 * Time: $O(Q \log Q \cdot \alpha(N))$, where $Q$ is the number of queries/updates and $N$ is the number of vertices.
 */

// 0-index
struct UF {
	vector<int> par, rk;
    vector<tuple<int, int, int>> st;

    UF() = default;
	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
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

vector<vector<Edge>> tree;
vector<pair<int, int>> queries;
vector<int> ans;

void update(int node, int start, int end, Edge e) {
    if (e.s > end || e.e < start) return;
    if (e.s <= start && end <= e.e) {
        tree[node].push_back(e);
        return;
    }
	int mid = (start + end) / 2;
    update(node * 2, start, mid, e);
    update(node * 2 + 1, mid + 1, end, e);
}

void dnc(int node, int start, int end) {
    int t = uf.time();
	for (auto i: tree[node]) uf.merge(i.u, i.v);
	if (start == end) {
        if (uf.find(queries[start].first) == uf.find(queries[start].second)) ans[start] = lv;
	} else {
		int mid = (start + end) / 2;
		dnc(node * 2, start, mid);
		dnc(node * 2 + 1, mid + 1, end);
	}
    uf.rollback(t);
}

int N, Q;

void solve() {
    uf = UF {N};

    ans = vector<int>(Q, -1);
    int h = (int)ceil(log2(Q));
	int tree_size = (1 << (h + 1));
    tree.resize(tree_size);

    for (auto& i: bridges) update(1, 0, q - 1);

    dnc(1, 0, q - 1);
}