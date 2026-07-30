/**
 * Description: Minimum Cost Maximum Flow using SPFA-based augmenting path algorithm.
 *  Computes the maximum flow with the minimum cost in a flow network.
 * Time: $O((V + E) \cdot F)$, where $V$ is the number of vertices, $E$ is the number of edges, and $F$ is the total flow.
 */
const ll INF = 987654321;

struct Edge {
	int vertex;
	ll capacity;
	ll cost;
	int reverse;
	ll flow = 0;
};

const int MAX_V = 502;
vector<Edge> adj[MAX_V];

void spfa(vector<int>& parent, vector<int>& ind, vector<bool>& inQ, vector<ll>& dis, int source) {
	for (auto& i: parent) i = -1;
	for (int i = 0; i < inQ.size(); ++i) inQ[i] = false;
	for (auto& i: dis) i = INF;
	queue<int> q;
	dis[source] = 0; inQ[source] = true; q.push(source);
	parent[source] = source;
	while (!q.empty()) {
		int here = q.front(); q.pop(); inQ[here] = false;
		for (int i = 0; i < adj[here].size(); ++i) {
			Edge& edge = adj[here][i];
			int there = edge.vertex;
			if (edge.capacity - edge.flow > 0 && dis[there] > dis[here] + edge.cost) {
				dis[there] = dis[here] + edge.cost;
				parent[there] = here;
				ind[there] = i;
				if (!inQ[there]) {
					q.push(there);
					inQ[there] = true;
				}
			}
		}
	}
}

// V: maximum vertex + 1
pair<ll, ll> networkFlow(int source, int sink, const int V) {
	for (int i = 0; i < V; ++i) for (Edge& j: adj[i]) j.flow = 0;
	ll totalFlow = 0;
	ll totalCost = 0;
	vector<int> parent(V), ind(V);
	vector<bool> inQ(V); vector<ll> dis(V);
	while (true) {
		spfa(parent, ind, inQ, dis, source);
		if (parent[sink] == -1) break;
		ll amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			Edge& edge = adj[parent[p]][ind[p]];
			amount = min(edge.capacity - edge.flow, amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			Edge& edge = adj[parent[p]][ind[p]];
			edge.flow += amount;
			adj[edge.vertex][edge.reverse].flow -= amount;
			totalCost += amount * edge.cost;
		}
		totalFlow += amount;
	}
	return make_pair(totalFlow, totalCost);
}

void addEdge(int s, int e, ll cap, ll dis) {
	adj[s].push_back({e, cap, dis, (int)adj[e].size()});
	adj[e].push_back({s, 0, -dis, (int)adj[s].size() - 1});
}