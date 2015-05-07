#include <cstdio>
#include <cstring>
using namespace std;

int main() {
	int n, num;
	scanf("%d", &n);
	num = 0;
	if (n < 4)
		printf("NO\n");
	else {
		printf("YES\n");
		if (n & 1 == 1) {
			while (n > 5) {
				printf("%d - %d = 1\n", n, n-1);
				num++;
				n -= 2;
			}
			while (num > 1) {
				printf("1 * 1 = 1\n");
				num--;
			}
			printf("1 + 3 = 4\n");
			printf("4 + 4 = 8\n");
			printf("5 - 2 = 3\n");
			printf("8 * 3 = 24\n");
			if (num > 0) {
				printf("24 * 1 = 24\n");
			}
		}
		else {
			while (n > 4) {
				printf("%d - %d = 1\n", n, n-1);
				num++;
				n -= 2;
			}
			while (num > 1) {
				printf("1 * 1 = 1\n");
				num--;
			}
			printf("1 + 2 = 3\n");
			printf("3 + 3 = 6\n");
			printf("4 * 6 = 24\n");
			if (num > 0)
				printf("24 * 1 = 24\n");
		}
	}
	return 0;
}