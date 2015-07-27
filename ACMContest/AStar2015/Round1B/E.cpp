#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#define EPS 1e-9
#define N 100010
using namespace std;
typedef long long ll;
int n, a[N], q[N];
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		memset(q, 0, sizeof(q));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[i] -= i;
		}
		int head = 1, tail = 1;
		q[head] = a[1];
		for (int i = 2; i <= n; ++i) {
			if (a[i] >= q[tail]) {
				q[++tail] = a[i];
			}
			else {
				int l = 1, r = tail, mid;
				while (l <= r) {
					mid = (l + r) >> 1;
					if (q[mid] > a[i]) {
						r = mid - 1;
					}
					else {
						l = mid + 1;
					}
				}
				q[l] = a[i];
			}
		}
		printf("Case #%d:\n", cas);
		printf("%d\n", n-tail);
	}
	return 0;
}