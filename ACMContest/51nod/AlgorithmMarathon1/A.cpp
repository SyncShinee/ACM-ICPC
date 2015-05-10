#include <cstdio>
#include <cstring>
#define MOD 10000007
typedef long long ll;
int n;
ll hash(char s[]) {
	ll ret = 0;
	for (int i = 0; i < (n >> 1); ++i) {
		ret = ((ret * 31) % MOD + s[i]) % MOD;
	}
	return ret;
}
char s[1000010], b[1000010];
int main() {
	while (~scanf("%s", s)) {
		n = strlen(s);
		if (n & 1) {
			printf("NO\n");
			continue;
		}
		for (int i = (n >> 1); i < n; ++i)
			b[i - (n >> 1)] = s[i];
		b[n >> 1] = s[n >> 1] = 0;
		if (strcmp(s, b) == 0) {
			printf("YES\n");
			continue;
		}
		printf("NO\n");
		continue;

		for (int i = n; i < 2 * n; ++i)
			s[i] = s[i - n];
		ll h1 = hash(s);
		ll h2 = hash(s + (n >> 1));
		ll po = 1;
		for (int i = 0; i < (n >> 1); ++i)
			po = (po * 31) % MOD;
		if (h1 == h2) {
			printf("YES\n");
			continue;
		}
		bool flag = false;
		for (int i = 1; i < n; ++i) {
			h1 = ((h1 * 31) % MOD + s[(n >> 1) + i - 1]) % MOD;
			h1 = ((h1 - (s[i - 1] * po) % MOD) % MOD + MOD) % MOD;
			h2 = ((h2 * 31) % MOD + s[n + i - 1]) % MOD;
			h2 = ((h2 - (s[(n >> 1) + i - 1] * po) % MOD) % MOD + MOD) % MOD;
			if (h1 == h2) {
				flag = true;
				printf("YES\n");
				break;
			}
		}
		if (!flag) {
			printf("NO\n");
		}
	}
}