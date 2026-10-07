/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: en.wikipedia.org/wiki/Alpha-beta_pruning
 * Description: Negamax with alpha-beta pruning for two-player
 * zero-sum games. The state \texttt{S} must provide
 * \texttt{moves()} (a vector of moves), \texttt{make(m)},
 * \texttt{undo(m)} and \texttt{eval()}, the score for the player to
 * move (called at depth 0 or when there are no moves). Returns the game
 * value with window $(a,b)$: exact if inside, else a bound $\le a$ or $\ge b$.
 * Try the best moves first to prune more.
 * Usage: int v = negamax(state, 10);
 * Time: O(b^d), or O(b^{d/2}) with best move ordering
 * Status: stress-tested
 */
#pragma once

const int INF = 1e9;
template<class S>
int negamax(S& s, int depth, int a = -INF, int b = INF) {
	auto ms = s.moves();
	if (!depth || ms.empty()) return s.eval();
	for (auto m : ms) {
		s.make(m);
		a = max(a, -negamax(s, depth - 1, -b, -a));
		s.undo(m);
		if (a >= b) break;
	}
	return a;
}
