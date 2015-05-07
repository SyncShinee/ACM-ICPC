#include <cstdio>
#include <cstring>
#define MOD 1000000007
using namespace std;
typedef long long ll;
ll len, mi, pow, ans;
ll ks() {
	ll ret = 1, mm = 2;
	while (pow) {
		if (pow & 1)
			ret = (ret * mm) % MOD;
		mm = (mm * mm) % MOD;
		pow >>= 1;
	}
	return ret;
}
char s[100010];
int main() {
	while (~scanf("%s", s)) {
		len = strlen(s);
		mi = 1;
		pow = 0;
		for (int i = len-1; i >= 0; --i) {
			pow = (((s[i] - '0') * mi) % (MOD-1) + pow) % (MOD-1);
			mi = (mi * 10) % (MOD-1);
		}
		pow = ((pow - 1) % MOD + MOD) % MOD;
		ans = ks();
		printf("%I64d\n", ans);
	}
	return 0;
}