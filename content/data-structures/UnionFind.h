/**
 * Description: Union-Find (Disjoint Set Union) with path compression and union by rank.
 *  Supports efficient merging and finding of connected components.
 * Time: $O(\alpha(N))$ per operation, where $\alpha$ is the inverse Ackermann function.
 */
// 0-index
struct UF {
	vector<int> par, rk;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};