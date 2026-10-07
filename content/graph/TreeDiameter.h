/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Diameter of a tree with non-negative edge weights.
 * The farthest node from any node is an endpoint of a diameter.
 * Returns \{length, \{a, b\}\}. \texttt{g[v]} holds \{neighbour, weight\}.
 * Time: O(N)
 * Status: stress-tested
 */
#pragma once

pair<ll, pii> treeDiameter(vector<vector<pair<int, ll>>>& g) {
	vector<ll> d(sz(g));
	auto far = [&](int s) {
		fill(all(d), -1);
		vi st = {s};
		d[s] = 0;
		int best = s;
		while (!st.empty()) {
			int v = st.back(); st.pop_back();
			if (d[v] > d[best]) best = v;
			for (auto [u, c] : g[v]) if (d[u] < 0)
				d[u] = d[v] + c, st.push_back(u);
		}
		return best;
	};
	int a = far(0), b = far(a);
	return {d[b], {a, b}};
}
