#include <cstdio>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long ll;
ll f[1000010];
int n, T;
int main() {
	scanf("%d", &T);
	f[1] = 1;
	f[2] = 2;
	for (int i = 3; i < 1000005; ++i)
		f[i] = (f[i-1] + ((i-1)*f[i-2]) % MOD) % MOD;
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		printf("Case #%d:\n", cas);
		printf("%I64d\n", f[n]);
	}
	return 0;
}