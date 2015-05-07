#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
	int n, k;
	while (~scanf("%d%d", &n, &k)) {
		if (k > 2) {
			printf("0\n");
			continue;
		}
		if (k == 2) {
			printf("1\n");
			continue;
		}
		int t = (int)sqrt(n), num = 0;
		for (int i = 1; i <= t; ++i) {
			if (n % i == 0)
				num++;
		}
		num = (num*2)%1000000009;
		if (t*t == n)
			num = (num-1)%1000000009;
		printf("%d\n", num);
	}
	return 0;
}