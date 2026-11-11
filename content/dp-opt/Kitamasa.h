/**
 * Description: Uses Polynomial.h. For $c=(0,c_1,\ldots,c_k)$, returns the coefficients of $x^n$ modulo the characteristic polynomial. Dot these with $A_0,\ldots,A_{k-1}$ to get $A_n$ (missing coefficients are zero).
 * Time: $O(k \log(2k) \log(n+2))$ for recurrence order $k$ and term index $n$, using NTT multiplication and polynomial division.
 */

// A_N = \sum c_{i}A_{N-i}
// f(x) = x^K - \sum c_{i}x^{K-i}
Poly kitamasa(Poly c, ll n){
    assert(c.size() && c[0] == 0);
    Poly res = {1};
    Poly xn = {0, 1};
    Poly f = c; f[0] = MOD - 1;
    reverse(f.begin(), f.end());
    for (int i = 0; i < f.size(); ++i)
      f[i] = (MOD - f[i]) % MOD;
    while (n) {
        if (n & 1) res = divmod(res * xn, f).second;
        xn = divmod(xn * xn, f).second;
        n >>= 1;
    }
    return res;
}
