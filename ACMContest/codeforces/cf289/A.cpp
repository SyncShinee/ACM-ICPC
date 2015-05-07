#include <cstdio>
using namespace std;
int main() {
	int a[16][16], n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		a[1][i] = 1;
		a[i][1] = 1;
	}
	for (int i = 2; i <= n; ++i)
		for (int j = 2; j <= n; ++j)
			a[i][j] = a[i-1][j] + a[i][j-1];
	printf("%d\n", a[n][n]);
	return 0;
}