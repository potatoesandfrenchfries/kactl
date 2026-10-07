/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Centroid decomposition of a tree. \texttt{cpar[v]} is the
 * parent of $v$ in the centroid tree (-1 for the root), which has depth
 * $O(\log n)$. For any $u,v$, their LCA in the centroid tree lies on
 * the $u$-$v$ path, so path queries can be answered by walking up
 * \texttt{cpar} from both ends. To process a component, DFS from the
 * centroid $c$ over vertices that are not \texttt{done}.
 * Usage: CentroidDecomposition cd(g); // g is adjacency list
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct CentroidDecomposition {
	vector<vi>& g;
	vi cpar, sub;
	vector<bool> done;
	CentroidDecomposition(vector<vi>& g) : g(g), cpar(sz(g)),
			sub(sz(g)), done(sz(g)) { build(0, -1); }
	int calc(int v, int p) {
		sub[v] = 1;
		for (int u : g[v]) if (u != p && !done[u])
			sub[v] += calc(u, v);
		return sub[v];
	}
	int find(int v, int p, int n) {
		for (int u : g[v]) if (u != p && !done[u] && sub[u]*2 > n)
			return find(u, v, n);
		return v;
	}
	void build(int v, int p) {
		int c = find(v, -1, calc(v, -1));
		cpar[c] = p, done[c] = 1;
		// process the component of c here
		for (int u : g[c]) if (!done[u]) build(u, c);
	}
};
