#include <cstdio>
#include <algorithm>
using namespace std;
long long a[4][4];
long long f[64][4][4];
long long dp(int x, int from, int to) {
	if (f[x][from][to] > 0)
		return f[x][from][to];
	if (x == 1) {
		f[x][from][to] = a[from][to];
		f[x][from][to] = min(f[x][from][to], a[from][6-from-to] + a[6-from-to][to]);
		return f[x][from][to];
	}
	f[x][from][to] = dp(x-1, from, 6-from-to) + a[from][to] + dp(x-1, 6-from-to, to);
	f[x][from][to] = min(f[x][from][to], dp(x-1, from, to) + a[from][6-from-to] + dp(x-1, to, from) + a[6-from-to][to] + dp(x-1, from, to));
	return f[x][from][to];
}
int main() {
	int n;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			scanf("%I64d", &a[i][j]);
	scanf("%d", &n);
	printf("%I64d\n", dp(n, 1, 3));
	return 0;
}