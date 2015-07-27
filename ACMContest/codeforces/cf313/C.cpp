#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 1000000007
using namespace std;
struct node {
	int x, y;
	friend bool operator < (node a, node b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	}
}p[100010];

int f[100010], factor[200010], invf[200010], dp[100010][2];
	int n, m, k;
int quick_inverse(int n, int p) {
	int ret = 1;
	int exponent = p - 2;
	for (int i = exponent; i; i >>= 1, n = 1ll * n * n % p) {
		if (i & 1) {
			ret = 1ll * ret * n % p;
		}
	} 
	return ret;
}

int C(int a, int b) {
	return 1ll * factor[a] * invf[b] % MOD * invf[a - b] % MOD;
}
void solve1() {
	memset(f, 0, sizeof f);
	f[1] = C(p[1].x + p[1].y - 2, p[1].x - 1);
	for (int i = 2; i <= k; ++i) {
		f[i] = C(p[i].x + p[i].y - 2, p[i].x - 1);
		for (int j = 1; j < i; ++j) {
			if (p[j].x <= p[i].x && p[j].y <= p[i].y) {
				f[i] = (f[i] - 1ll * C(p[i].x - p[j].x + p[i].y - p[j].y, p[i].x - p[j].x) * f[j] % MOD) % MOD;
			}
		}
	}
	printf("%d\n", (f[k] + MOD) % MOD);
}

void solve2() {
	memset(dp, 0, sizeof dp);
	dp[1][1] = 1;
	for (int i = 2; i <= k; ++i)
		for (int j = 1; j < i; ++j) {
			if (p[j].x <= p[i].x && p[j].y <= p[i].y) {
				dp[i][1] = (dp[i][1] + 1ll * dp[j][0] * C(p[i].x - p[j].x + p[i].y - p[j].y, p[i].x - p[j].x) % MOD) % MOD;
				dp[i][0] = (dp[i][0] + 1ll * dp[j][1] * C(p[i].x - p[j].x + p[i].y - p[j].y, p[i].x - p[j].x) % MOD) % MOD;
			}
		}
	int ans = (dp[k][0] - dp[k][1]) % MOD;
	printf("%d\n", (ans + MOD) % MOD);
	
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	factor[0] = 1;
	for (int i = 1; i <= n + m; ++i) {
		factor[i] = 1ll * factor[i - 1] * i % MOD;
	}
	invf[n + m] =  quick_inverse(factor[n + m], MOD);
	for (int i = n + m -1; i >= 0; --i) {
		invf[i] = 1ll * invf[i + 1] * (i + 1) % MOD;
	}
	p[++k].x = n;
	p[k].y = m;
	sort(p + 1, p + k + 1);
	solve1();
	return 0;
}