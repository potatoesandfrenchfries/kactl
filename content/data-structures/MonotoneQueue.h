/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Sliding window minimum. \texttt{push} adds a value at the
 * back, \texttt{pop} removes the oldest value, \texttt{get} returns the
 * minimum of the values in the queue. Use \texttt{greater} instead
 * of \texttt{less} for the maximum.
 * Usage: MonotoneQueue<int> q; q.push(3); q.push(1); q.get(); // 1
 * Time: O(1) amortized
 * Status: stress-tested
 */
#pragma once

template<class T, class C = less<T>>
struct MonotoneQueue {
	deque<pair<T, int>> q;
	int lo = 0, hi = 0; // indices of oldest value, next value
	void push(T x) {
		while (!q.empty() && !C()(q.back().first, x)) q.pop_back();
		q.emplace_back(x, hi++);
	}
	void pop() { if (q.front().second == lo++) q.pop_front(); }
	T get() { return q.front().first; }
};
