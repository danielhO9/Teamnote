/**
 * Description: Computes the center and radius of the circumcircle of a triangle.
 * Time: $O(1)$.
 */
// circumcircle center
template<typename T>
Circle<T> ccCenter(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
	Point<T> nb = c - a, nc = b - a;
	Point<T> na = a;
	Point<T> center = na + (nb * nc.dist2() - nc * nb.dist2()).perp() / nb.cross(nc) / 2;
	T r = (b - a).dist() * (c - b).dist() * (a - c).dist() / (double) abs((b - a).cross(c - a)) / 2.0;
	return {center, r};
}