#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson l, m, k << 1
#define rson m + 1, r, k << 1 | 1
using namespace std;
const int N = 200010;
struct T {
	int v;
}f[N << 2];
int a[N];
T put(T a, T b) {
	T c;
	c.v = max(a.v, b.v);
	return c;
}
void mk(int l, int r, int k) {
	if (l == r) {
		f[k].v = a[l];
		return;
	}
	int m = (l + r) >> 1;
	mk(lson);
	mk(rson);
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}
void update(int pos, int l, int r, int k, int val) {
	if (l == pos && r == pos) {
		f[k].v = val;
		return;
	}
	int m = (l + r) >> 1;
	if (pos <= m) {
		update(pos, lson, val);
	}
	else {
		update(pos, rson, val);
	}
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}
T query(int la, int ra, int l, int r, int k) {
	if (la <= l && r <= ra) {
		return f[k];
	}
	int m = (l + r) >> 1;
	if (la > m) {
		return query(la, ra, rson);
	}
	if (ra <= m) {
		return query(la, ra, lson);
	}
	T t1 = query(la, ra, lson), t2 = query(la, ra, rson);
	return put(t1, t2);
}
int main() {
	int n, m, x, y;
	char s[2];
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		mk(1, n, 1);
		while (m --) {
			scanf("%s%d%d", s, &x, &y);
			if (s[0] == 'U') {
				update(x, 1, n, 1, y);
			}
			else {
				T ans = query(x, y, 1, n, 1);
				printf("%d\n", ans.v);
			}
		}
	}
	return 0;
}