#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
struct node {
	int l, r, idx;
	friend bool operator < (node x, node y) {
		return x.l < y.l || (x.l == y.l && x.r < y.r) || (x.l == y.l && x.r == y.r && x.idx < y.idx);
	}
}p[50010];
int hs[50010];
struct ans_node {
	int sum, idx;
	ans_node(int _sum = 0, int _pre = 0) {
		sum = _sum;
		idx = _pre;
	}
	friend bool operator < (ans_node x, ans_node y) {
		return x.sum < y.sum || x.sum == y.sum && x.idx > y.idx;
	}
}C[50010], f[50010];
int ans, ans_pos, prepre[50010];
ans_node getMax(int x) {
	ans_node ret = ans_node(0, 0);
	while (x > 0) {
		ret = max(ret, C[x]);
		x -= x & -x;
	}
	return ret;
}
bool cmp(node x, node y) {
	return x.idx < y.idx;
}
void solve(int l, int r) {
	//printf("@#$%d %din\n", l, r);
	if (l == r) {
		if (f[l].sum == 0) {
			f[l].sum = 1;
			f[l].idx= l;
		}
		//printf("@#$%d %dout\n", l, r);
		return;
	}
	int mid = (l + r) >> 1;
	solve(mid + 1, r);
	int i = l, j = mid + 1;
	sort(p + l, p + mid + 1);
	sort(p + mid + 1, p + r + 1);
	int hs_len = 0;
	for (int i = mid + 1; i <= r; ++i) {
		hs[hs_len++] = p[i].r;
	}
	sort(hs, hs + hs_len);
	hs_len = unique(hs, hs + hs_len) - hs;
	for (int i = 0; i <= hs_len; ++i) {
		C[i] = 0;
	}
	for (int i = l; i <= mid; ++i) {
		int pos;
		while (j <= r && p[j].l <= p[i].l) {
			pos = lower_bound(hs, hs + hs_len, p[j].r) - hs + 1;
			while (pos <= hs_len) {
				C[pos] = max(C[pos], f[p[j].idx]);
				pos += pos & -pos;
			}
			j++;
		}
		pos = upper_bound(hs, hs + hs_len, p[i].r) - hs;
		ans_node max_nxt = getMax(pos), max_now = ans_node(f[p[i].idx].sum, prepre[p[i].idx]);
		max_nxt.sum++;
		if (max_now < max_nxt) {
			f[p[i].idx] = max_nxt;
			prepre[p[i].idx] = f[p[i].idx].idx;
			//printf("------%d %d\n", p[i].idx, f[p[i].idx].idx);
			f[p[i].idx].idx = p[i].idx;
		}
	}
	sort(p + l, p + mid + 1, cmp);
	solve(l, mid);
	//printf("@#$%d %dout\n", l, r);
}
int main() {
	//freopen("1009.in", "r", stdin);
	//freopen("out.txt", "w", stdout);
	while (~scanf("%d", &n)) {
		memset(f, 0, sizeof f);
		memset(prepre, 0, sizeof prepre);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &p[i].l);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &p[i].r);
			p[i].r = -p[i].r;
			p[i].idx = i;
		}
		solve(1, n);
		int ans = 0, ans_pos = 1000010;
		for (int i = 1; i <= n; ++i) {
			if (f[i].sum > ans || f[i].sum == ans && f[i].idx < ans_pos) {
				ans = f[i].sum;
				ans_pos = f[i].idx;
			}
		}
		printf("%d\n", ans);
		printf("%d", ans_pos);
		for (int k = prepre[ans_pos]; k > 0; k = prepre[k]) {
			printf(" %d", k);
		}
		printf("\n");
	}
	return 0;
}