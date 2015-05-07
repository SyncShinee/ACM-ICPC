#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int t, n, a;
ll f[1024], b;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(f, 0, sizeof(f));
		scanf("%d%d", &t, &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%lld", &a, &b);
			for (int j = t; j >= a; --j)
				if (f[j] < f[j-a] + b)
					f[j] = f[j-a] + b;
		}
		printf("%lld\n", f[t]);
	}
	return 0;
}