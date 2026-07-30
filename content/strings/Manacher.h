/**
 * Description: Manacher's Algorithm for finding all palindromic substrings.
 *  Computes the radius of the largest palindrome centered at each position.
 * Time: $O(N)$, where $N$ is the length of the string.
 */

vector<int> manacher(const string& s) {
	const int n = s.size();
	vector<int> ret(n);
	int r = -1, p = -1;
	for (int i = 0; i < n; ++i) {
		if (i < r) ret[i] = min(ret[2 * p - i], r - i);
		while (i - ret[i] - 1 >= 0 && i + ret[i] + 1 < n && s[i - ret[i] - 1] == s[i + ret[i] + 1]) ++ret[i];
		if (r < i + ret[i]) {
			r = i + ret[i];
			p = i;
		}
	}
	return ret;
}

// radius = palindrome
vector<int> palindrome(const string& S) {
	// #a#b#c#d#e#
	string ts;
	for (auto i: S) {
		ts += '#';
		ts += i;
	}
	ts += '#';
	return manacher(ts);
}