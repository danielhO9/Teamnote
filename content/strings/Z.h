/**
 * Description: Z-Algorithm for pattern matching and substring search.
 *  Computes the Z-array, where Z[i] is the length of the longest substring starting from S[i] that matches a prefix of S.
 * Time: $O(N)$, where $N$ is the length of the string.
 */

vector<int> getZ(const string& s) {
	const int n = s.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r) z[i] = min(r - i, z[i - l]);
		while (s[i + z[i]] == s[z[i]]) ++z[i];
		if (i > r) l = i;
		r = max(r, i + z[i] - 1);
	}
	return z;
}