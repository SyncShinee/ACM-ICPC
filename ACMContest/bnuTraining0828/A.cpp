#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int b[64], real[64], treal[64];
int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y); }
int Lcm(int x, int y) {return x * y / gcd(x, y); };
bool flag[64];
int main() {
	int T, n, l, r;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		for (int i = 1; i <= 52; ++ i) {
			scanf("%d", &real[i]);
			flag[i] = false;
		}
		scanf("%d%d%d", &n, &l, &r);
		for (int i = 1; i <= l - 1; ++ i) 	b[i] = r - l + i + 1;
		for (int i = l; i <= r; ++ i) 		b[i] = i - l + 1;
		for (int i = r + 1; i <= 52; ++ i)	b[i] = i;
		int tot = 0, lcm = 1;
		for (int i = 1; i <= 52; ++ i) {
			if (flag[i]) continue;
			int tmp = i, tnum = 0;
			while (!flag[tmp]) {
				flag[tmp] = true;
				tmp = b[tmp];
				tnum++;
			}
			lcm = Lcm(lcm, tnum);
		}
		n %= lcm;
		for (int i = 0; i < n; ++ i) {
			for (int i = 1; i <= 52; ++ i) treal[b[i]] = real[i];
			for (int i = 1; i <= 52; ++ i) real[i] = treal[i];
		}
		printf("Case #%d:", cas);
		for (int i = 1; i <= 52; ++ i) printf(" %d", real[i]);
		puts("");
	}
	return 0;
}