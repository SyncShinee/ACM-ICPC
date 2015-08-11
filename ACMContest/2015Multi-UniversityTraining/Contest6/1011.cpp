#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <cmath>
#define N 100010
#define MOD 1000000007
using namespace std;
typedef long long ll;
int powe_mod(int m, int p) {
	int ret = 1;
	while (p > 0) {
		if (p & 1) {
			ret = 1ll * ret * m % MOD;
		}
		m = 1ll * m * m % MOD;
		p >>= 1;
	}
	return ret;
}
int main() {
	int T, ans, od, ev, n;
	scanf("%d", &T);
	while (T --) {
		scanf("%d", &n);
		ev = n / 2;
		od = n - ev;
		ans = powe_mod(2, ev);
		ans = (1ll * ans * powe_mod(2, od - 1)) % MOD;
		ans = ((ans - 1) % MOD + MOD) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}