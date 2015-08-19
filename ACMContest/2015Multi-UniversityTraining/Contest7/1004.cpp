#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct node {
	
}p[N];
int C[N][2];
int getSum(int x, int i) {
	int ret = 0;
	while (x) {
		ret += C[x][i];
		x -= x & -x;
	}
	return ret;
}
void update(int x, int y, int i) {
	while (x <= n) {
		C[x][i] += y;
		x += x & -x;
	}
}
int main() {
	while (~scanf("%d", &n)) {
		int sum = 0;
		for (int i = 1; i <= n; ++ i) {
			scanf("%d%d", &p[i].op, &p[i].l);
			if (p[i].op == 0) {
				++ sum;
				p[i].r = p[i].l + sum;
				opt[sum] = i;	
			}
		}
		len_hs = 1;
		for (int i = 1; i <= sum; ++ i) {
			hs[len_hs++] = p[opt[i]].l;
			hs[len_hs++] = p[opt[i]].r;
		}
		sort(hs + 1, hs + len_hs);
		len_hs = unique(hs + 1, hs + len_hs) - hs;
		num = 0;
		for (int i = 1; i <= n; ++ i) {
			int x = lower_bound(hs + 1, hs + len_hs, p[i].l) - hs, y = lower_bound(hs + 1, hs + len_hs, p[i].r);
			if (p[i].op == 0) {
				printf("%d\n", num - getSum(x - 1, 0) - getSum(len_hs - 1, 1) + getSum(y, 1));
				num ++;
				update(x, 1, 0);
				update(y, 1, 1);
			}
			else {
				update(x, -1, 0);
				update(y, -1, 1);
			}
		}
	}
	return 0;
}