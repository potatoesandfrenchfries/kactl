/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: cp-algorithms.com/geometry/halfplane-intersection.html
 * Description: Intersection of half-planes, where each half-plane is
 * everything to the left of the directed line \texttt{L[0]->L[1]}.
 * Returns the vertices of the resulting convex polygon in ccw order, or
 * an empty vector if the intersection is empty (or degenerate).
 * Add a large bounding box so the result is always bounded.
 * Usage: vector<L> v = {{P(0,0), P(1,0)}, {P(1,1), P(0,1)}, ...};
 * vector<P> poly = halfPlanes(v);
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "lineIntersection.h"

typedef Point<double> P;
typedef array<P, 2> L;
vector<P> halfPlanes(vector<L> v) {
	auto d = [](L l) { return l[1] - l[0]; };
	auto up = [&](L l) { P p = d(l);
		return p.y > 0 || (p.y == 0 && p.x > 0); };
	sort(all(v), [&](L a, L b) {
		if (up(a) != up(b)) return up(a);
		return d(a).cross(d(b)) > 0;
	});
	deque<L> q;
	auto out = [](L l, P p) {
		return sideOf(l[0], l[1], p, 1e-9) < 0; };
	auto pt = [&](int i, int j) { // vertex between q[i], q[j]
		L a = q[i], b = q[j];
		return lineInter(a[0], a[1], b[0], b[1]).second;
	};
	auto back = [&]() { return pt(sz(q)-2, sz(q)-1); };
	for (L h : v) {
		while (sz(q) > 1 && out(h, back())) q.pop_back();
		while (sz(q) > 1 && out(h, pt(0, 1))) q.pop_front();
		if (sz(q) && abs(d(h).cross(d(q.back()))) < 1e-9) {
			if (d(h).dot(d(q.back())) < 0) return {};
			if (!out(h, q.back()[0])) continue;
			q.pop_back();
		}
		q.push_back(h);
	}
	while (sz(q) > 2 && out(q[0], back())) q.pop_back();
	while (sz(q) > 2 && out(q.back(), pt(0, 1))) q.pop_front();
	if (sz(q) < 3) return {};
	vector<P> res;
	rep(i,0,sz(q)) res.push_back(pt(i, (i+1) % sz(q)));
	return res;
}
