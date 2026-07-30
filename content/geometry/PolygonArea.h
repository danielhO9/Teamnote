/**
 * Description: Computes twice the area of a simple polygon.
 *  Returns the absolute value of the area.
 * Time: $O(N)$, where $N$ is the number of vertices in the polygon.
 */
template<typename T>
T polygonArea2(const vector<Point<T>>& pts) {
	assert(!pts.empty());
	T ret = pts.back().cross(pts[0]);
	for (int i = 0; i + 1 < pts.size(); ++i) ret += pts[i].cross(pts[i + 1]);
	return abs(ret);
}