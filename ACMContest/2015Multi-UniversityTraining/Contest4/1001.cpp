#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 100010;
int a[N];
bool judge(int x) {
	bool k[10] = {0};
	while (x) {
		int tmp = x % 10;
		if (k[tmp]) return false;
		k[tmp] = true;
		x /= 10;
	}
	return true;
}
int main() {
	int T, x, y;
	scanf("%d", &T);
	for (int i = 1; i < N; ++i) {
		a[i] = judge(i);
	}
	for (int i = 1; i < N; ++ i) a[i] += a[i - 1];
	while (T --) {
		scanf("%d%d", &x, &y);
		printf("%d\n", a[y] - a[x - 1]);
	}
	return 0;
}