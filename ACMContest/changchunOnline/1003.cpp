#include <cstdio>
using namespace std;
int a[100010], f[100010];
int main() {
	a[1] = 1, a[2] = 2, a[3] = 2;
	int k = 4;
	f[1] = 2, f[2] = 3;
	for (int i = 3; i <= 100; ++ i) {
		for (int j = 0; j < a[i]; ++ j) {
			a[k++] = i;
		}
		f[i] = k - 1;
	}
	for (int i = 1; i <= 100; ++ i) {
		printf("%d%c", f[i], " \n"[i % 10 == 0]);
	}
	return 0;
}