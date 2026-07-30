/**
 * Description: Computes the convex hull of a set of points.
 *  Returns the vertices of the convex hull in counter-clockwise order.
 * Time: $O(N \log N)$, where $N$ is the number of points.
 */
template<typename P>
vector<P> convexHull(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	P unit = pts[0];
	for (auto& i: pts) i = i - unit;
	sort(next(pts.begin()), pts.end(), [](const P& a, const P& b) {
		if (a.cross(b) == 0) {
			if (a.x == b.x) return a.y < b.y;
			return a.x < b.x;
		}
		return a.cross(b) > 0;
	});
	vector<P> h;
	h.push_back(pts[0]); h.push_back(pts[1]);
	for (int i = 2; i < pts.size(); ++i) {
		while (h.size() >= 2) {
			P b = h.back(); h.pop_back();
			P a = h.back();
			if (a.cross(b, pts[i]) > 0) {
				h.push_back(b);
				break;
			}
		}
		h.push_back(pts[i]);
	}
	for (auto& i: h) i = i + unit;
	return h;
}