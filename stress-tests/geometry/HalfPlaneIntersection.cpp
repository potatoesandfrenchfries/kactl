#include "../utilities/template.h"

#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/PolygonCut.h"
#include "../../content/geometry/HalfPlaneIntersection.h"

double area(vector<P> v) {
	return sz(v) < 3 ? 0 : abs(polygonArea2(v)) / 2;
}

int main() {
	int nonEmpty = 0, empty = 0;
	rep(it,0,200000) {
		int R = it % 2 ? 4 : 10;
		vector<L> v = {
			L{P(-R,-R), P(R,-R)}, L{P(R,-R), P(R,R)},
			L{P(R,R), P(-R,R)}, L{P(-R,R), P(-R,-R)}};
		vector<P> poly = {P(-R,-R), P(R,-R), P(R,R), P(-R,R)};
		int n = rand() % 7;
		rep(i,0,n) {
			P a(rand() % 11 - 5, rand() % 11 - 5);
			P b(rand() % 11 - 5, rand() % 11 - 5);
			if (a == b) continue;
			v.push_back(L{a, b});
			poly = polygonCut(poly, b, a); // keeps left of a -> b
		}
		shuffle(all(v), mt19937(rand()));
		vector<P> res = halfPlanes(v);
		double want = area(poly), got = area(res);
		if (abs(want - got) > 1e-6) {
			cout << "want " << want << " got " << got << endl;
			for (L l : v) cout << l[0] << "->" << l[1] << endl;
			return 1;
		}
		if (want > 1e-6) {
			nonEmpty++;
			// result must be convex ccw and inside every half-plane
			rep(i,0,sz(res)) {
				P a = res[i], b = res[(i+1)%sz(res)], c = res[(i+2)%sz(res)];
				assert(a.cross(b, c) > -1e-6);
				for (L l : v) assert(l[0].cross(l[1], a) > -1e-6);
			}
		} else empty++;
	}
	cout << "nonempty " << nonEmpty << " empty " << empty << endl;
	cout << "Tests passed!" << endl;
}
