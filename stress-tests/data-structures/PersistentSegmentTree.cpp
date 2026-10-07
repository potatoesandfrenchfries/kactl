#include "../utilities/template.h"

#include "../../content/data-structures/PersistentSegmentTree.h"

int main() {
	rep(it,0,3000) {
		int n = rand() % 30 + 1, V = rand() % 12 + 1;
		vi a(n);
		for (int& x : a) x = rand() % V;
		PST t(V);
		vi root = {0};
		rep(i,0,n) root.push_back(t.add(root[i], a[i], 1));
		rep(q,0,100) {
			int l = rand() % (n + 1), r = rand() % (n + 1);
			if (l > r) swap(l, r);
			int x = rand() % (V + 1), y = rand() % (V + 1);
			if (x > y) swap(x, y);
			int want = 0;
			rep(i,l,r) want += x <= a[i] && a[i] < y;
			assert(t.query(root[r], x, y) - t.query(root[l], x, y) == want);
			if (l < r) {
				int k = rand() % (r - l);
				vi s(a.begin() + l, a.begin() + r);
				sort(all(s));
				assert(t.kth(root[l], root[r], k) == s[k]);
			}
		}
		// negative updates and persistence of old versions
		int v = t.add(root[n], 0, -1);
		assert(t.query(v, 0, V) == n - 1);
		assert(t.query(root[n], 0, V) == n);
	}
	cout << "Tests passed!" << endl;
}
