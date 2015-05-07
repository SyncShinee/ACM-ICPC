#include <cstdio>
long long l, r, mid, m[1024];
long long b, n;
bool judge(long long x) {
	long long tmp = 0;
	for (long long i = 1; i <= b; ++i) {
		tmp += (x+m[i])/m[i];
	}
	if (tmp >= n)
		return true;
	return false;
}
int main() {
	freopen("B-large.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	long long T;
	scanf("%lld", &T);
	for (long long cas = 1; cas <= T; ++cas) {
		scanf("%lld%lld", &b, &n);
		for (long long i = 1; i <= b; ++i) {
			scanf("%lld", &m[i]);
		}
		l = 0; r = 100000000000000;
		while (l <= r) {
			mid = (l + r) / 2;
			if (judge(mid))
				r = mid-1;
			else
				l = mid+1;
		}
		//printf("%lld\n", l);
		long long kk = 0;
		for (long long i = 1; i <= b; ++i)
			kk += (l+m[i]-1)/m[i];
		for (long long i = 1; i <= b; ++i)
			if (l % m[i] == 0) {
				kk ++;
				if (kk == n) {
					printf("Case #%lld: %lld\n", cas, i);
				}
			}
			
	}
}