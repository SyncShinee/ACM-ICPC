#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 65536
#define lson l, m, k << 1
#define rson m + 1, r, k << 1 | 1
using namespace std;

struct T {
	int sum;
}f[N << 2];

int n, q, a[N];

T put(T a, T b) {
	T c;
	c.sum = a.sum + b.sum;
	return c;
}

void mk(int l, int r, int k) {
	if (l == r) {
		f[k].sum = a[l];
		return;
	}
	int m = (l + r) >> 1;
	mk(lson);
	mk(rson);
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}

void update(int pos, int l, int r, int k, int val) {
	if (l == pos && r == pos) {
		f[k].sum += val;
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
	if (ra <= m) {
		return query(la, ra, lson);
	}
	if (la > m) {
		return query(la, ra, rson);
	}
	T t1 = query(la, ra, lson), t2 = query(la, ra, rson);
	return put(t1, t2);
}
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int Tc, x, y;
	char s[8];
	scanf("%d", &Tc);
	for (int cas = 1; cas <= Tc; ++ cas) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		mk(1, n, 1);
		printf("Case %d:\n", cas);
		while (scanf("%s", s), strcmp(s, "End")) {
			if (strcmp(s, "Query") == 0) {
				scanf("%d%d", &x, &y);
				T ans = query(x, y, 1, n, 1);
				printf("%d\n", ans.sum);
			}
			else if (strcmp(s, "Add") == 0){
				scanf("%d%d", &x, &y);
				update(x, 1, n, 1, y);
			}
			else {
				scanf("%d%d", &x, &y);
				update(x, 1, n, 1, -y);
			}
		}
	}
	return 0;
}