#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson l, m, k << 1
#define rson m + 1, r, k << 1 | 1
using namespace std;
const int N = 100010;
struct T {
	int sum, tag;
}f[N << 2];
T put(T a, T b) {
	T c;
	c.sum = a.sum + b.sum;
	c.tag = 0;
	return c;
}
void pushDown(int k, int len) {
	if (f[k].tag) {
		f[k << 1].tag = f[k << 1 | 1].tag = f[k].tag;
		f[k << 1].sum = f[k].tag * (len - (len >> 1));
		f[k << 1 | 1].sum = f[k].tag * (len >> 1);
		f[k].tag = 0;
	}
}
T query(int la, int ra, int l, int r, int k) {
	if (la <= l && r <= ra) {
		return f[k];
	}
	pushDown(k, r - l + 1);
	int m = (l + r) >> 1;
	if (ra <= m) {
		return query(la, ra, lson);
	}
	if (la > m) {
		return query(la, ra, rson);
	}
	T t1 = query(la, ra, lson), t2 = query(la, ra, rson);
	return put(t1, t2);
}
void update(int la, int ra, int l, int r, int k, int val) {
	if (la <= l && r <= ra) {
		f[k].tag = val;
		f[k].sum = (r - l + 1) * val;
		return;
	}
	pushDown(k, r - l + 1);
	int m = (l + r) >> 1;
	if (la <= m) update(la, ra, lson, val);
	if (m < ra) update(la, ra, rson, val);
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}
void mk(int l, int r, int k) {
	if (l == r ) {
		f[k].tag = 0;
		f[k].sum = 1;
		return;
	}
	int m = (l + r) >> 1;
	mk(lson);
	mk(rson);
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}
int main() {
	int Tc, n, m, x, y, z;
	scanf("%d", &Tc);
	for (int cas = 1; cas <= Tc; ++cas){
		scanf("%d%d", &n, &m);
		mk(1, n, 1);
		while (m --) {
			scanf("%d%d%d", &x, &y, &z);
			update(x, y, 1, n, 1, z);
		}
		printf("Case %d: The total value of the hook is %d.\n", cas, query(1, n, 1, n, 1).sum);
	}
}