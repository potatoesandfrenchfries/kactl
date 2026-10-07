/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: en.wikipedia.org/wiki/Jacobi_symbol
 * Description: Jacobi symbol $(a/n)$ for odd $n>0$, which equals the
 * Legendre symbol $a^{(n-1)/2} \pmod n$ for prime $n$ (1 if $a$ is a
 * nonzero square, -1 if not, 0 if $n \mid a$). For composite $n$,
 * $(a/n) = -1$ implies $a$ is a non-residue, but 1 does not imply a square.
 * Quadratic reciprocity: for odd coprime $m,n>0$,
 * $(m/n)(n/m) = (-1)^{\frac{m-1}{2}\frac{n-1}{2}}$,
 * $(-1/n) = (-1)^{\frac{n-1}{2}}$, $(2/n) = (-1)^{\frac{n^2-1}{8}}$.
 * Time: O(\log n)
 * Status: stress-tested
 */
#pragma once

int jacobi(ll a, ll n) {
	a %= n; if (a < 0) a += n;
	int r = 1;
	while (a) {
		while (a % 2 == 0) {
			a /= 2;
			if (n % 8 == 3 || n % 8 == 5) r = -r;
		}
		swap(a, n);
		if (a % 4 == 3 && n % 4 == 3) r = -r;
		a %= n;
	}
	return n == 1 ? r : 0;
}
