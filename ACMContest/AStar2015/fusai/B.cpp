#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
int f[5010][32];
int per[32][8];
struct node {
	int p, x;
}a[5010][8], z1, z2, z3, z4, zz1, zz2, zz3, zz4;
int n, ans;
int main() {
	int T;
	per[0][1] = a[0][1].p = 1;
	per[0][2] = a[0][2].p = 2;
	per[0][3] = a[0][3].p = 3;
	per[0][4] = a[0][4].p = 4;
	for (int i = 1; i < 24; ++i) {
		for (int j = 1; j <= 4; ++j)
			per[i][j] = per[i-1][j];
		next_permutation(per[i]+1, per[i]+5);
	}
	scanf("%d", &T);
	a[0][1].x = a[0][2].x = a[0][3].x = a[0][4].x = 0;
	for (int cas = 1; cas <= T; ++cas) {
		printf("Case #%d:\n", cas);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d%d%d%d%d%d", &a[i][1].x, &a[i][1].p, &a[i][2].x, &a[i][2].p, &a[i][3].x, &a[i][3].p, &a[i][4].x, &a[i][4].p);
		}
		memset(f, -1, sizeof(f));
		f[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 24; ++j) {
				 z1 = a[i][per[j][1]];
				 z2 = a[i][per[j][2]];
				 z3 = a[i][per[j][3]];
				 z4 = a[i][per[j][4]];
				 if (z1.p > z2.p) {
				 	continue;
				 }
				 if (z2.p > z3.p) {
				 	continue;
				 }
				 if (z3.p > z4.p) {
				 	continue;
				 }
				 for (int t = 0; t < 24; ++t) {
				 	if (f[i-1][t] > -1) {
				 		zz1 = a[i-1][per[t][1]];
						zz2 = a[i-1][per[t][2]];
						zz3 = a[i-1][per[t][3]];
						zz4 = a[i-1][per[t][4]];
						int tmp = f[i-1][t] + abs(z1.p - zz1.p) + abs(z1.x - zz1.x) + abs(z2.p - zz2.p) + abs(z2.x - zz2.x)
							    + abs(z3.p - zz3.p) + abs(z3.x - zz3.x) + abs(z4.p - zz4.p) + abs(z4.x - zz4.x);
				 		if (f[i][j] == -1) {
				 			f[i][j] = tmp;
				 		}
				 		else {
				 			f[i][j] = min(f[i][j], tmp);
				 		}
				 	}
				 }
			}
		}
		ans = -1;
		for (int i = 0; i < 24; ++i) {
			if(f[n][i] > -1) {
				if (ans == -1)
					ans = f[n][i];
				else 
					ans = min(f[n][i], ans);
			}
		}
		printf("%d\n", ans);
	} 
	return 0;
}