#include "../utilities/template.h"

#include "../../content/combinatorial/AlphaBeta.h"

// random game tree; leaf score is for the player to move there
struct Tree {
	vector<vi> ch;
	vi score, path;
	int at = 0;
	Tree(int n) : ch(n), score(n) {
		rep(i,1,n) ch[rand() % i].push_back(i);
		rep(i,0,n) score[i] = rand() % 21 - 10;
	}
	vi moves() { return ch[at]; }
	void make(int m) { path.push_back(at); at = m; }
	void undo(int) { at = path.back(); path.pop_back(); }
	int eval() { return score[at]; }
};

int plain(Tree& t, int depth) {
	if (!depth || t.ch[t.at].empty()) return t.eval();
	int best = -INF;
	for (int m : t.moves()) {
		t.make(m);
		best = max(best, -plain(t, depth - 1));
		t.undo(m);
	}
	return best;
}

int main() {
	rep(it,0,100000) {
		Tree t(rand() % 40 + 1);
		int depth = rand() % 6 + 1;
		int v = plain(t, depth);
		assert(negamax(t, depth) == v);
		assert(t.at == 0 && t.path.empty());
		int a = rand() % 25 - 12, b = a + rand() % 10 + 1;
		int r = negamax(t, depth, a, b);
		if (v <= a) assert(r <= a);
		else if (v >= b) assert(r >= b);
		else assert(r == v);
	}
	cout << "Tests passed!" << endl;
}
