/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore (shortest paths over residues)
 * Description: Largest integer that is not a non-negative combination
 * of the positive integers \texttt{a}, or -1 if every integer is
 * (e.g. if 1 is in \texttt{a}). Requires $\gcd(a_i) = 1$.
 * For two coprime values, the answer is $ab-a-b$ and exactly
 * $(a-1)(b-1)/2$ non-negative integers are not representable.
 * Time: O(nm \log m), where $m = \min a_i$
 * Status: stress-tested
 */
#pragma once

ll frobenius(vector<ll> a) {
	ll m = *min_element(all(a));
	vector<ll> d(m, LLONG_MAX); // min sum with sum % m = i
	priority_queue<pair<ll, int>> q;
	d[0] = 0, q.push({0, 0});
	while (!q.empty()) {
		auto [w, v] = q.top(); q.pop();
		if (-w > d[v]) continue;
		for (ll c : a) {
			int u = int((v + c) % m);
			if (d[u] > d[v] + c) d[u] = d[v] + c, q.push({-d[u], u});
		}
	}
	return *max_element(all(d)) - m;
}
