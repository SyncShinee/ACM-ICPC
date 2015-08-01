#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 1000010
using namespace std;
int p_num[N], p[N], tot, f[N][8], g[8], ans, l, r;
void get_prime() {
	tot = 0;
	for (int i = 2; i <= N; ++i) {
		if (!p_num[i]) {
			p[tot++] = i;
			p_num[i] = 1;
		}
		for (int j = 0; j < tot && 1ll * i * p[j] <= N; ++j) {
			if (i % p[j]) {
				p_num[i * p[j]] = p_num[i] + 1;
			}
			else {
				p_num[i * p[j]] = p_num[i];
				break;
			}
		}
	}
}
int main() {
	get_prime();
	memset(f, 0, sizeof f);
	f[2][1] = 1;
	for (int i = 3; i <= N; ++i) {
		for (int j = 1; j < 8; ++j) {
			f[i][j] = f[i-1][j];
		}
		f[i][p_num[i]]++;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &l, &r);
		ans = 1;
		for (int i = 1; i <= 7; ++i) {
			g[i] = f[r][i] - f[l - 1][i];
		}
		for (int i = 7; i >= 1; --i) {
			if (g[i] >= 2) {
				ans = max(ans, i);
			}
			else if (i == 3 && g[i] == 1 && g[6] > 0) {
				ans = max(i, ans);
			}
			else if (i == 4 && g[i] == 1 && g[6] > 0) {
				ans = max(2, ans);
			}
			else if (i == 2 && g[i] == 1 && g[4] + g[6] > 0) {
				ans = max(2, ans);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}