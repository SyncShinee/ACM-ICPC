#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 20010;
const int M = 100010;
struct edge {
	int a, b, v;
}e[M];
bool operator < (const edge &A, const edge &B) {
	return A.v < B.v;
}
struct node {
	int val, idx;
}p[N];
bool operator < (const node &A, const node &B) {
	return A.val < B.val;
}
struct node1 {
	int fa;
	ll sz;
}f[N];
int n, m, q;
ll sum, ans[N];
int gf(int x) {
	if (f[x].fa == x)
		return x;
	return f[x].fa = gf(f[x].fa);
}
int merge(int x, int y) {
	int i = gf(x), j = gf(y);
	sum -= f[i].sz * (f[i].sz - 1) + f[j].sz * (f[j].sz - 1);
	f[i].fa = j;
	f[x].fa = j;
	f[j].sz += f[i].sz;
	sum += (f[j].sz) * (f[j].sz - 1);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d%d", &n, &m, &q);
		for (int i = 0; i < m; ++ i) {
			scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].v);
		}
		sort(e, e + m);
		for (int i = 0; i < q; ++ i) {
			scanf("%d", &p[i].val);
			p[i].idx = i;
		}
		sort(p, p + q);
		for (int i = 1; i <= n; ++ i) {
			f[i].fa = i;
			f[i].sz = 1;
		}
		int l = 0;
		sum = 0;
		for (int i = 0; i < q; ++ i) {
			while (l < m && e[l].v <= p[i].val) {
				if (gf(e[l].a) != gf(e[l].b)) {
					merge(e[l].a, e[l].b);
				}
				l ++;
			}
			ans[p[i].idx] = sum;
		}
		for (int i = 0; i < q; ++ i) {
			printf("%I64d\n", ans[i]);
		}
	}
	return 0;
}