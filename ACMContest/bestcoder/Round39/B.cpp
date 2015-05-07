#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int n, a[10010], sum[10010], f[10010], ans;
int main() {
	while (~scanf("%d", &n)) {
		ans = 0;
		memset(f, 0, sizeof(f));
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; ++i) 
			scanf("%d", &a[i]);
		f[1] = 0;
		sum[a[1]] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j*j <= a[i]; ++j) {
				if (a[i] % j == 0) {
					f[i] += sum[j]*i;
					sum[j] = 0;
					f[i] += sum[a[i]/j]*i;
					sum[a[i]/j] = 0;
				}
			}
			sum[a[i]]++;
		}
		for (int i = 1; i <= n; ++i) {
			ans += f[i];
			//printf("%d\n", f[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}