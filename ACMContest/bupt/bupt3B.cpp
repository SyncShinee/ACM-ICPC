#include<cstdio>
using namespace std;
int a[512][512];
int main() {
	int n, m, rad;
	while (scanf("%d%d%d", &n, &m, &rad) != EOF){
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
			}
		rad = rad - (rad/360)*360;
		if (rad == 0) {
			for (int i = 1; i <= n; ++i) {
				printf("%d", a[i][1]);
				for (int j = 2; j <= m; ++j) {
					printf(" %d", a[i][j]);
				}
				printf("\n");
			}
		}
		else if (rad == 180) {
			for (int i = n; i >= 1; --i) {
				printf("%d", a[i][m]);
				for (int j = m-1; j >= 1; --j) {
					printf(" %d", a[i][j]);
				}
				printf("\n");
			}
		}
		else if (rad == 270) {
			for (int i = m; i >= 1; --i) {
				printf("%d", a[1][i]);
				for (int j = 2; j <= n; ++j)
					printf(" %d", a[j][i]);
				printf("\n");
			}
		}
		else if (rad == 90) {
			for (int i = 1; i <= m; ++i) {
				printf("%d", a[n][i]);
				for (int j = n-1; j >= 1; --j)
					printf(" %d", a[j][i]);
				printf("\n");
			}
		}
	}
	return 0;
}