#include <cstdio>
using namespace std;
int a[128], n, k, mn, mx;
int main() {
	scanf("%d%d", &n, &k);
	mn = 128;
	mx = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] < mn)
			mn = a[i];
		if (a[i] > mx)
			mx = a[i];
	}
	if (mx - mn > k)
		printf("NO\n");
	else {
		printf("YES\n");
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= a[i]; ++j) {
				if (j <= mn+1)
					printf("%d%c", 1, (j == a[i]) ? '\n' : ' ');
				else 
					printf("%d%c", j-mn, (j == a[i]) ? '\n' : ' ');
			}
		}
	}
	return 0;
}