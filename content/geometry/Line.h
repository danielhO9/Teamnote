/**
 * Description: Line structure with basic operations.
 *  Includes methods for intersection, distance, and segment checks.
 * Time: $O(1)$ per operation.
 */
template<typename T>
struct Line {
	Point<T> s, e;
	explicit Line(Point<T> s = Point<T>(0, 0), Point<T> e = Point<T>(1, 0)) : s(s), e(e) { assert(s != e); }
	bool sinPos() const { return s.y == e.y ? s.x <= e.x : s.y <= e.y; } // angle in [0, pi)
	bool operator< (const Line<T>& l) const {
		return sinPos() != l.sinPos() ? sinPos() > l.sinPos() : (e - s).cross(l.e - l.s) >= 0;
	}
	// only direction, not segment
	bool operator== (const Line<T>& l) const { sinPos() == l.sinPos() && (e - s).cross(l.e - l.s) == 0; }
	Line operator+ (const Point<T>& p) const { return Line(s + p, e + p); }
	Line operator- (const Point<T>& p) const { return Line(s - p, e - p); }
	bool onSegment(const Point<ll>& p) const { return abs(p.cross(s, e)) == 0 && (s - p).dot(e - p) <= 0; }
	bool onSegment(const Point<double>& p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) < EPS; }
	double lineDist(const Point<T>& p) const { return (double)(e - s).cross(p - s) / (e - s).dist(); }
	double segDist(const Point<T>& p) const {
		double d = (e - s).dist2(), t = min(d, max(0.0, (double) (p - s).dot(e - s)));
		return ((p - s) * d - (e - s) * t).dist() / d;
	}
	pair<int, Point<T>> lineInter(const Line& l) const {
		auto d = (e - s).cross(l.e - l.s);
		if (d == 0) return {-(s.cross(e, l.s) == 0), Point<T>(0, 0)};
		auto p = l.s.cross(e, l.e), q = l.s.cross(l.e, s);
		return {1, (s * p + e * q) / d};
	}
	pair<int, Point<T>> segInter(const Line& l) const {
		auto sgn = [&](T x) { return (x > 0) - (x < 0); };
		auto oa = l.s.cross(l.e, s), ob = l.s.cross(l.e, e),
		oc = s.cross(e, l.s), od = s.cross(e, l.e);
		// Checks if intersection is single non-endpoint point
		if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
			return {1, (s * ob - e * oa) / (ob - oa)};
		set<Point<T>> spts;
		if (l.onSegment(s)) spts.insert(s);
		if (l.onSegment(e)) spts.insert(e);
		if (onSegment(l.s)) spts.insert(l.s);
		if (onSegment(l.e)) spts.insert(l.e);
		if (spts.size() == 1) return {1, *spts.begin()};
		if (spts.size() == 0) return {0, Point<T>(0, 0)};
		return {-1, Point<T>(0, 0)};
	}
};