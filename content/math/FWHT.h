/**
 * Description: Fast Walsh-Hadamard Transform (FWHT) for XOR, AND, OR convolutions.
 *  Supports efficient computation of subset convolutions.
 * Time: $O(N \log N)$, where $N$ is the size of the input.
 */

void fwht_or(vector<ll> &a, bool inv) {
    ll n = a.size();
    ll dir = inv ? -1 : 1;
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                a[l + h + i] += dir * a[l + i];
            }
        }
    }
}

void fwht_and(vector<ll> &a, bool inv) {
    ll n = a.size();
    ll dir = inv ? -1 : 1;
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                a[l + i] += dir * a[l + h + i];
            }
        }
    }
}

void fwht_xor(vector<ll> &a, bool inv) {
    ll n = a.size();
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                ll t = a[l + h + i];
                a[l + h + i] = a[l + i] - t;
                a[l + i] += t;
                if (inv) a[l + h + i] /= 2, a[l + i] /= 2;
            }
        }
    }
}

vector<ll> convolute(vector<ll>& A, vector<ll>& B) {
    vector<ll> a(A.begin(), A.end()), b(B.begin(), B.end());

    ll n = max(a.size(), b.size());
    ll i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);

    fwht_xor(a, false);
    fwht_xor(b, false);
    for (ll i = 0; i < n; i++) a[i] *= b[i];
    fwht_xor(a, true);
    return a;
}