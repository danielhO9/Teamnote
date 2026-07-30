/**
 * Description: Mo's Algorithm for answering range queries efficiently.
 *  Sorts queries in a specific order to minimize the number of add/del operations.
 * Time: $O((N + Q) \sqrt{N})$, where $N$ is the size of the array and $Q$ is the number of queries.
 */
int N, sqrtN, M;

struct Query {
	int s, e, idx;
};

void add(int idx, bool last);

void del(int idx, bool last);

void solve() {
	vector<Query> query;
	sqrtN = sqrt(N);
	sort(query.begin(), query.end(), [](const Query& a, const Query& b) {
		if (a.s / sqrtN == b.s / sqrtN) return a.e < b.e;
		return a.s / sqrtN < b.s / sqrtN;
	});

	vector<int> ans(M);
	int s = 1, e = 1;
	add(1, true);
	for (int i = 0; i < M; ++i) {
		while (e < query[i].e) add(++e, true);
		while (e > query[i].e) del(e--, true);
		while (s < query[i].s) del(s++, false);
		while (s > query[i].s) add(--s, false);
	}
	for (int i = 0; i < M; ++i) cout << ans[i] << '\n';
}