#include "../utilities/template.h"

#include "../../content/graph/CentroidDecomposition.h"

int main() {
	rep(it,0,20000) {
		int n = rand() % 40 + 1, mode = rand() % 3;
		vector<vi> g(n);
		rep(i,1,n) {
			int p = mode == 0 ? rand() % i : mode == 1 ? i-1 : max(0, i-1-rand()%3);
			g[i].push_back(p), g[p].push_back(i);
		}
		CentroidDecomposition cd(g);

		// all-pairs distances
		vector<vi> d(n, vi(n, 1e9));
		rep(s,0,n) {
			d[s][s] = 0;
			queue<int> q;
			q.push(s);
			while (!q.empty()) {
				int v = q.front(); q.pop();
				for (int u : g[v]) if (d[s][u] > d[s][v] + 1) {
					d[s][u] = d[s][v] + 1;
					q.push(u);
				}
			}
		}

		int roots = 0, maxDepth = 0;
		vi depth(n);
		rep(v,0,n) {
			roots += cd.cpar[v] == -1;
			int x = v, dep = 1;
			while (cd.cpar[x] != -1) x = cd.cpar[x], dep++;
			depth[v] = dep;
			maxDepth = max(maxDepth, dep);
		}
		assert(roots == 1);
		int lg = 1;
		while ((1 << lg) <= n) lg++;
		assert(maxDepth <= lg);

		// the centroid-tree LCA must lie on the tree path
		rep(u,0,n) rep(v,0,n) {
			vector<bool> anc(n);
			for (int x = u; x != -1; x = cd.cpar[x]) anc[x] = 1;
			int l = v;
			while (!anc[l]) l = cd.cpar[l];
			assert(d[u][l] + d[l][v] == d[u][v]);
		}
	}
	cout << "Tests passed!" << endl;
}
