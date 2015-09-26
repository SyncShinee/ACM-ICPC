#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
long long n, m;
long long ans;
int main() {
	int T;
	scanf("%d", &T);
	while (T --) {
		scanf("%lld", &n);
		m = n;
		while (m - (int)sqrt(m) < n) {
			m += n - m + (int) sqrt(m);
		}
		long long l;
		ans = 0;
		for (l = 1; (l+1) * (l+1) <= m; ++ l) {
			ans += ((l + 1) * (l + 1) - l * l) * l;
			//printf("%lld\n", ans);
		}
		//printf("---%lld\n", l);
		ans += (m - l * l + 1) * l;
		printf("%lld %lld\n", m, ans);
	}
	return 0;
}