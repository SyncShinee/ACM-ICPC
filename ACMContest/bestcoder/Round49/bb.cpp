#include <cstdio>
int main() {
	freopen("in.txt", "w", stdout);
	printf("1\n");
	for (int i = 1; i <= 9999; ++i)
		printf("a");
	printf("bc");
	for (int j = 1; j <= 9999; ++j)
		printf("a");
	return 0;
}