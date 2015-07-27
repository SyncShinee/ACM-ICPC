#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 997
using namespace std;
typedef long long ll;
int f[100010], factor[2000010], invf[2000010], n, m, k, num1;
struct node {
	int x, y;
	friend bool operator < (node a, node b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	}
}p[100010], q[100010];
int quick_inverse(int n, int p) {
	n %= MOD;
	int ret = 1;
	int exponent = p - 2;
	for (int i = exponent; i; i >>= 1, n = 1ll * n * n % p) {
		if (i & 1) {
			ret = 1ll * ret * n % p;
		}
	} 
	return ret;
}
ll ks(ll x, ll p) {
	ll ret = 1;
	ll po = p-2;
	while (po > 0) {
		if (po & 1) {
			ret = (ret * x) % p;
		}
		x = (x * x) % p;
		po /= 2;
	}
	return ret;
}
ll lucas(ll n, ll m, ll p) {
	if (n < m)
		return 0;
	if (n == m)
		return 1;
	ll ret = 1, a, b;
	while (n && m) {
		a = n % p;
		b = m % p;
		if (a < b)
			return 0;
		ret = (ret * factor[a] * ks((factor[b] * factor[a-b]) % p, p)) % p;
		n /= p;
		m /= p;
	}
	return ret;
}

bool legal(int xx, int yy) {
	if (xx >= 1 && xx <= n && yy >= 1 && yy <= m)
		return true;
	return false;
}

int main() {
	int T, x, y;
	scanf("%d", &T);
	factor[0] = 1;
	for (ll i = 1; i <= 997; ++i)
		factor[i] = (factor[i-1] * i) % MOD;
	for (int cas = 1; cas <= T; ++cas) {
		int num = 0;
		memset(f, 0, sizeof f);
		memset(p, 0, sizeof p);
		scanf("%d%d%d", &n, &m, &k);
		bool flag = false;
		for (int i = 1; i <= k; ++i) {
			scanf("%d%d", &x, &y);
			for (int tx = -1; tx <= 1; ++tx)
				for (int ty = -1; ty <= 1; ++ty) {
					if (legal(x + tx, y + ty)) {
						p[++num].x = x + tx;
						p[num].y = y + ty;
						if (x + tx == n && y + ty == m) {
							flag = true;
						}
					}
				}
		}
		if (flag) {
			printf("Case #%d: %d\n", cas, 0);
			continue;
		}

		p[++num].x = n;
		p[num].y = m;
		sort(p + 1, p + num + 1);
		num1 = 1;
		q[1] = p[1];
		for (int i = 2; i <= num; ++i) {
			if (p[i].x == p[i-1].x && p[i].y == p[i-1].y)
				continue;
			q[++num1] = p[i];
		}


		for (int i = 1; i <= num1; ++i) {
			f[i] = lucas(q[i].x + q[i].y - 2, q[i].x - 1, MOD);
			for (int j = 1; j < i; ++j) {

				if (q[j].x <= q[i].x && q[j].y <= q[i].y ) {
					f[i] = (f[i] - 1ll * lucas(q[i].x - q[j].x + q[i].y - q[j].y, q[i].x - q[j].x, MOD) * f[j] % MOD) % MOD;
				}
			}
		}
		printf("Case #%d: %d\n", cas, (f[num1] + MOD) % MOD);

	}
	return 0;
}