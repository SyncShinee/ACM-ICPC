#include <cstdio>
using namespace std;
int main() {
	int n, m, t, f[16];
	f[0] = 1;
	for (int i = 1; i < 12; ++i)
		f[i] = f[i-1]*2;
	while (~scanf("%d%d", &n, &m)) {
		if (n > m) {
			t = n; 
			n = m;
			m = t;
		}
		printf("%d\n", (f[m]-1)*f[n]);
	}
	return 0;
}