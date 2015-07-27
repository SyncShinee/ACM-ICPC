#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int n, m, p, q, color[4096];
struct point {
	long long x, y, z;
}P[4096];
long long A[4096], B[4096], C[4096], D[4096], X[4096], Y[4096], Z[4096], R[4096];
int calc_plane(int x, point tmp) {
	if (A[x]*tmp.x + B[x] * tmp.y + C[x] * tmp.z + D[x] > 0)
		return 1;
	else 
		return 0;
}
int calc_sphere(int x, point tmp) {
	if ((tmp.x - X[x]) * (tmp.x - X[x]) + (tmp.y - Y[x]) * (tmp.y - Y[x]) + (tmp.z - Z[x]) * (tmp.z - Z[x]) - R[x] * R[x] > 0)
		return 1;
	else
		return 0;
}
int main() {
	int T;
	freopen("1011.in", "r", stdin);
	freopen("1011.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &n, &m, &p, &q);
		for (int i = 0; i < n; ++i) {
			scanf("%I64d%I64d%I64d%I64d", &A[i], &B[i], &C[i], &D[i]);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%I64d%I64d%I64d%I64d", &X[i], &Y[i], &Z[i], &R[i]);
		}
		memset(color, 0, sizeof color);
		for (int i = 0; i < p + q; ++i) {
			scanf("%I64d%I64d%I64d", &P[i].x, &P[i].y, &P[i].z);
			for (int j = 0; j < n; ++j) {
				color[i] ^= calc_plane(j, P[i]);
			}
			for (int j = 0; j < m; ++j) {
				color[i] ^= calc_sphere(j, P[i]);
			}
		}
		int ans = 0;
		if (p == 0) {
			for (int i = 0; i < q; ++i) {
				printf("Both\n");
			}
		}
		else {
			for (int i = 0; i < p; ++i) {
				if (color[i] != 1) {
					ans = 1;
					break;
				}
			}
			if (!ans) {
				for (int i = p; i < p + q; ++i) {
					if (color[i] == 1) {
						printf("Y\n");
					}
					else {
						printf("R\n");
					}
				}
			}
			else {
				ans = 0;
				for (int i = 0; i < p; ++i) {
					if (color[i] == 1) {
						ans = 1;
						break;
					}
				}
				if (!ans) {
					for (int i = p; i < p + q; ++i) {
						if (color[i] == 0) {
							printf("Y\n");
						}
						else {
							printf("R\n");
						}
					}
				}
				else {
					printf("Impossible\n");
				}
			}
		}
		if (T > 0) { 
			printf("\n");
		}
	}
	return 0;
}