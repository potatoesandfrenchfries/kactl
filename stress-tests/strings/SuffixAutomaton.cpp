#include "../utilities/template.h"

#include "../../content/strings/SuffixAutomaton.h"

bool has(SuffixAutomaton& sa, const string& s) {
	int v = 0;
	for (char c : s) {
		v = sa.nx[v][c - 'a'];
		if (!v) return false;
	}
	return true;
}

int main() {
	rep(it,0,20000) {
		int n = rand() % 15 + 1, alpha = rand() % 3 + 1;
		string s;
		rep(i,0,n) s += char('a' + rand() % alpha);

		SuffixAutomaton sa;
		for (char c : s) sa.add(c);
		assert(sz(sa.nx) <= max(2, 2*n-1));

		set<string> subs;
		rep(i,0,n) rep(j,i,n) subs.insert(s.substr(i, j-i+1));
		ll distinct = 0;
		rep(v,1,sz(sa.nx)) distinct += sa.len[v] - sa.len[sa.link[v]];
		assert(distinct == sz(subs));

		for (auto& t : subs) assert(has(sa, t));
		rep(k,0,50) {
			string t;
			int m = rand() % 6 + 1;
			rep(i,0,m) t += char('a' + rand() % (alpha + 1));
			assert(has(sa, t) == (bool)subs.count(t));
		}

		// occurrence counts via suffix links
		vi cnt(sz(sa.nx)), ord(sz(sa.nx));
		int v = 0;
		for (char c : s) {
			v = sa.nx[v][c - 'a'];
			cnt[v] = 1;
		}
		iota(all(ord), 0);
		sort(all(ord), [&](int a, int b) { return sa.len[a] > sa.len[b]; });
		for (int u : ord) if (u) cnt[sa.link[u]] += cnt[u];
		for (auto& t : subs) {
			int occ = 0, u = 0;
			rep(i,0,n-sz(t)+1) occ += s.compare(i, sz(t), t) == 0;
			for (char c : t) u = sa.nx[u][c - 'a'];
			assert(cnt[u] == occ);
		}
	}
	cout << "Tests passed!" << endl;
}
