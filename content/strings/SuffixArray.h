/**
 * Description: Constructs the suffix array and LCP (Longest Common Prefix) array of a string.
 *  Suffix Array Time: $O(N \log N)$, where $N$ is the length of the string.
 *  LCP Array Time: $O(N)$.
 */

bool radixSort(vector<int>& rk, int k) {
    const int n = rk.size();
    int m = *max_element(rk.begin(), rk.end());
    if (n == m) return false;
    vector<int> sr(n), srk(n);
    vector<int> cnt(m + 1);

    vector<int> rkk(n);
    for (int i = 0; i < n; ++i) {
        if (i + k < n) rkk[i] = rk[i + k];
        else rkk[i] = 0;
    }

    for (auto i: rkk) ++cnt[i];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) srk[--cnt[rkk[i]]] = i;
    reverse(srk.begin(), srk.end());

    for (auto& i: cnt) i = 0;
    for (auto i: rk) ++cnt[i];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) {
        int j = srk[i];
        sr[--cnt[rk[j]]] = j;
    }

    vector<int> nrk(n);
    m = 1; nrk[sr[0]] = m;
    for (int i = 1; i < n; ++i) {
        int cur = sr[i], prv = sr[i - 1];
        if (rk[cur] != rk[prv] || rkk[cur] != rkk[prv]) ++m;
        nrk[cur] = m;
    }
    swap(nrk, rk);
    return true;
}

vector<int> getSuffixArray(const string& s) {
    const int n = s.size();
    const int m = 255;
    vector<int> cnt(m);
    for (auto i: s) cnt[i] = 1;
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];

    vector<int> rk(n);
    for (int i = 0; i < n; ++i) rk[i] = cnt[s[i]];
    int k = 1;
    while (radixSort(rk, k)) k *= 2;

    vector<int> sfx(n);
    for (int i = 0; i < n; ++i) sfx[rk[i] - 1] = i;
    return sfx;
}

vector<int> getLcp(const string& s, const vector<int>& sfx) {
	const int n = s.size();
	vector<int> inv(n), lcp(n);
	for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
	int h = 0;
	for(int i = 0; i < n; ++i) if (inv[i]) {
		int prv = sfx[inv[i] - 1];
		while (s[prv + h] == s[i + h]) ++h;
		lcp[inv[i]] = h;
		h = max(h - 1, 0);
	}
	return lcp;
}