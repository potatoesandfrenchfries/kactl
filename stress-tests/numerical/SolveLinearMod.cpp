#include "../utilities/template.h"

#include "../../content/numerical/SolveLinear.h"
#include "../../content/numerical/SolveLinearMod.h"

int main() {
	int consistent = 0, inconsistent = 0;
	rep(it,0,100000) {
		int n = rand() % 5 + 1, m = rand() % 5 + 1;
		// small entries, so ranks over Q and mod p agree
		vector<vd> D(n, vd(m));
		vector<vl> A(n, vl(m));
		vd bd(n);
		vl b(n);
		rep(i,0,n) rep(j,0,m) {
			int v = rand() % 5 - 2;
			if (rand() % 3 == 0) v = 0;
			D[i][j] = v, A[i][j] = (v % mod + mod) % mod;
		}
		vi x0(m);
		for (int& v : x0) v = rand() % 7 - 3;
		bool consist = rand() % 2;
		rep(i,0,n) {
			int v = rand() % 11 - 5;
			if (consist) {
				v = 0;
				rep(j,0,m) v += (int)D[i][j] * x0[j];
			}
			bd[i] = v;
			b[i] = (v % mod + mod) % mod;
		}
		vector<vl> A0 = A;
		vl b0 = b;
		vd xd(m);
		vl x(m);
		int want = solveLinear(D, bd, xd);
		int got = solveLinearMod(A, b, x);
		assert(want == got);
		if (consist) assert(got >= 0);
		if (got >= 0) {
			consistent++;
			rep(i,0,n) {
				ll s = 0;
				rep(j,0,m) s = (s + A0[i][j] * x[j]) % mod;
				assert(s == b0[i]);
			}
		} else inconsistent++;
	}
	assert(consistent > 1000 && inconsistent > 1000);
	cout << "Tests passed!" << endl;
}
