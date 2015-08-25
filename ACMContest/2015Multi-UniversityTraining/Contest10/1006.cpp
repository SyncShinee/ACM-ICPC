#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#define MOD 2015
using namespace std;
int sum, n, m, x;
struct mar {
	int a[128][128];
}ans, ta, c;
mar operator * (const mar &x, const mar &y) {
	mar k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			k.a[i][j] = 0;
			for (int t = 1; t <= n; ++t) {
				k.a[i][j] += x.a[i][t] * y.a[t][j];
			}
		}
	}
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) k.a[i][j] %= MOD;
	return k;
} 
mar power_mod(mar yuan, int k) {
	mar ret;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {			
			if (i == j) {
				ret.a[i][j] = 1;
			}
			else {
				ret.a[i][j] = 0;
			}
		}
	while (k > 0) {
		if (k & 1) {
			ret = ret * yuan;
		}
		yuan = yuan * yuan;
		k >>= 1;
	}
	return ret;
}
int main() {
	int T, k;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n + n; ++ i)
			for (int j = 1; j <= n + n; ++ j) ans.a[i][j] = ta.a[i][j] = 0;
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &k);
			for (int j = 0; j < k; ++ j) {
				scanf("%d", &x);
				ta.a[i][x] = 1;
			}
		}
		for (int i = n + 1; i <= n + n; ++ i)
			for (int j = 1; j <= n; ++ j) ta.a[i][j] = ta.a[i - n][j];
		for (int i = n + 1; i <= n + n; ++ i) ta.a[i][i] = 1;
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++j) ans.a[i][j] = ta.a[i][j];
		for (int i = 1; i <= n; ++i) ans.a[i][i+n] = 1;
		n += n;
		if (m > 2) {
			c = power_mod(ta, m - 2);
			ans = ans * c;
		}
		n /= 2;
		sum = n + 1;
		if (m > 1) {
			for (int i = 1; i <= n; ++ i)
				for (int j = 1; j <= n; ++ j) {
					sum = (sum + ans.a[i][j]) % MOD;
				}
		}
		printf("%d\n", sum);
	}
	return 0;
}