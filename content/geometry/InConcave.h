/**
 * Description: Checks if a point is inside a concave polygon.
 *  Returns true if the point is inside, false otherwise.
 * Time: $O(N)$, where $N$ is the number of vertices in the polygon.
 */
// time complexity: N
template <typename T>
bool inConcave(const Point<T>& pt, const vector<Point<T>>& pts) {
	vector<Line<ll>> lines;
	const int n = pts.size();
    for (int i = 0; i < n; ++i) lines.push_back(Line<ll>(pts[i], pts[(i + 1) % n]));
	Line<ll> line {pt, Point<ll> {pt.x + 1000000000ll, pt.y + 1}}; // non parallel
	for (auto j: lines) if (j.onSegment(pt)) return true;
	int cnt = 0;
	for (auto j: lines) {
		auto tmp = j.segInter(line).first;
		cnt += tmp;
	}
	if (cnt % 2) return true;
	else return false;
}