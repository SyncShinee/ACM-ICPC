#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int a[128][128];
int main() {
	//freopen("1007.in", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n, m, tx, ty, mn, sum;
	while (~scanf("%d%d", &n, &m)) {
		mn = 1e9;
		sum = 0;
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				scanf("%d", &a[i][j]);
				if (((i ^ j) & 1) && (mn > a[i][j])) {
					tx = i, ty = j, mn = a[i][j];
				}
				sum += a[i][j];
			}
		}
		if ((n | m) & 1) {
			printf("%d\n", sum);
		}
		else {
			printf("%d\n", sum - mn);
		}
		if (n & 1) {
			for (int i = 1; i < n; i += 2) {
				for (int j = 1; j < m; ++ j) printf("R");
				printf("D");
				for (int j = 1; j < m; ++ j) printf("L");
				printf("D");
			}
			for (int i = 1; i < m; ++ i) printf("R");
		}
		else if (m & 1) {
			for (int i = 1; i < m; i += 2) {
				for (int j = 1; j < n; ++ j) printf("D");
				printf("R");
				for (int j = 1; j < n; ++ j) printf("U");
				printf("R");
			}
			for (int i = 1; i < n; ++ i) printf("D");
		}
		else {
			if (tx & 1) {
				for (int i = 1; i < tx; i += 2) {
					for (int j = 1; j < m; ++ j) printf("R");
					printf("D");
					for (int j = 1; j < m; ++ j) printf("L");
					printf("D");
				}
				printf("DR");
				for (int i = 2; i < ty; i += 2) printf("URDR");
				for (int i = ty; i < m; i += 2) printf("RURD");
				for (int i = tx + 2; i < n; i += 2) {
					printf("D");
					for (int j = 1; j < m; ++ j) printf("L");
					printf("D");
					for (int j = 1; j < m; ++ j) printf("R");
				}
			}
			else {
				for (int i = 1; i < ty; i += 2) {
					for (int j = 1; j < n; ++ j) printf("D");
					printf("R");
					for (int j = 1; j < n; ++ j) printf("U");
					printf("R");
				}
				printf("RD");
				for (int i = 2; i < tx; i += 2) printf("LDRD");
				for (int i = tx; i < n; i += 2) printf("DLDR");
				for (int i = ty + 2; i < m; i += 2) {
					printf("R");
					for (int j = 1; j < n; ++ j) printf("U");
					printf("R");
					for (int j = 1; j < n; ++ j) printf("D");
				}
			}
		}
		printf("\n");
	}
	return 0;
}