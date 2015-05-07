#include <cstdio>
#include <cstring>
using namespace std;
int a[1024][1024], f[1024][1024], k[1024][1024];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);
	memset(f, 0x7f, sizeof(f));
	memset(k, 0x7f, sizeof(k));
	for (int j = m; j >= 1; --j)
		for (int i = n; i >= 1; --i) {
			k[i][j] = a[i][j];
			if (k[i][j] > k[i+1][j])
				k[i][j] = k[i+1][j];
			if (k[i][j] > k[i][j+1])
				k[i][j] = k[i][j+1];
			f[i][j] = k[i][j];
			if (i > 1 && f[i][j] > f[i-1][j+1])
				f[i][j] = f[i-1][j+1];
		}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			printf("%d%c", f[i][j], (j == m) ? '\n' : ' ');
	}
	return 0;
}