#include <cstdio>
using namespace std;
int main() {
	int T, x, y, z;
	freopen("D-small-attempt0.in", "r", stdin);
	freopen("D.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		printf("Case #%d: ", cas);
		scanf("%d%d%d", &x, &y, &z);
		for (int i = 1; i <= x; ++ i) {
			printf("%d%c", i, " \n"[i == x]);
		}
	}
	return 0;
}