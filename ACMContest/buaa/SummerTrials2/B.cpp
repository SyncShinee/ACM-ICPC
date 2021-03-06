#include <cstdio>
#include <cstring>
#define MOD 1000000007
using namespace std;
typedef long long ll;
ll f[2048][2048], n, k;
char s[2048];
int main() {
	//memset(f, 0, sizeof f);
	scanf("%I64d%I64d", &n, &k);
	scanf("%s", s+1);
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			f[i][j] = (f[i-1][j] * (s[i]-'a'+1)) % MOD;
			for (int t = 1; t*(n-i+1) <= j && t <= i; ++t) {
				f[i][j] = (f[i][j] + (f[i-t][j - t*(n-i+1)] * ('z' - s[i])) % MOD) % MOD;
				if (t < i)
					f[i][j] = ((f[i][j] - (f[i-t-1][j-t*(n-i+1)] * ('z' - s[i])) % MOD) % MOD + MOD) % MOD;
			}
		}
	}
	printf("%I64d\n", f[n][k]);
	return 0;
}