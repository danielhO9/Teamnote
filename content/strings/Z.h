/**
 * Description: Z-Algorithm for pattern matching and substring search.
 *  Computes the Z-array, where Z[i] is the length of the longest substring starting from S[i] that matches a prefix of S.
 * Time: $O(N)$, where $N$ is the length of the string.
 */

vector<int> getZ(const string& s) {
	const int n = s.size();
	if (n == 0) return {};
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i < r) z[i] = min(r - i, z[i - l]);
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}