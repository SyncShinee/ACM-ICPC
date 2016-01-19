#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
	int n;
	while (~scanf("%d", &n)) {
		if (n < 4) {
			puts("-1");
		}
		else if (n == 4) {
			puts("1 * 2");
			puts("5 + 3");
			puts("6 + 4");
		}
		else if (n == 5) {
			puts("1 / 2");
			puts("6 / 3");
			puts("4 - 7");
			puts("5 * 8");
		}
		else if (n == 6) {
			puts("1 + 2");
			puts("3 / 4");
			puts("5 / 6");
			puts("8 + 9");
			puts("7 * 10");
		}
		else if (n == 7) {
			puts("1 + 2");
			puts("3 + 8");
			puts("9 / 4");
			puts("10 + 5");
			puts("11 + 6");
			puts("12 + 7");
		}
		else if (n == 8) {
			puts("1 - 2");
			puts("9 * 3");
			puts("10 * 4");
			puts("11 * 5");
			puts("12 + 6");
			puts("13 + 7");
			puts("14 + 8");
		}
		else if (n == 9) {
			puts("1 + 2");
			puts("10 + 3");
			puts("11 / 4");
			puts("5 + 6");
			puts("7 / 8");
			puts("9 + 14");
			puts("13 - 15");
			puts("12 * 16");
		}
		else if (n == 10) {
			puts("1 / 2");
			puts("3 / 4");
			puts("5 / 6");
			puts("7 / 8");
			puts("9 + 10");
			puts("11 + 12");
			puts("13 + 14");
			puts("15 + 16");
			puts("17 + 18");
		}
		else if (n == 11) {
			puts("1 / 2");
			puts("3 / 4");
			puts("5 / 6");
			puts("7 + 8");
			puts("9 + 10");
			puts("15 / 11");
			puts("16 + 17");
			puts("18 * 12");
			puts("19 * 13");
			puts("20 * 14");
		}
		else if (n == 13) {
			puts("1 + 2");
			puts("14 + 3");
			puts("15 / 4");
			puts("5 + 6");
			puts("7 + 8");
			puts("9 + 10");
			puts("17 / 11");
			puts("18 / 12");
			puts("19 / 13");
			puts("16 * 20");
			puts("21 * 22");
			puts("23 * 24");
		}
		else {
			puts("1 + 2");
			puts("3 + 4");
			puts("5 + 6");
			puts("7 + 8");
			printf("9 + %d\n", n + 1);
			printf("%d + %d\n", n + 2, n + 3);
			printf("%d / 10\n", n + 4);
			printf("%d / 11\n", n + 5);
			printf("%d / 12\n", n + 6);
			printf("%d * %d\n", n + 7, n + 8);
			printf("%d * %d\n", n + 9, n + 10);
			if (n > 12) {
				puts("13 - 14");
				for (int i = 15; i <= n; ++ i) {
					printf("%d * %d\n", n + i - 3, i);
				}
				printf("%d + %d\n", n + 11, 2 * n - 2);
			}
		}
	}
	return 0;
}