#include "../utilities/template.h"

#include "../../content/graph/Kruskal.h"

// Prim on each component
ll prim(int n, vector<array<ll, 3>>& e) {
	vector<vector<ll>> w(n, vector<ll>(n, -1));
	for (auto& x : e) {
		int a = (int)x[1], b = (int)x[2];
		if (w[a][b] == -1 || x[0] < w[a][b]) w[a][b] = w[b][a] = x[0];
	}
	vector<bool> in(n);
	ll total = 0;
	rep(r,0,n) if (!in[r]) {
		vector<ll> best(n, LLONG_MAX);
		best[r] = 0;
		while (true) {
			int v = -1;
			rep(i,0,n) if (!in[i] && best[i] != LLONG_MAX
					&& (v == -1 || best[i] < best[v])) v = i;
			if (v == -1) break;
			in[v] = 1, total += best[v];
			rep(u,0,n) if (!in[u] && w[v][u] != -1)
				best[u] = min(best[u], w[v][u]);
		}
	}
	return total;
}

int main() {
	rep(it,0,50000) {
		int n = rand() % 9 + 1, m = rand() % 20;
		vector<array<ll, 3>> e;
		rep(i,0,m) {
			int a = rand() % n, b = rand() % n;
			e.push_back({rand() % 20, a, b});
		}
		auto [w, ids] = kruskal(n, e);
		assert(w == prim(n, e));

		// chosen edges are a forest with the right weight
		vi p(n);
		iota(all(p), 0);
		function<int(int)> f = [&](int x) { return p[x] == x ? x : f(p[x]); };
		ll sum = 0;
		for (int i : ids) {
			int a = f((int)e[i][1]), b = f((int)e[i][2]);
			assert(a != b);
			p[a] = b;
			sum += e[i][0];
		}
		assert(sum == w);
	}
	cout << "Tests passed!" << endl;
}
