#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
using namespace std;
const int N = 64;

int h[2560];

int main() {
	int T, x, n;
	freopen("B-large-practice.in", "r", stdin);
	freopen("ouot.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d", &n);
		memset(h, 0, sizeof h);
		for (int i = 1; i < 2 * n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				scanf("%d", &x);
				h[x]++;
			}
			
		}
		printf("Case #%d:", cas);
		for (int i = 1; i < 2560; ++ i) {
			if (h[i] & 1) {
				printf(" %d", i);
			}
		}
		puts("");
	}
	return 0;
}