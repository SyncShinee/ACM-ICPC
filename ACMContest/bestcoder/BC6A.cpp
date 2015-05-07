#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int n, a[1024], sum;
int main() {
	while (~scanf("%d", &n)) {
		sum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		sort(a, a+n);
		if (a[((n+1) >> 1) - 1] * n > sum)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}