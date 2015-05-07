#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int f[100010], n, m;
ll s[100010];
int gf(int x) {
	if (f[x] == x)
		return x;
	return f[x] = gf(f[x]);
}
void merge(int x, int y) {
	int i = gf(x), j = gf(y);
	f[i] = j;
	f[x] = j;
	s[j] += s[i];
}
bool judge(int x, int y) {
	if (gf(x) == gf(y))
		return true;
	return false;
}
int main() {
	int T, cas, x, y;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(s,0,sizeof(s));
		for (int i = 1; i <= n; ++i) {
			f[i] = i;
			scanf("%d", &s[i]);
		}
		while (m--) {
			scanf("%d", &cas);
			if (cas == 1) {
				scanf("%d%d", &x, &y);
				if (!judge(x, y))
					merge(x, y);
			}
			else {
				scanf("%d", &x);
				printf("%lld\n", s[gf(x)]);
			}
		}
	}
	return 0;
}