#include "../utilities/template.h"

#include "../../content/data-structures/MonotoneQueue.h"

int main() {
	rep(it,0,2000) {
		MonotoneQueue<int> mn;
		MonotoneQueue<int, greater<int>> mx;
		deque<int> ref;
		rep(step,0,200) {
			if (ref.empty() || rand() % 5 < 3) {
				int x = rand() % 10;
				mn.push(x), mx.push(x), ref.push_back(x);
			} else {
				mn.pop(), mx.pop(), ref.pop_front();
			}
			if (!ref.empty()) {
				assert(mn.get() == *min_element(all(ref)));
				assert(mx.get() == *max_element(all(ref)));
			}
		}
	}
	cout << "Tests passed!" << endl;
}
