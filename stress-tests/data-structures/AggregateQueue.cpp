#include "../utilities/template.h"

#include "../../content/data-structures/AggregateQueue.h"

int main() {
	rep(it,0,2000) {
		// string concatenation: associative but not commutative
		AggregateQueue<string> q([](string a, string b) { return a + b; });
		AggregateQueue<int> g([](int a, int b) { return __gcd(a, b); });
		deque<string> ref;
		deque<int> refg;
		rep(step,0,100) {
			if (ref.empty() || rand() % 5 < 3) {
				int x = rand() % 12 + 1;
				string s(1, char('a' + rand() % 26));
				q.push(s), g.push(x), ref.push_back(s), refg.push_back(x);
			} else {
				q.pop(), g.pop(), ref.pop_front(), refg.pop_front();
			}
			if (!ref.empty()) {
				string want;
				for (auto& s : ref) want += s;
				assert(q.get() == want);
				int gg = 0;
				for (int x : refg) gg = __gcd(gg, x);
				assert(g.get() == gg);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
