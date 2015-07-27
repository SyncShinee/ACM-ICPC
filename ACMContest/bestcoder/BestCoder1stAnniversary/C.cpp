#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
int a[100000];
int main() {
	int n;
	for (int i = 1; i <= 20000; ++i) {
		a[i] = 3 * (i - 1) * i + 1;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int x, ans = 0, pos;
		scanf ("%d", &x);
		if (x % 6 == 0 || x % 6 > 2) {
			printf("%d\n", x%6 == 0 ? 6 : x % 6);
		}
		else {
			if (x % 6 == 1) {
				if (a[lower_bound(a, a + 20000, x) - a] == x) {
					printf("1\n");
				}
				else {
					printf("7\n");
				}
			}
			else {
				bool flag = false;
				for (int i = 1; a[i] < x; ++i) {
					if (a[lower_bound(a, a + 20000, x - a[i]) - a] == x - a[i]) {
						flag = true;
						break;
					}
				}
				if (flag) {
					printf("%d\n", 2);
				}
				else {
					printf("%d\n", 8);
				}
			}
		}
	}
	return 0;
}