/**
 * Description: Miller-Rabin Primality Test for checking if a number is prime.
 *  Probabilistic test with high accuracy for large numbers.
 * Time: $O(K \log^3 N)$, where $K$ is the number of iterations.
 */
typedef unsigned long long ull;

const vector<vector<__int128_t>> a = {
	{2, 7, 61},
	{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
};

__int128_t pow(__int128_t a, __int128_t b, __int128_t MOD) {
	a %= MOD;
	if (b == 0) return 1;
	__int128_t half = pow(a, b / 2, MOD);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

bool millerRabin(__int128_t n) {
	int type = (n > INT32_MAX);
	if (type == 1 && n < 40) {
		for (auto i: a[type]) if (i == n) return true;
		return false;
	}
	for (int i = 0; i < a[type].size(); ++i) {
		if (a[type][i] == n) return true;
		__int128_t k = n - 1;
		while (true) {
			__int128_t temp = pow(a[type][i], k, n);
			if (temp == n - 1) break;
			if (k % 2 == 1) {
				if (temp == 1) break;
				else return false;
			}
			k /= 2;
		}
	}
	return true;
}