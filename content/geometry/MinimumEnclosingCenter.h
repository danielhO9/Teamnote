/**
 * Description: Computes the minimum enclosing circle for a set of points.
 *  Returns the center and radius of the circle.
 * Time: $O(N)$ on average.
 */
template<typename T>
Circle<T> mec(vector<Point<T>> pts) {
	shuffle(pts.begin(), pts.end(), mt19937(time(0)));
	Circle<T> c = {pts[0], 0};
	for (int i = 0; i < pts.size(); ++i) if (!c.inCircle(pts[i])) {
		c = {pts[i], 0};
		for (int j = 0; j < i; ++j) if (!c.inCircle(pts[j])) {
			c.c = (pts[i] + pts[j]) / 2;
			c.r = (c.c - pts[i]).dist();
			for (int k = 0; k < j; ++k) if (!c.inCircle(pts[k])) {
				c = ccCenter(pts[i], pts[j], pts[k]);
			}
		}
	}
	return c;
}