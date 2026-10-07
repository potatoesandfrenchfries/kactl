/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree of counts over positions $[0,n)$.
 * \texttt{add(v, i, d)} returns a new version equal to version \texttt{v}
 * with \texttt{d} added at position \texttt{i}; old versions stay valid
 * and version 0 is empty. \texttt{query(v, a, b)} is the sum over $[a,b)$.
 * Usage: Build \texttt{root[i+1] = add(root[i], rank(a[i]), 1)}. Then
 * \texttt{query(root[r], x, y) - query(root[l], x, y)} counts the values
 * in $[x,y)$ among \texttt{a[l..r)}, and \texttt{kth(root[l], root[r], k)}
 * is the (0-indexed) $k$'th smallest rank in it.
 * Time: O(\log N) per operation, O(\log N) memory per update
 * Status: stress-tested
 */
#pragma once

struct PST {
	struct Node { int l, r, sum; };
	vector<Node> t{{0, 0, 0}}; // node 0 is the empty tree
	int n;
	PST(int n) : n(n) {}
	int add(int v, int i, int d) { return add(v, i, d, 0, n); }
	int add(int v, int i, int d, int lo, int hi) {
		t.push_back(t[v]);
		int u = sz(t) - 1;
		t[u].sum += d;
		if (hi - lo > 1) {
			int mid = (lo + hi) / 2;
			if (i < mid) {
				int c = add(t[u].l, i, d, lo, mid);
				t[u].l = c;
			} else {
				int c = add(t[u].r, i, d, mid, hi);
				t[u].r = c;
			}
		}
		return u;
	}
	int query(int v, int a, int b) {
		return query(v, a, b, 0, n);
	}
	int query(int v, int a, int b, int lo, int hi) {
		if (!v || b <= lo || hi <= a) return 0;
		if (a <= lo && hi <= b) return t[v].sum;
		int mid = (lo + hi) / 2;
		return query(t[v].l, a, b, lo, mid) +
			query(t[v].r, a, b, mid, hi);
	}
	int kth(int u, int v, int k) { // in version v minus u
		int lo = 0, hi = n;
		while (hi - lo > 1) {
			int mid = (lo + hi) / 2;
			int c = t[t[v].l].sum - t[t[u].l].sum;
			if (k < c) u = t[u].l, v = t[v].l, hi = mid;
			else k -= c, u = t[u].r, v = t[v].r, lo = mid;
		}
		return lo;
	}
};
