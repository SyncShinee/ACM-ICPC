#include <cstdio>
using namespace std;
int main() {
	freopen("in.txt", "w", stdout);
	printf("1\n");
	printf("100000 1000000\n");
	for (int i = 0; i < 100000; ++i)
		printf("%d\n", i + 10);
	return 0;
}