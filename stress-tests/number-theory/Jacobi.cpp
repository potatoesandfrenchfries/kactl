#include "../utilities/template.h"

#include "../../content/number-theory/Jacobi.h"

int legendreSym(ll a, ll p) {
	ll r = 1, b = ((a % p) + p) % p;
	rep(i,0,(int)(p-1)/2) r = r * b % p;
	return r == 0 ? 0 : r == 1 ? 1 : -1;
}

int main() {
	vi primes;
	for (int p = 3; p < 400; p += 2) {
		bool ok = true;
		for (int d = 3; d * d <= p; d += 2) ok &= p % d != 0;
		if (ok) primes.push_back(p);
	}
	for (int n = 1; n < 400; n += 2) {
		for (int a = -2 * n; a <= 2 * n; a++) {
			int want = 1, m = n;
			for (int p : primes) while (m % p == 0) {
				want *= legendreSym(a, p);
				m /= p;
			}
			if (n > 1 && jacobi(a, n) != want) {
				cout << a << " " << n << " " << jacobi(a, n) << " " << want << endl;
				return 1;
			}
		}
		if (n == 1) assert(jacobi(5, 1) == 1);
	}
	// quadratic reciprocity
	for (int m = 1; m < 200; m += 2) for (int n = 1; n < 200; n += 2) {
		if (__gcd(m, n) != 1 || n == 1 || m == 1) continue;
		int sign = ((m-1)/2 * ((n-1)/2)) % 2 ? -1 : 1;
		assert(jacobi(m, n) * jacobi(n, m) == sign);
	}
	cout << "Tests passed!" << endl;
}
