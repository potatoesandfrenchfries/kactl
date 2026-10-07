/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Shortest paths from \texttt{s} with non-negative edge
 * weights. \texttt{g[v]} holds \{neighbour, weight\} pairs. Unreachable
 * nodes get distance \texttt{LLONG\_MAX}. Use BellmanFord for negative
 * weights.
 * Time: O(E \log V)
 * Status: stress-tested
 */
#pragma once

vector<ll> dijkstra(vector<vector<pair<int, ll>>>& g, int s) {
	vector<ll> d(sz(g), LLONG_MAX);
	priority_queue<pair<ll, int>> q;
	d[s] = 0, q.push({0, s});
	while (!q.empty()) {
		auto [w, v] = q.top(); q.pop();
		if (-w > d[v]) continue;
		for (auto [u, c] : g[v]) if (d[u] > d[v] + c)
			d[u] = d[v] + c, q.push({-d[u], u});
	}
	return d;
}
