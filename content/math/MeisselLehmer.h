/**
 * Description: Meissel-Lehmer Algorithm for counting primes up to a given number $x$.
 *  Combines sieve methods with recursive calculations for efficiency.
 * Time: $O(x^{2/3} / \log x)$ for preprocessing, $O(x^{1/2})$ for queries.
 */
const int MAXV = 1e8+10;
const int MAXV2 = 1e8 + 1e4 + 10;
const int MAXLEAF = 8e5;

int pi[MAXV];
bool isPrime[MAXV];
vector<int> p;

void init() {
    p.push_back(1);
    p.push_back(2);
    isPrime[2] = true;
    for (int i = 3; i < MAXV; i += 2) isPrime[i] = true;
    int threshold = INT32_MAX / 3;
    for (int i = 3; i < MAXV; i += 2) if (isPrime[i] && i <= threshold) {
        for (int j = i * 3; j < MAXV; j += (i << 1)) isPrime[j] = false;
        p.push_back(i);
    }
    for (int i = 2; i < MAXV; ++i) pi[i] = pi[i - 1] + isPrime[i];
}

struct Node {
    ll n;
    int b;
    int sgn;
};

int sz;
bool arr[MAXV2];

int tree[MAXLEAF];
Node leaf[MAXLEAF];

void update(int i, int dif) { while (i < sz) { tree[i] += dif; i += (i & -i); } }
int query(int i) { int ret = 0; while (i > 0) { ret += tree[i]; i -= (i & -i); } return ret; }

ll phi(const ll x, const int a) {
    ll ret = 0;
    int c = cbrt(0.5 + x);
    for (int i = 1; i <= x / c; ++i) arr[i] = false;
    int leaf_sz = 0;
    int mxx = INT32_MIN;
    vector<ll> limn;
    queue<Node> q;
    q.push(Node {1ll, a, 1});
    vector<int> v;
    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        if (cur.b == 0) {
            ret += (x / cur.n) * cur.sgn;
            continue;
        }
        if (cur.n >= c) {
            int xx = x / cur.n;
            if (xx < p[cur.b] * p[cur.b]) {
                ret += (pi[xx] - cur.b + 1) * cur.sgn;
                continue;
            }
            leaf[leaf_sz++] = Node {xx, cur.b, cur.sgn};
            mxx = max(mxx, xx);
            v.push_back(xx);
            limn.push_back(mxx);
            continue;
        }
        q.push(Node {cur.n, cur.b - 1, cur.sgn});
        q.push(Node {cur.n * p[cur.b], cur.b - 1, -cur.sgn});
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sz = v.size() + 1;
    for (int i = 1; i <= v.size(); ++i) tree[i] = 0;
    int pidx = 0, vidx = 0, dif = 0;
    for (int i = leaf_sz - 1; i >= 0; --i) {
        const Node& cur = leaf[i];
        while (pidx < cur.b) {
            ++pidx;
            vidx = 0, dif = 0;
            for (int j = p[pidx]; j <= limn[i]; j += p[pidx]) if (!arr[j]) {
                arr[j] = true;
                if (v[vidx] < j && dif) {
                    update(vidx + 1, dif);
                    dif = 0;
                }
                while (v[vidx] < j) ++vidx;
                ++dif;
            }
            if (dif) update(vidx + 1, dif);
        }
        int idx = lower_bound(v.begin(), v.end(), cur.n) - v.begin();
        ret += (cur.n - query(idx + 1)) * cur.sgn;
    }
    return ret;
}

ll getPi(ll x) {
    if (x < MAXV) return pi[x];
    int c = cbrt(0.5 + x), s = sqrt(0.5 + x);
    int a = pi[c];
    ll ret = phi(x, a) + a - 1;
    for (int i = a + 1; i <= pi[s]; ++i) ret -= getPi(x / p[i]) - i + 1;
    return ret;
}