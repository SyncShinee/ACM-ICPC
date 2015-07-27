#include <cstdio>
#include <map>
#include <cstring>
#include <string>
using namespace std;
char s[200010];
string a[20010];
map<string, int> mp;
long long ans, sum[4], num, gc;
long long gcd(long long x, long long y) {
	if (y == 0)
		return x;
	return gcd(y, x % y);
}
int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		mp.clear();
		scanf("%d", &n);
		sum[0] = sum[1] = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			a[i] = "";
			int len = strlen(s);
			sum[len & 1]++;
			for (int j = 0; j < len; ++j)
				a[i] += s[j];
			mp[a[i]]++;
		}
		ans = sum[0] * sum[1];
		for (int i = 0; i < n; ++i) {
			long long tmp = mp[a[i]];
			if (tmp > 1) {
				ans = ans + tmp * (tmp - 1) / 2;
			}
			mp[a[i]] = 0;
		}
		num = (long long)n * (long long)(n-1) / 2;
		gc = gcd(ans, num);
		printf("%I64d/%I64d\n", ans/gc, num/gc);
	}
	return 0;
}