#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <cmath>
#include <cassert>
#define N 1000010
using namespace std;
typedef long long ll;
ll ans, sum[100010], LOG[N], mi[50];
int n, a[100010];
int Log(ll x) {
	//if (x < N) 
	//	return LOG[x];
	return upper_bound(mi, mi + 35, x) - mi - 1;
}
int main() {
	int T;
	freopen("in.txt", "r", stdin);
	freopen("out.tt", "w", stdout);
	scanf("%d", &T);
	mi[0] = 1;
	for (int i = 1; i < 35; ++i) {
		mi[i] = mi[i - 1] * 2;
	}
	for (int i = 0; (1 << i) < N; ++ i)
        LOG[1 << i] = i;
    for (int i = 2; i < N; ++ i)
        if (!LOG[i]) LOG[i] = LOG[i - 1]; 
	while (T--) {
		scanf("%d", &n);
		ans = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		sum[0] = 0; 
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + a[i];
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				ans += 1ll * (i + j) * (Log(sum[j] - sum[i - 1]) + 1);
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}