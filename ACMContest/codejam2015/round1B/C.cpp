#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
struct node {
	long long time, inc;
	int order;
	friend bool operator < (node x, node y) {
		return x.time < y.time || (x.time == y.time && x.order > y.order);
	}
}tnode, tmp;
multiset <node> tree;
int ans, change, n, cnt, h;
long long d, m;
int main() {
	freopen("C-large-practice.in", "r", stdin);
	freopen("C.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		tree.clear();
		cnt = 0;
		for (int i = 0; i < n; ++ i) {
			scanf("%lld%d%lld", &d, &h, &m);
			cnt += h;
			for (int j = 0; j < h; ++ j) {				
				tnode.time = (360 - d) * (m + j);				
				tnode.order = 1;
				tnode.inc = (m + j)*360;
				tree.insert(tnode);
			}
		}
		ans = cnt;
		change = 0;
		while (change < ans) {
			tnode = *(tree.begin());
			while (tree.begin()->time == tnode.time) {
				tmp = *tree.begin();
				tree.erase(tree.begin());
				if (tmp.order == 1) {
					change --;
				}
				else {
					change ++;
				}
				tmp.order ++;
				tmp.time += tmp.inc;
				tree.insert(tmp);
			}
			ans = min(ans, change + cnt);
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}