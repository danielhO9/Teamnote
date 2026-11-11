/**
 * Description: 2D Fenwick Tree supports point updates and prefix queries in a 2D grid.
 *  Useful for maintaining cumulative sums in two dimensions efficiently.
 * Time: Both operations are $O(\log N \cdot \log M)$, where $N$ and $M$ are the dimensions of the grid.
 */
// 1-index
struct Fenwick2D {
    int n, m;
    vector<vector<ll>> tree;

    Fenwick2D(int n, int m): n(n), m(m) {
        tree.resize(n);
        for (int i = 0; i < n; ++i) tree[i].resize(m);
    }
    void update(int y, int x, ll dif) {
        for (int i = y; i < n; i += (i & -i))
            for (int j = x; j < m; j += (j & -j))
              tree[i][j] += dif;
    }
    ll query(int y, int x) {
        ll ret = 0;
        for (int i = y; i; i -= (i & -i))
            for (int j = x; j; j -= (j & -j))
              ret += tree[i][j];
        return ret;
    }
};