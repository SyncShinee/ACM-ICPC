#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[1024], n, p;
struct node {
	int v, num;
} b[1024];
int main() {
	while (~scanf("%d%d", &n, &p)) {
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		sort(a, a + n);
		int len = 0;
		for (int i = 0; i < n; ++i) {
			if (i == 0 || a[i] != a[i - 1]) {
				b[++len].v = a[i];
				b[len].num = 1;
			}
			else {
				b[len].num++;
			}
		}
		int l = 1, ans = 0, nu = 0, sum = 0;
		while (l <= len && b[l].v * b[l].num <= p) {
			nu = 0;
			while (l <= len && b[l].v * (nu + b[l].num) <= p) {
				nu += b[l].num;
				l++;
			}
			ans ++;
			sum += nu;
		}
		printf("%d %d\n", sum, ans);
	}
	return 0; 
}