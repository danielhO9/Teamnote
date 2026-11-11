/**
 * Description: Circle structure with basic operations.
 *  Includes methods to check if a point is inside the circle.
 * Time: $O(1)$ per operation.
 */
const double EPS = 1e-9;

template<typename T>
struct Point {
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(const Point& p) const {
	  return tie(x, y) < tie(p.x, p.y);
	}
	bool operator==(const Point& p) const {
	  return tie(x, y) == tie(p.x, p.y);
	}
	bool operator!= (const Point& p) const {
	  return !(*this == p); }
	Point operator+ (const Point& p) const {
	  return Point(x + p.x, y + p.y); }
	Point operator- (const Point& p) const {
	  return Point(x - p.x, y - p.y); }
	Point operator* (T d) const { return Point(x * d, y * d); }
	Point operator/(T d) const { return Point(x / d, y / d); }
	friend istream& operator>>(istream& in, Point<T>& p) {
	  in >> p.x >> p.y;
	  return in;
	}
	friend ostream& operator<<(ostream& out, Point<T>& p) {
	  out << p.x << ' ' << p.y;
	  return out;
	}
	T dot(const Point& p) const { return x * p.x + y * p.y; }
	T cross(const Point& p) const { return x * p.y - y * p.x; }
	T cross(const Point& a, const Point& b) const {
	  return (a - *this).cross(b - *this);
	}
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const {
	  return atan2(y, x);
	} // angle to x-axis in interval [-pi, pi]
	// makes dist() = 1
	Point unit() const { return *this / dist(); }
	// rotates +90 degrees
	Point perp() const { return Point(-y, x); }
	Point normal() const { return perp().unit(); }
	// returns point rotated a radians ccw around the origin
	Point rotate(double a) const {
	  return Point(x * cos(a) - y * sin(a),
	               x * sin(a) + y * cos(a));
	}
};

template<typename T>
struct Circle {
	Point<T> c; T r;
	bool inCircle(const Point<T>& p) const {
	  return (p - c).dist() < r * (1 + EPS);
	}
};