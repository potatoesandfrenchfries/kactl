#include "../utilities/template.h"

#include "../../content/various/MeetInTheMiddle.h"

int main() {
	rep(it,0,20000) {
		int n = rand() % 13;
		vector<ll> a(n);
		for (ll& x : a) x = rand() % 41 - 20;
		ll T = rand() % 81 - 40;
		ll want = 0;
		rep(mask,0,1 << n) {
			ll s = 0;
			rep(i,0,n) if (mask >> i & 1) s += a[i];
			want += s <= T;
		}
		assert(countSubsets(a, T) == want);
	}
	cout << "Tests passed!" << endl;
}
