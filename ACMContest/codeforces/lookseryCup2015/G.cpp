#include <cstdio>
#define N 200010
using namespace std;
struct node {
	int val, idx;
	friend bool operator < (node x, node y) {
		return x.val < y.val;
	}
}a[N];
int n, m;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i].val);
		a[i].val -= n-i;
		a[i].idx = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; ++i) {
		if (a[i].val == a[i-1].val) {
			printf(":(\n");
				return 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d ", a[i].val + n - i);
	}
	return 0;
}