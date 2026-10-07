#include "../utilities/template.h"

#include "../../content/number-theory/Frobenius.h"

int main() {
	rep(it,0,20000) {
		int n = rand() % 4 + 1, hi = rand() % 25 + 1;
		vector<ll> a;
		rep(i,0,n) a.push_back(rand() % hi + 1);
		ll g = 0;
		for (ll x : a) g = __gcd(g, x);
		if (g != 1) continue;

		int lim = 2000;
		vector<bool> ok(lim + 1);
		ok[0] = 1;
		rep(x,1,lim+1) for (ll c : a) if (x >= c && ok[x - c]) ok[x] = 1;
		ll want = -1;
		rep(x,0,lim+1) if (!ok[x]) want = x;
		assert(frobenius(a) == want);

		if (n == 2 && a[0] != a[1] && a[0] > 1 && a[1] > 1) {
			assert(want == a[0] * a[1] - a[0] - a[1]);
			ll cnt = 0;
			rep(x,0,lim+1) cnt += !ok[x];
			assert(cnt == (a[0] - 1) * (a[1] - 1) / 2);
		}
	}
	cout << "Tests passed!" << endl;
}
