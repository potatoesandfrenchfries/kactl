/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Minimum spanning tree (forest if disconnected) of a
 * graph with \texttt{n} nodes. Edges are \{weight, a, b\}. Returns the
 * total weight and the indices of the chosen edges.
 * Usage: vector<array<ll,3>> e = {{5, 0, 1}, {2, 1, 2}};
 * auto [w, ids] = kruskal(3, e);
 * Time: O(E \log E)
 * Status: stress-tested
 */
#pragma once

pair<ll, vi> kruskal(int n, vector<array<ll, 3>>& e) {
	vi id(sz(e)), p(n), res;
	iota(all(id), 0), iota(all(p), 0);
	sort(all(id), [&](int i, int j) {
		return e[i][0] < e[j][0]; });
	function<int(int)> f = [&](int x) {
		return p[x] == x ? x : p[x] = f(p[x]); };
	ll w = 0;
	for (int i : id) {
		int a = f(int(e[i][1])), b = f(int(e[i][2]));
		if (a != b) p[a] = b, w += e[i][0], res.push_back(i);
	}
	return {w, res};
}
