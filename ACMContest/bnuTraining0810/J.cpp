#include <cstdio>
using namespace std;
int main() {
	int a, b, c, d, n;
	while (~scanf("%d%d", &a, &b)) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &c, &d);
			if ((c >= a && d >= b) || (c >= b && d >= a)) {
				printf("Block the hole\n");
			}
			else {
				printf("Too small\n");
			}
		}
	}
	return 0;
}