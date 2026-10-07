#include "../utilities/template.h"

#include "../../content/data-structures/LiChaoTree.h"

int main() {
	rep(it,0,3000) {
		int n = rand() % 40 + 1;
		LiChao t(n);
		vector<array<ll, 4>> lines; // k, m, a, b
		rep(step,0,60) {
			if (rand() % 3) {
				ll k = rand() % 2001 - 1000, m = rand() % 200001 - 100000;
				int a = 0, b = n;
				if (rand() % 2) {
					a = rand() % n, b = a + rand() % (n - a + 1);
					t.addSeg(k, m, a, b);
				} else t.add(k, m);
				lines.push_back({k, m, a, b});
			} else {
				int x = rand() % n;
				ll want = LLONG_MAX;
				for (auto& l : lines) if (l[2] <= x && x < l[3])
					want = min(want, l[0] * x + l[1]);
				ll got = t.query(x);
				if (want == LLONG_MAX) assert(got >= (ll)4e18);
				else assert(got == want);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
