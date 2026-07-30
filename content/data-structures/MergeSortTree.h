/**
 * Description: Merge Sort Tree supports range queries to count elements satisfying a condition.
 *  Useful for answering range queries efficiently.
 * Time: Build $O(N \log N)$, Query $O(\log^2 N)$.
 */
struct MergeSortTree {
	vector<ll> arr;
	vector<vector<ll>> tree;
	int sz;

	MergeSortTree() = default;
	MergeSortTree(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<vector<ll>>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node].push_back(arr[start]);
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
			merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
		}
	}
	// # of element <= k
	ll query(int node, int start, int end, int left, int right, ll k) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
		ll lcnt = query(node * 2, start, (start + end) / 2, left, right, k);
		ll rcnt = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, k);
		return lcnt + rcnt;
	}
	ll query(int left, int right, ll k) { return query(1, 0, sz - 1, left, right, k); }
};