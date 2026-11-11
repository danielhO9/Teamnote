/**
 * Description: Polynomial and formal power series arithmetic modulo $998244353$. Store coefficients in ascending degree order. Use divmod for Euclidean division and operator/ for truncated series division.
 * Time: Let $L$ be the largest input or requested coefficient count. NTT, multiplication, division, divmod, series inverse, log and exp take $O(L \log(2L))$. Derivative and integral take $O(L)$ for the fixed modulus (one modular power per integrated coefficient).
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// MOD = k * 2^b + 1; max NTT length = 2^b.
// 1004535809 = 479 * 2^21 + 1, ROOT = 3
//  998244353 = 119 * 2^23 + 1, ROOT = 3
//  754974721 =  45 * 2^24 + 1, ROOT = 11
//  167772161 =   5 * 2^25 + 1, ROOT = 3
//  469762049 =   7 * 2^26 + 1, ROOT = 3
// 2013265921 =  15 * 2^27 + 1, ROOT = 31

typedef vector<ll> Poly;
const ll MOD = 998244353, ROOT = 3;

Poly operator*(Poly f, Poly g);
Poly operator/(Poly f, Poly g);

ll modpow(ll a, ll b) {
	if (b == 0) return 1;
	ll half = modpow(a, b >> 1);
	half = (half * half) % MOD;
	if (b & 1) return (half * a) % MOD;
    else return half;
}

void ntt(Poly& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        ll w = modpow(ROOT, (MOD - 1) / (i << 1));
        if (inv) w = modpow(w, MOD - 2);
        for (int j = 0; j < n; j += i << 1) {
            ll th = 1ll;
            for (int k = 0; k < i; k++) {
                ll tmp = a[i + j + k] * th % MOD;
                a[i + j + k] = a[j + k] - tmp;
				if (a[i + j + k] < 0) a[i + j + k] += MOD;
                a[j + k] += tmp;
				if (a[j + k] >= MOD) a[j + k] -= MOD;
                th = th * w % MOD;
            }
        }
    }
    if (inv) {
		ll ninv = modpow(n, MOD - 2);
        for (int i = 0; i < n; i++) a[i] = a[i] * ninv % MOD;
    }
}

Poly deriv(Poly f) {
    if (f.size() <= 1) return Poly{0};
    for (int i = 1; i < f.size(); ++i) {
        f[i - 1] = (f[i] * i) % MOD;
    }
    f.resize(f.size() - 1);
    return f;
}

Poly polyint(Poly f) {
    int n = f.size();
    f.resize(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        f[i + 1] = f[i] * modpow(i + 1, MOD - 2) % MOD;
    }
    f[0] = 0;
    return f;
}

Poly inv(Poly f, int N) {
    assert(f.size() && f[0] != 0);
    Poly g; g.push_back(modpow(f[0], MOD - 2));
    int n = 1;
    while (n < N) {
        n <<= 1;

        Poly fc = f; fc.resize(n);

        Poly m = g * fc; m.resize(n);
        for (int i = 0; i < n; ++i) m[i] = (MOD - m[i]) % MOD;
        m[0] = (m[0] + 2) % MOD;

        g = g * m; g.resize(n);
    }
    g.resize(N);
    return g;
}

Poly polylog(Poly f, int N) {
    assert(f.size() && f[0] != 0);

    auto g = polyint(deriv(f) * inv(f, N));
    g.resize(N);
    return g;
}

Poly polyexp(Poly f, int N) {
    assert(f.size() && f[0] == 0);
    Poly g; g.push_back(1);
    int n = 1;
    while (n < N) {
        n <<= 1;

        Poly fc = f; fc.resize(n);
        fc[0] = (fc[0] + 1) % MOD;

        Poly logg = polylog(g, n);

        for (int i = 0; i < n; ++i)
          fc[i] = (MOD + fc[i] - logg[i]) % MOD;

        g = g * fc; g.resize(n);
    }
    g.resize(N);
    return g;
}

Poly operator*(Poly f, Poly g) {
    assert(f.size() && g.size());

    int sz = f.size() + g.size() - 1;
    
    int n = 1;
    while (n < sz) n <<= 1;
    f.resize(n); g.resize(n);

    ntt(f, false); ntt(g, false);
    for (int i = 0; i < n; ++i) f[i] = f[i] * g[i] % MOD;
    ntt(f, true);

    f.resize(sz);
    return f;
}

Poly operator/(Poly f, Poly g) {
    assert(f.size() && g.size());

    g = inv(g, f.size());
    auto h = f * g; h.resize(f.size());
    return h;
}

pair<Poly, Poly> divmod(Poly f, Poly g) {
    while (!f.empty() && f.back() == 0) f.pop_back();
    while (!g.empty() && g.back() == 0) g.pop_back();

    assert(!g.empty());

    if (f.size() < g.size())
      return {{0}, f.empty() ? Poly{0} : f};

    int k = f.size() - g.size() + 1;

    Poly revf(f.rbegin(), f.rend());
    Poly revg(g.rbegin(), g.rend());

    revf.resize(k);
    revg.resize(k);

    Poly h = revf / revg;
    reverse(h.begin(), h.end());

    Poly gh = g * h;
    for (int i = 0; i < gh.size(); ++i)
      f[i] = (f[i] - gh[i] + MOD) % MOD;

    while (f.size() > 1 && f.back() == 0) f.pop_back();
    return {h, f};
}
