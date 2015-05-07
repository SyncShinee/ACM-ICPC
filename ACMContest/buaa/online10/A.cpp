#include <cstdio>
using namespace std;
int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		if (m > (n >> 1))
			printf("Wonderful Contest!\n");
		else
			printf("_(:3_|Z)_\n");
	}
	return 0;
}