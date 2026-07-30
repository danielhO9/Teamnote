/**
 * Description: Extended Euclidean Algorithm to find integers x and y such that ax + by = gcd(a, b).
 *  Returns gcd(a, b) along with x and y.
 * Time: $O(\log \min(a, b))$.
 */
tuple<ll, ll, ll> extended_euclidean(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x, y] = extended_euclidean(b, a % b);
    return {g, y, x - (a / b) * y};
}