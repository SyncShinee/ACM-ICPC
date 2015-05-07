#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, num, ans, modi;
const int sg0[30] = {0, 1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12};
bool vis[100010];
int main() {
	int i;
	while (~scanf("%d", &n)) {
		memset(vis, 0, sizeof(vis));
		num = 0;
		ans = 0;
		modi = n;
		for (int i = 2; i*i <= n; ++i) {
			if (vis[i])
				continue;
			num = 0;
			long long k = i;
			while (k <= n) {
				num++;
				if (k*k <= n)
					vis[k] = true;
				k *= (long long)i;
			}
			ans ^= sg0[num];
			modi -= num;
		}
		ans ^= modi%2;
		if (ans)
			printf("Vasya\n");
		else
			printf("Petya\n");
	}
	return 0;
}