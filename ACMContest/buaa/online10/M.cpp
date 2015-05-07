#include <cstdio>
using namespace std;
int a[100010], n, k, num;
int main() {
	while (~scanf("%d%d", &n, &k)) {
		num = 0;
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		for (int i = 1; i < n; ++i)
			if (a[i] != a[i-1])
				num++;
		printf("%d\n", num*k);
	}
	return 0;
}