#include "../utilities/template.h"

#include "../../content/graph/Dijkstra.h"

int main() {
	rep(it,0,50000) {
		int n = rand() % 8 + 1, m = rand() % 20;
		vector<vector<pair<int, ll>>> g(n);
		const ll INF = LLONG_MAX / 4;
		vector<vector<ll>> fw(n, vector<ll>(n, INF));
		rep(i,0,n) fw[i][i] = 0;
		rep(i,0,m) {
			int a = rand() % n, b = rand() % n;
			ll w = rand() % 10 == 0 ? 0 : rand() % 1000000;
			g[a].push_back({b, w});
			fw[a][b] = min(fw[a][b], w);
		}
		rep(k,0,n) rep(i,0,n) rep(j,0,n)
			fw[i][j] = min(fw[i][j], fw[i][k] + fw[k][j]);
		int s = rand() % n;
		vector<ll> d = dijkstra(g, s);
		rep(v,0,n) assert(d[v] == (fw[s][v] >= INF ? LLONG_MAX : fw[s][v]));
	}
	cout << "Tests passed!" << endl;
}
