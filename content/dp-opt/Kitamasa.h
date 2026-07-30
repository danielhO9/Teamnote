/**
 * Description: Kitamasa's Algorithm for efficiently computing terms in a linear recurrence relation.
 *  Computes the $n$-th term modulo a given number.
 *  The recurrence relation coefficients $c_1, c_2, \dots, c_m$ must be provided, and the modulo must be a prime number.
 * Time: $O(M^2 \log N)$, where $M$ is the order of the recurrence and $N$ is the term to compute.
 */

const ll MOD = 1999; // Modulo value

ll a[1001]; // Initial terms of the recurrence relation
ll c[1001]; // Coefficients of the recurrence relation
ll d[1001]; // Temporary array for storing intermediate results
ll t[2001]; // Temporary array for polynomial multiplication

void kitamasa(ll n, int m) {
    if (n == 1) {
        d[1] = 1;
        for (int i = 2; i <= m; ++i) d[i] = 0;
        return;
    }
    if (n & 1) {
        kitamasa(n ^ 1, m);
        ll tmp = d[m];
        for (int i = m; i >= 1; --i) d[i] = (d[i - 1] + c[m - i + 1] * tmp) % MOD;
        return;
    }
    kitamasa(n >> 1, m);
    for (int i = 1; i <= 2 * m; ++i) t[i] = 0;
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) t[i + j] = (t[i + j] + d[i] * d[j]) % MOD;
    for (int i = 2 * m; i > m; --i) for (int j = 1; j <= m; ++j) t[i - j] = (t[i - j] + c[j] * t[i]) % MOD;
    for (int i = 1; i <= m; ++i) d[i] = t[i];
}