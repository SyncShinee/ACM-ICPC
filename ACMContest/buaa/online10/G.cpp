#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll f[1024][1024], ans, sta[1024], n, m, top, h[1024][1024];
char s[2], a[1024][1024];
ll solve(char ch) {
	ll res = 0;
	memset(f, 0, sizeof(f));
	memset(h, 0, sizeof(h));
	for (int i = 1; i <= n; ++i) {
		top = 0;
		for (int j = 1; j <= m; ++j) {
			//printf("%d %d %c\n", i, j, ch);
			if (a[i][j] != ch) {
				top = 1;
				sta[top] = j;
				continue;
			}
			h[i][j] = h[i-1][j] + 1;
			if (h[i][j] >= h[i][j-1])
				f[i][j] = f[i][j-1] + h[i][j];
			else {
				while (top && h[i][sta[top]] >= h[i][j])
					top--;
				if (top == 0)
					f[i][j] = j*h[i][j];
				else
					f[i][j] = f[i][sta[top]] + (j-sta[top])*h[i][j];
			}
			sta[++top] = j;
			//printf("%d %d %lld %lld\n", i, j, f[i][j], top);
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			res += f[i][j];
	return res;
}
int main() {
	while (~scanf("%lld%lld", &n, &m)) {
		gets(s);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
				scanf("%c", &a[i][j]);
			gets(s);
		}
		ans = n*(n+1)*m*(m+1)/4;
		ans -= solve('W') + solve('B');
		printf("%lld\n", ans);
	}
	return 0;
}