#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
	int n, k, f[512];
	for (int i = 1; i <= 500; ++i)
		f[i] = i*i;
	while (~scanf("%d%d", &n, &k)) {
		if (k*(k+1)/2 > n) {
			printf("NO\n");
			continue;
		}
		if (k == 2) {
			printf("YES\n");
			continue;
		}
		int *t = lower_bound(f+1, f+500, n);
		int ans = *(--t), tt = 0;
		int num = 0, i = 1;
		while (num < k-1) {
			if (i != n-ans) {
				tt += i;
				num++;
			}
			i++;
		}
		if (tt <= ans && !(tt == ans-1 && n-ans == k))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
