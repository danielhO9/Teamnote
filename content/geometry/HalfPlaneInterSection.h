/**
 * Description: Computes the intersection of half-planes defined by a set of lines.
 *  Returns the vertices of the intersection polygon in counter-clockwise order.
 * Time: $O(N \log N)$, where $N$ is the number of lines.
 */
// half plane intersection(convex)
template<typename T>
vector<Point<T>> hpi(vector<Line<T>> lines) {
	// intersection of a, b is not part of c's half plane
	auto bad = [&](Line<T>& a, Line<T>& b, Line<T>& c) {
		auto v = a.lineInter(b);
		if (v.first != 1) return false;
		return c.s.cross(c.e, v.second) <= EPS;
	};
	sort(lines.begin(), lines.end());
	deque<Line<T>> dq;
	for (int i = 0; i < lines.size(); ++i) {
		while(dq.size() >= 2 && bad(dq[(int) dq.size() - 2], dq.back(), lines[i])) dq.pop_back();
		while(dq.size() >= 2 && bad(dq[0], dq[1], lines[i])) dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), lines[i], dq[0])) dq.push_back(lines[i]);
	}
	vector<Point<T>> ret;
	if (dq.size() >= 3) for (int i = 0; i < dq.size(); ++i) {
		int j = (i + 1) % dq.size();
		auto v = dq[i].lineInter(dq[j]);
		if (v.first == 1) ret.push_back(v.second);
	}
	return ret;
}