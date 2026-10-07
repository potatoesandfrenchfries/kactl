#include "../utilities/template.h"

#include "../../content/graph/TreeDiameter.h"

int main() {
	rep(it,0,50000) {
		int n = rand() % 12 + 1;
		vector<vector<pair<int, ll>>> g(n);
		rep(i,1,n) {
			int p = rand() % 3 == 0 ? i - 1 : rand() % i;
			ll w = rand() % 5 == 0 ? 0 : rand() % 100;
			g[i].push_back({p, w});
			g[p].push_back({i, w});
		}
		// brute force: distances from every node
		ll best = 0;
		vector<vector<ll>> dist(n, vector<ll>(n, -1));
		rep(s,0,n) {
			vi st = {s};
			dist[s][s] = 0;
			while (!st.empty()) {
				int v = st.back(); st.pop_back();
				for (auto [u, c] : g[v]) if (dist[s][u] < 0)
					dist[s][u] = dist[s][v] + c, st.push_back(u);
			}
			rep(v,0,n) best = max(best, dist[s][v]);
		}
		auto [len, ends] = treeDiameter(g);
		assert(len == best);
		assert(dist[ends.first][ends.second] == best);
	}
	cout << "Tests passed!" << endl;
}
