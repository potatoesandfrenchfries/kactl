/**
 * Author: Kanish H R
 * Date: 2026-10-07
 * License: CC0
 * Source: folklore
 * Description: Queue (FIFO) with the aggregate of all its values under
 * an associative operation \texttt{f}, which need not be commutative or
 * invertible. Built from two stacks.
 * Usage: AggregateQueue<int> q([](int a, int b) { return __gcd(a, b); });
 * Time: O(1) amortized
 * Status: stress-tested
 */
#pragma once

template<class T>
struct AggregateQueue {
	function<T(T, T)> f;
	vector<pair<T, T>> in, out; // {value, aggregate}
	AggregateQueue(function<T(T, T)> f) : f(f) {}
	void push(T x) {
		T a = x;
		if (!in.empty()) a = f(in.back().second, x);
		in.emplace_back(x, a);
	}
	void pop() {
		if (out.empty()) while (!in.empty()) {
			T x = in.back().first, a = x;
			if (!out.empty()) a = f(x, out.back().second);
			out.emplace_back(x, a);
			in.pop_back();
		}
		out.pop_back();
	}
	T get() { // queue must be non-empty
		if (out.empty()) return in.back().second;
		if (in.empty()) return out.back().second;
		return f(out.back().second, in.back().second);
	}
};
