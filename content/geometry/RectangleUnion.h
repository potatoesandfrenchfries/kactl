/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Area of the union of axis-aligned rectangles
 * \{x1, y1, x2, y2\}. A sweep-line over $x$: events are sorted by $x$,
 * and a segment tree over compressed $y$ keeps the covered length.
 * Reuse the pattern for other sweeps: sort events, update a structure
 * for each, and query it between consecutive $x$ values.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

ll rectangleUnion(vector<array<int, 4>> r) {
	vi ys;
	vector<array<int, 4>> ev; // {x, +1 open / -1 close, y1, y2}
	for (auto& q : r) if (q[0] < q[2] && q[1] < q[3]) {
		ys.push_back(q[1]), ys.push_back(q[3]);
		ev.push_back({q[0], 1, q[1], q[3]});
		ev.push_back({q[2], -1, q[1], q[3]});
	}
	if (ev.empty()) return 0;
	sort(all(ys)), ys.erase(unique(all(ys)), ys.end());
	sort(all(ev));
	int m = sz(ys) - 1; // elementary intervals [ys[i], ys[i+1])
	vi cnt(4 * m);
	vector<ll> cov(4 * m);
	function<void(int, int, int, int, int, int)> upd =
		[&](int v, int l, int h, int a, int b, int d) {
		if (b <= l || h <= a) return;
		if (a <= l && h <= b) cnt[v] += d;
		else {
			int mid = (l + h) / 2;
			upd(2*v, l, mid, a, b, d), upd(2*v+1, mid, h, a, b, d);
		}
		cov[v] = cnt[v] ? ys[h] - ys[l] :
			h - l == 1 ? 0 : cov[2*v] + cov[2*v+1];
	};
	ll area = 0;
	int px = ev[0][0];
	for (auto [x, d, a, b] : ev) {
		area += cov[1] * (x - px), px = x;
		int i = int(lower_bound(all(ys), a) - ys.begin());
		int j = int(lower_bound(all(ys), b) - ys.begin());
		upd(1, 0, m, i, j, d);
	}
	return area;
}
