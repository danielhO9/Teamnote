/**
 * Description: Computes the diameter of a convex hull using rotating calipers.
 *  Returns the pair of points that are farthest apart.
 * Time: $O(N)$, where $N$ is the number of points in the convex hull.
 */
// rotating calipers(convex)
template<typename T>
pair<Point<T>, Point<T>> hullDiameter(vector<Point<T>>& pts) {
	int n = pts.size();
	if (n == 0) return {Point<T>(0, 0), Point<T>(0, 0)};
	if (n == 1) return {pts[0], pts[0]};
	pair<T, pair<Point<T>, Point<T>>> res({0, {pts[0], pts[0]}});
	int j = 1;
	for (int i = 0; i < j; ++i) {
		while (true) {
			res = max(res, {(pts[i] - pts[j]).dist2(), {pts[i], pts[j]}});
			if ((pts[(j + 1) % n] - pts[j]).cross(pts[i + 1] - pts[i]) >= 0) break;
			j = (j + 1) % n;
		}
	}
	return res.second;
}