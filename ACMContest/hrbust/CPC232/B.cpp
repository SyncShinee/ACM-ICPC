#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int a[128], n, p, T;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &p);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		sort(a+1, a+n+1);
		int l = n;
		while (l > 0 && (n-l+1)*100 < n*p)
			l--;
		if (p == 0)
			printf("100\n");
		else
			printf("%d\n", a[l]);
	}
	return 0;
}