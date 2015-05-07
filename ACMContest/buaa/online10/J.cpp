#include <cstdio>
using namespace std;
long long p[100010], ans, n, f[100010];
int cas;
int main() {
	p[0] = 1;
	f[0] = 0;
	cas = 0;
	for (long long i = 1; i <= 100005; ++i){
		p[i] = (p[i-1]*i) % 1000000007;
		f[i] = ((i*f[i-1]) % 1000000007 + ((i-1)*p[i-1]) % 1000000007) % 1000000007;
	}
	while (~scanf("%lld", &n)) {
		cas++;
		printf("Case #%d: %lld\n", cas, f[n]);
	}
	return 0;
}