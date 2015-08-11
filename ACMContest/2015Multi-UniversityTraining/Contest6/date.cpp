#include <cstdio>
#include <cstdlib>
#include <ctime>
int main () {
	freopen("in.txt", "w", stdout);
	printf("1\n");
	srand(time(NULL));
	int n = 100000;
	printf("%d\n", n);
	for (int i = 0; i < n; ++ i) {
		printf("%d ", 100000);
	}
}