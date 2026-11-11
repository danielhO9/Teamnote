/**
 * Description: Fast Fourier Transform (FFT) for polynomial multiplication.
 *  Supports efficient multiplication of large polynomials.
 * Time: $O(N \log N)$, where $N$ is the size of the input.
 */
typedef complex<double> base;

void fft(vector<base>& a, bool inv) {
    ll n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? M_PI / i : -M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

vector<ll> multiply(const vector<ll>& A, const vector<ll>& B) {
    if (A.empty() || B.empty()) return {};
    vector<base> f(A.begin(), A.end()), g(B.begin(), B.end());

    int sz = f.size() + g.size() - 1;
    
    int n = 1;
    while (n < sz) n <<= 1;
    f.resize(n); g.resize(n);

    fft(f, false); fft(g, false);
    for (int i = 0; i < n; ++i) f[i] = f[i] * g[i];
    fft(f, true);

    vector<ll> result(sz);
    for (int i = 0; i < sz; ++i)
      result[i] = llround(f[i].real());
    return result;
}
