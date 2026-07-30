/**
 * Description: Fenwick Tree (Binary Indexed Tree) supports point updates and prefix queries.
 *  Useful for maintaining cumulative sums efficiently.
 * Time: Both operations are $O(\log N)$.
 */

// 1-index
struct Fenwick {
    vector<ll> tree;

    Fenwick() = default;
    Fenwick(int sz) { tree.resize(sz); }
    void update(int i, ll dif) { while (i < tree.size()) { tree[i] += dif; i += (i & -i); } }
    ll query(int i) {
        ll ret = 0;
        while (i > 0) { ret += tree[i]; i -= (i & -i); }
        return ret;
    }
};