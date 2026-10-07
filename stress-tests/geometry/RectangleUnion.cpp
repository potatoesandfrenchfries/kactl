#include "../utilities/template.h"

#include "../../content/geometry/RectangleUnion.h"

int main() {
	rep(it,0,50000) {
		int n = rand() % 8, C = rand() % 12 + 2;
		vector<array<int, 4>> r;
		vector<vi> grid(C, vi(C));
		rep(i,0,n) {
			int x1 = rand() % C, x2 = rand() % C;
			int y1 = rand() % C, y2 = rand() % C;
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			r.push_back({x1, y1, x2, y2});
			rep(x,x1,x2) rep(y,y1,y2) grid[x][y] = 1;
		}
		ll want = 0;
		rep(x,0,C) rep(y,0,C) want += grid[x][y];
		assert(rectangleUnion(r) == want);
	}
	cout << "Tests passed!" << endl;
}
