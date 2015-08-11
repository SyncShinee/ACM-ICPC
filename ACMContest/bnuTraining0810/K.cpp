#include <cstdio>
#include <algorithm>
using namespace std;
int n, l;
int main() {
	while (~scanf("%d%d", &n, &l)) {
		if ((l & 1) || l < 4) {
			printf("Unsuitable device\n");
			continue;
		}
		if ((n & 1) == 0 && n * n < l) {
			printf("Unsuitable device\n");
			continue;
		}
		if ((n & 1) == 1 && n * n - 1 < l) {
			printf("Unsuitable device\n");
			continue;
		}
		printf("Overwhelming power of magic\n");
		if (l <= 4 * n - 4) {
			if (l / 2 <= n) {
				for (int i = 1; i <= l / 2; ++i) {
					printf("%d %d\n", 1, i);
				}
				for (int i = l / 2; i > 0; --i) 
					printf("%d %d\n", 2, i);
			}
			else {
				int remain = (l - 2 * n) / 2;
				for (int i = 1; i <= n; ++i)
					printf("%d %d\n", 1, i);
				for (int i = 2; i <= remain + 1; ++i)
					printf("%d %d\n", i, n);
				for (int i = n; i > 0; --i)
					printf("%d %d\n",remain + 2, i);
				for (int i = remain + 1; i > 1; --i) {
					printf("%d %d\n", i, 1);
				}
			}
		}
		else {
			if ((n & 1) == 0) {
				int remain = l - 4 * n + 4, now = 2;
				printf("1 1\n");
				while (remain >= 2 * (n - 2)) {
					remain -= 2 * (n - 2);
					for (int i = 1; i <= n - 1; ++i)
						printf("%d %d\n", now, i);
					now ++;
					for (int i = n - 1; i > 0; --i)
						printf("%d %d\n", now, i);
					now ++;
				}
				if (remain > 0) {
					for (int i = 1; i <= (remain / 2) + 1; ++i)
						printf("%d %d\n", now, i);
					now ++;
					for (int i = (remain / 2) + 1; i > 0; --i)
						printf("%d %d\n", now, i);
					now ++;
					remain = 0;
				}
				while (now <= n) {
					printf("%d %d\n", now, 1);
					now ++;
				}
				for (int i = 2; i <= n; ++i)
					printf("%d %d\n", n, i);
				for (int i = n - 1; i > 0; --i)
					printf("%d %d\n", i, n);
				for (int i = n - 1; i > 1; --i) 
					printf("%d %d\n", 1, i);
			}
			else {
				int remain = l - 4 * n + 4, now = 2;
				printf("1 1\n");
				while (now < n - 1 && remain >= 2 * (n - 2)) {
					remain -= 2 * (n - 2);
					for (int i = 1; i <= n - 1; ++i)
						printf("%d %d\n", now, i);
					now ++;
					for (int i = n - 1; i > 0; --i)
						printf("%d %d\n", now, i);
					now ++;
				}
				if (now < n - 1) {
					if (remain > 0) {
						for (int i = 1; i <= (remain / 2) + 1; ++i)
							printf("%d %d\n", now, i);
						now ++;
						for (int i = (remain / 2) + 1; i > 0; --i)
							printf("%d %d\n", now, i);
						now ++;
						remain = 0;
					}
					while (now <= n) {
						printf("%d %d\n", now, 1);
						now ++;
					}
					for (int i = 2; i <= n; ++i)
						printf("%d %d\n", n, i);
					for (int i = n - 1; i > 0; --i)
						printf("%d %d\n", i, n);
					for (int i = n - 1; i > 1; --i) 
						printf("%d %d\n", 1, i);
				}
				else {
					printf("%d %d\n%d %d\n",n - 1, 1, n, 1);
					int len = 2;
					while (remain > 0) {
						remain -= 2;
						printf("%d %d\n", n, len);
						printf("%d %d\n", n - 1, len);
						len ++;
						printf("%d %d\n", n - 1, len);
						printf("%d %d\n", n, len);
						len ++;
					}
					while (len <= n) {
						printf("%d %d\n", n, len);
						len++;
					}
					for (int i = n - 1; i > 0; --i)
						printf("%d %d\n", i, n);
					for (int i = n - 1; i > 1; --i) 
						printf("%d %d\n", 1, i);
				}
			}
		}
	}
	return 0;
}