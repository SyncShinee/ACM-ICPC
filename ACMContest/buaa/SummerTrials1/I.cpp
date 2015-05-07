#include <cstdio>
#include <cstring>
using namespace std;
int n;
long long f[32], c[32][32];
long long dp(int x) {
	if (f[x] > 0) {
		return f[x];
	}
	for (int i = 1; i <= x; i += 2) {
		f[x] += dp(i-1) * dp(x-i) * c[x-1][i-1];
	}
	return f[x];
}
int main() {
	int T, t, n;
	scanf("%d", &T);
	memset(f, 0, sizeof(f));
	c[0][0] = 1;
	for (int i = 1; i <= 20; ++i)
		for (int j = 0; j <= i; ++j)
			if (j == 0)
				c[i][j] = 1;
			else
				c[i][j] = c[i-1][j] + c[i-1][j-1];
	f[0] = 1; f[1] = 1; f[2] = 1; f[3] = 2;
	while (T--) {
		scanf("%d%d", &t, &n);
		printf("%d %lld\n", t, n == 1 ? 1 : 2*dp(n));
	}
	return 0;
}