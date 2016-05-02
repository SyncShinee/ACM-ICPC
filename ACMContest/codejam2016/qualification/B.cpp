#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[128];
int a[128];
int f[128][2];
int main() {
	int T;
	freopen("B-large.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%s", s);
		printf("Case #%d: ", cas);
		int n = strlen(s);
		for (int i = 1; i <= n; ++ i) {
			a[i] = s[i - 1] == '-' ? 0 : 1;
		}
		f[0][0] = f[0][1] = 0;
		for (int i = 1; i <= n; ++ i) {
			int j = i - 1;
			while (j >= 1 && a[j] == a[i]) {
				j --;
			}
			if (j == 0) {
				f[i][a[i]] = 0;
				f[i][a[i] ^ 1] = 1;
			}
			else {
				f[i][a[i]] = f[j][a[i]];
				f[i][a[i] ^ 1] = f[j][a[i]] + 1;
			}
		}
		printf("%d\n", f[n][1]);
	}
	return 0;
}