/**
 * Description: Dijkstra's Algorithm for finding the shortest paths from a source vertex to all other vertices.
 *  Assumes non-negative edge weights.
 * Time: $O((V + E) \log V)$, where $V$ is the number of vertices and $E$ is the number of edges.
 */
const int MAX_V = 100001;
vector<pair<int, ll>> adj[MAX_V];

// time complexity: (V+E)logV
// V: maximum vertex + 1
vector<ll> dijkstra(int src, int V) {
	vector<ll> dist(V, LLONG_MAX);
	dist[src] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			ll nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}