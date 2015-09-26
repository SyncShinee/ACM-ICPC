#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 100010;
const int INF = 1e9+7;
struct node {
	int x, y;
	node (int _x = 0, int _y = 0) : x(_x), y(_y) {}
}p[N], a[N];
bool operator < (const node &A, const node &B) {
	return A.y < B.y || A.y == B.y && A.x > B.x;
}
int n, m, num;
int main() {
	int l, r;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++ i) {
			scanf("%d%d", &p[i].x, &p[i].y);
		}
		sort(p, p + n);
		int lmax = -1, num = 0;
		for (int i = 0; i < n; ++ i) {
			if (lmax < p[i].x) {
				lmax = p[i].x;
				a[num++] = p[i];
			}
		}
		while (m --) {
			scanf("%d%d", &l, &r);
			int ans = 0;
			while (l <= r) {
				//printf("%d\n", l);
				int cur = lower_bound(a, a + num, node(INF, l)) - a;
				while (cur < num && a[cur].x < l) cur ++;
				if (cur >= num || a[cur].y > r) break;
				ans++;
				l = a[cur].y;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}