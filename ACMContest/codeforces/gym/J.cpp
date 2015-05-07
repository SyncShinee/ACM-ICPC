#include <cstdio>
#include <cstring>
#include <algorithm>
#define oo 2014091922
using namespace std;

int engine, query, f[1024][128], ans;
char elist[128][128], qlist[1024][128], s[128];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &engine);
		gets(s);
		for (int i = 1; i <= engine; ++i)
			gets(elist[i]);
		scanf("%d", &query);
		gets(s);
		for (int i = 1; i <= query; ++i)
			gets(qlist[i]);
		memset(f, 0x7F, sizeof(f));
		for (int i = 1; i <= engine; ++i)
			f[0][i] = 0;
		for (int i = 1; i <= query; ++i)
			for (int j = 1; j <= engine; ++j) {
				if (strcmp(qlist[i], elist[j]) == 0) {
					f[i][j] = oo;
					continue;
				}
				for (int k = 1; k <= engine; ++k) {
					if (k == j)
						f[i][j] = min(f[i][j], f[i-1][k]);
					else
						f[i][j] = min(f[i][j], f[i-1][k] + 1);
				}
			}
		ans = oo;
		for (int i = 1; i <= engine; ++i) {
			if (ans > f[query][i])
				ans = f[query][i];
		}
		printf("%d\n", ans);
	}
	return 0;
}