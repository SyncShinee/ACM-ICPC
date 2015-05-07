#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, k, black[16], white[16], f[2][16][128], ans;
int main() {
	scanf("%I64d%I64d", &n, &k);
	for (int i = 1; i < 2*n; ++i) {
		if (i & 1 == 1) {
			black[i/2 + 1] = (i < n) ? i : 2 * n - i; 
		}
		else {
			white[i/2] = (i < n) ? i : 2 * n - i;
		}
	}
	sort(black + 1, black + n + 1);
	sort(white + 1, white + n);
	//printf("%lld %lld\n", black[2], white[1]);
	for (int i = 0; i <= n; ++i)
		f[0][i][0] = f[1][i][0] = 1;
	f[0][1][1] = 1;
	for (int i = 2; i < 2*n; ++i)
		for (int j = 1; j <= k; ++j)  
			if (i & 1 == 1) {
				if (j > black[i/2 + 1])
					break;
				f[0][i/2 + 1][j] = f[0][i/2][j] + f[0][i/2][j-1] * (black[i/2 + 1] - j + 1);
			}
			else {
				if (j > white[i/2])
					break;
				f[1][i/2][j] = f[1][i/2 - 1][j] + f[1][i/2 - 1][j-1] * (white[i/2] - j + 1);
			}
	ans = 0;
	for (int i = 0; i <= k; ++i) {
		ans += f[0][n][i] * f[1][n-1][k-i];
		//printf("%lld %lld %lld %lld\n", f[0][n][i], f[1][n-1][k-i],  f[0][n][i] * f[1][n-1][k-i], ans);
	}
	printf("%I64d\n", ans);
	return 0;
}