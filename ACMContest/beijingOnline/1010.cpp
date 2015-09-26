#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
using namespace std;
const int N = 50010, BLKSZ = 233;
int n, m, blk[N], mx[5][256], lastans, lim;
bitset <N> bt[5][256], ans[5], ans1;
struct node {
	int id, d;
}p[5][N];
bool operator < (const node &A, const node &B) {
	return A.d < B.d;
}
int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < N; ++ i) {
		blk[i] = i / BLKSZ;
	}
	while (T --) {
		scanf("%d%d", &n, &m);
		lastans = 0;
		for (int j = 0; j < 5; ++ j) {
			for (int i = 0; i <= blk[n]; ++ i) {
				bt[j][i].reset();
			}
		}
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < 5; ++ j) {
				scanf("%d", &p[j][i].d);
				p[j][i].id = i;
			}
		}
		for (int j = 0; j < 5; ++ j) {
			sort(p[j], p[j] + n);
		}
		for (int j = 0; j < 5; ++ j) {
			for (int i = 0; i < n; ++ i) {
				bt[j][blk[i]].set(p[j][i].id);
				mx[j][blk[i]] = p[j][i].d;
			}
			for (int i = 1; i <= blk[n - 1]; ++ i) {
				bt[j][i] |= bt[j][i - 1];
			}
		}
		scanf("%d", &m);
		while (m --) {
			for (int j = 0; j < 5; ++ j) {
				scanf("%d", &lim);
				ans[j].reset();
				lim ^= lastans;
				int l = 0;
				while (l <= blk[n - 1] && mx[j][l] <= lim) {
					l ++;
				}
				ans[j] = l > 0 ? bt[j][l - 1] : 0;
				for (int i = l * BLKSZ; i < n; ++ i) {
					if (p[j][i].d > lim) break;
					ans[j].set(p[j][i].id);
				}
			}
			ans1.set();
			for (int j = 0; j < 5; ++ j) {
				ans1 &= ans[j];
			}
			lastans = ans1.count();
			printf("%d\n", lastans);
		}
	}
	return 0;
}