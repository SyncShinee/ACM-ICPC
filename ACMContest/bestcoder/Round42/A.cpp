#include <cstdio>
#include <cstring>
using namespace std;
int main() {
	int n, ans;
	while (~scanf("%d", &n)) {
		ans = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				int a;
				scanf("%d", &a);
				if (a)
					ans ++;
			}
		ans += 2*n;
		printf("%d\n", ans);
	}
	return 0;
}