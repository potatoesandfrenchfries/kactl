/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Number of subsets of \texttt{a} (values may be negative)
 * with sum at most \texttt{T}, for $N$ up to about 40. Splits \texttt{a} in
 * two halves, lists the sorted subset sums of each and combines them
 * with two pointers. For an exact sum, count with \texttt{equal\_range}.
 * The same split works for other subset problems (closest sum, xor).
 * Time: O(2^{N/2})
 * Status: stress-tested
 */
#pragma once

vector<ll> subsetSums(vector<ll>& a, int lo, int hi) {
	vector<ll> s = {0};
	rep(i,lo,hi) {
		vector<ll> t(sz(s)), r(2 * sz(s));
		rep(j,0,sz(s)) t[j] = s[j] + a[i];
		merge(all(s), all(t), r.begin());
		s = r;
	}
	return s;
}

ll countSubsets(vector<ll>& a, ll T) {
	int h = sz(a) / 2;
	auto L = subsetSums(a, 0, h), R = subsetSums(a, h, sz(a));
	ll res = 0;
	int j = sz(R);
	for (ll x : L) {
		while (j && x + R[j-1] > T) j--;
		res += j;
	}
	return res;
}
