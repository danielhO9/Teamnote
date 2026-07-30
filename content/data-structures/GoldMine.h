/**
 * Description: Segment Tree implementation for solving the Gold Mine problem.
 *  Supports range queries and point updates efficiently.
 * Time: Both update and query operations are $O(\log N)$.
 */

struct Node {
	ll lmx, rmx, mx, sm;

	Node() = default;
	Node(ll x): lmx(x), rmx(x), mx(x), sm(x) {}
};

struct SegmentTree {
	vector<ll> arr;
	vector<Node> tree;
	int sz;

	inline Node merge(const Node& l, const Node& r) {
		Node ret{};
		ret.lmx = max(l.lmx, l.sm + r.lmx);
		ret.rmx = max(r.rmx, r.sm + l.rmx);
		ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
		ret.sm = l.sm + r.sm;
		return ret;
	}
	SegmentTree() = default;
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int) ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = Node {arr[start]};
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] = Node {arr[index]};
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return Node {INT32_MIN};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(l, r);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};