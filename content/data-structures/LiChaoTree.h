/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: cp-algorithms.com/geometry/convex_hull_trick.html
 * Description: Minimum of lines $kx+m$ at integer points $x \in [0,n)$.
 * Lines can be added in any order, either over the whole range or on a
 * segment $[a,b)$, and queries can come in any order. Compress $x$ if
 * needed. For maximum, add $(-k,-m)$ and negate the answer.
 * Needs $|kx+m| < 4 \cdot 10^{18}$. A query with no line returns a huge value.
 * Usage: LiChao t(100); t.add(2, 5); t.addSeg(-1, 9, 10, 20); t.query(15);
 * Time: O(\log N) per add and query, O(\log^2 N) per segment
 * Status: stress-tested
 */
#pragma once

struct LiChao {
	typedef pair<ll, ll> L; // {k, m}
	int n;
	vector<L> t;
	LiChao(int n) : n(n), t(4 * n, L(0, LLONG_MAX / 2)) {}
	ll f(L l, ll x) { return l.first * x + l.second; }
	void ins(L l, int v, int lo, int hi) {
		int mid = (lo + hi) / 2;
		bool a = f(l, lo) < f(t[v], lo);
		bool b = f(l, mid) < f(t[v], mid);
		if (b) swap(t[v], l);
		if (hi - lo == 1) return;
		if (a != b) ins(l, 2*v, lo, mid);
		else ins(l, 2*v+1, mid, hi);
	}
	void seg(L l, int a, int b, int v, int lo, int hi) {
		if (b <= lo || hi <= a) return;
		if (a <= lo && hi <= b) return ins(l, v, lo, hi);
		int mid = (lo + hi) / 2;
		seg(l, a, b, 2*v, lo, mid), seg(l, a, b, 2*v+1, mid, hi);
	}
	void add(ll k, ll m) { ins(L(k, m), 1, 0, n); }
	void addSeg(ll k, ll m, int a, int b) {
		seg(L(k, m), a, b, 1, 0, n);
	}
	ll query(int x) {
		ll r = LLONG_MAX;
		for (int v = 1, lo = 0, hi = n;;) {
			r = min(r, f(t[v], x));
			if (hi - lo == 1) return r;
			int mid = (lo + hi) / 2;
			if (x < mid) v = 2*v, hi = mid;
			else v = 2*v+1, lo = mid;
		}
	}
};
