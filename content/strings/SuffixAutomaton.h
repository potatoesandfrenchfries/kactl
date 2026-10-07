/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: cp-algorithms.com/string/suffix-automaton.html
 * Description: Minimal automaton accepting exactly the substrings of a
 * string, built online. State 0 is the root, \texttt{nx[v][c]} is the
 * transition (0 = none), \texttt{link} is the suffix link and
 * \texttt{len[v]} the longest string in state $v$ (it holds strings of
 * length \texttt{len[link[v]]+1..len[v]}).
 * Distinct substrings $= \sum_{v>0}$ \texttt{len[v]-len[link[v]]}.
 * To count occurrences, set \texttt{cnt = 1} for every non-clone state
 * and add \texttt{cnt[v]} to \texttt{cnt[link[v]]} by decreasing \texttt{len}.
 * Time: O(26N)
 * Status: stress-tested
 */
#pragma once

struct SuffixAutomaton {
	vector<array<int, 26>> nx{{}};
	vi len{0}, link{-1};
	int last = 0;
	int node(int l, int k, array<int, 26> t) {
		nx.push_back(t); len.push_back(l); link.push_back(k);
		return sz(nx) - 1;
	}
	void add(char ch) {
		int c = ch - 'a', p = last, cur = node(len[last]+1, 0, {});
		for (; p != -1 && !nx[p][c]; p = link[p]) nx[p][c] = cur;
		if (p != -1) {
			int q = nx[p][c];
			if (len[p]+1 == len[q]) link[cur] = q;
			else {
				int cl = node(len[p]+1, link[q], nx[q]);
				for (; p != -1 && nx[p][c] == q; p = link[p])
					nx[p][c] = cl;
				link[q] = link[cur] = cl;
			}
		}
		last = cur;
	}
};
