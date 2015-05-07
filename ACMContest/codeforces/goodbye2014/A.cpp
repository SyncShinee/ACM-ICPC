#include <cstdio>
using namespace std;
int a[32768];
int main() {
	int n, t, k;
	scanf("%d%d", &n, &t);
	for (int i = 1; i < n; ++i)
		scanf("%d", &a[i]);
	k = 1;
	if (k == t) {
		printf("YES\n");
		return 0;
	}
	while (k < n && a[k] > 0) {
		k = k + a[k];
		if (k == t)
			break;
	}
	if (k == t)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}