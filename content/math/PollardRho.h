/**
 * Description: Pollard's Rho Algorithm for integer factorization.
 *  Efficient for finding non-trivial factors of large integers.
 *  The factors returned are not sorted.
 * Time: $O(N^{1/4})$ for most inputs.
 */
typedef unsigned long long ull;

random_device rd;
mt19937_64 gen(rd());

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

__int128_t gcd(__int128_t a, __int128_t b) {
	if (a < b) swap(a, b);
	__int128_t remainder;
	while (b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;
}

__int128_t f(__int128_t x, __int128_t c, __int128_t MOD) { return (x * x + c) % MOD; }

void pollardRho(__int128_t n, vector<ll>& ret) {
	if (n == 1) return;
	if (n % 2 == 0) {
		ret.push_back(2);
		pollardRho(n / 2, ret);
		return;
	}
	if (millerRabin(n)) {
		ret.push_back(n);
		return;
	}
	__int128_t a, b, c, g = n;
	do {
		if (g == n) {
			uniform_int_distribution<> dist1(2, n - 1);
			a = dist1(gen); b = a;
			uniform_int_distribution<> dist2(1, 20);
			c = dist2(gen);
		}
		a = f(a, c, n);
		b = f(f(b, c, n), c, n);
		g = gcd(a > b ? a - b : b - a, n);
	} while (g == 1);
	pollardRho(g, ret);
	pollardRho(n / g, ret);
}

vector<ll> factorization(__int128_t n) {
	vector<ll> ret;
	pollardRho(n, ret);
	return ret;
}