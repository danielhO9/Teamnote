/**
 * Description: Persistent Segment Tree supports range queries and updates with versioning.
 *  Allows access to any previous version of the segment tree.
 * Time: Update $O(\log N)$, Query $O(\log N)$.
 */
struct Node { int l, r; ll val; };

struct PST {
	vector<Node> tree;
	vector<int> root; // 1-index (0: dummy)
	int sz;

	PST() = default;
	PST(int sz): sz(sz) {
        tree.resize(1);
        root.resize(1);
	}
    // p -> c
	void newRoot(int p, int c) {
        assert(p < root.size());
        while (root.size() <= c) root.push_back(0);
        root[c] = tree.size();
		tree.push_back(Node{tree[root[p]]});
        return;
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		tree[node].val += val;
		if (start == end) return;
		int mid = (start + end) / 2;
		if (index <= mid) {
			int lidx = tree[node].l;
			tree[node].l = tree.size();
			tree.push_back(Node{tree[lidx]});
			update(tree[node].l, start, mid, index, val);
		}
		if (index > mid) {
			int ridx = tree[node].r;
			tree[node].r = tree.size();
			tree.push_back(Node{tree[ridx]});
			update(tree[node].r, mid + 1, end, index, val);
		}
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node].val;
        int mid = (start + end) / 2;
		ll lsum = query(tree[node].l, start, mid, left, right);
		ll rsum = query(tree[node].r, mid + 1, end, left, right);
		return lsum + rsum;
	}
    int kth(int l, int r, int start, int end, ll k) {
        if (start == end) return start;
        ll tmp = tree[tree[r].l].val - tree[tree[l].l].val;
        int mid = (start + end) / 2;
        if (tmp >= k) return kth(tree[l].l, tree[r].l, start, mid, k);
        else return kth(tree[l].r, tree[r].r, mid + 1, end, k - tmp);
    }
    void update(int rt, int index, ll val) {
        assert(rt < root.size());
        update(root[rt], 0, sz - 1, index, val);
    }
	ll query(int rt, int left, int right) {
        assert(rt < root.size());
        return query(root[rt], 0, sz - 1, left, right);
    }
    int kth(int l, int r, int k) {
        assert(l - 1 < root.size() && r < root.size());
        return kth(root[l - 1], root[r], 0, sz - 1, k);
    }
};