/**
 * Description: Checks if a point is inside a convex polygon.
 *  Returns true if the point is inside, false otherwise.
 * Time: $O(\log N)$, where $N$ is the number of vertices in the polygon.
 */
template <typename T>
bool inConvex(const Point<T>& p, const vector<Point<T>>& pts) {
    assert(pts.size() >= 3);
    if (pts[0].cross(pts[1], p) < 0 || pts[0].cross(pts.back(), p) > 0) return false;
    int l = 0, r = pts.size(), mid; --r;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        if (pts[0].cross(p, pts[mid]) >= 0) r = mid;
        else l = mid;
    }
    return pts[r - 1].cross(pts[r], p) > 0;
}