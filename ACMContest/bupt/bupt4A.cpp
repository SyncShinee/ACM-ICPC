#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define oo 2000000000
using namespace std;
bool a[2000010];
int main() {
	int T, n, m, ans, l, r, tmp;
	scanf("%d", &T);
	while (T--) {
		ans = oo;
		memset(a,0,sizeof(a));
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &tmp);
			if (tmp <= m && a[m-tmp])
				if (ans > abs(m-tmp-tmp)) {
					ans = abs(m-tmp-tmp);
					l = min(tmp, m-tmp);
					r = max(tmp, m-tmp);
				}
			a[tmp] = true;
		}
		if (ans < oo)
			printf("%d %d\n", l, r);
		else
			printf("Sad\n");
	}
	return 0;
}