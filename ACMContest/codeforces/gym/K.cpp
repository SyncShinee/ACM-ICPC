#include <cstdio>
#include <cstring>
using namespace std;
int a[200][200], step[200], ans[200];
bool f[200];
int main() {
	int n, tmp, maxstep, anstmp;
	scanf("%d", &n);
	memset(step, 0, sizeof(step));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]);
	for (int t = 1; t <= n; ++t) {
		for (int i = 1; i <= n; ++i) {
			if (f[i])
				continue;
			tmp = maxstep = anstmp = 0;
			for (int j = 1; j <= n; ++j)
				if (a[i][j] == i || f[a[i][j]]) {
					if (maxstep < step[a[i][j]]) {
						maxstep = step[a[i][j]];
						anstmp = a[i][j];
					}
					tmp++;
				}
			if (tmp == n) {
				f[i] = true;
				step[i] = maxstep+1;
				ans[i] = anstmp;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}