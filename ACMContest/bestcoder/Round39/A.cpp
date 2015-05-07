#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int n, ans, k, a[128];
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		scanf("%d", &k);
		sort(a, a+n);
		ans = 1;
		for (int i = 1; i < n; ++i)
			if (a[i] != a[i-1])
				ans++;
		if (n-ans >= k)
			printf("%d\n",ans);
		else
			printf("%d\n", ans - (k-(n-ans)));
	}
	return 0;
}