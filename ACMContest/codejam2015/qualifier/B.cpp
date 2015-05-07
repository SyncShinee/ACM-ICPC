#include <cstdio>
using namespace std;
int n, a[1024];
bool judge(int x) {
	int tmp;
	for (int i = 0; i < x; ++i) {
		tmp = i;
		for (int j = 0; j < n; ++j) {
			if (a[j] > x-i) {
				tmp -= (a[j]-1)/(x-i);
			}
		}
		if (tmp >= 0)
			return true;
	}
	return false;
}
int main() {
	int T;
	freopen("B-large.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		int l = 1, r = 1000, mid;
		while (l <= r) {
			mid = (l+r) >> 1;
			if(judge(mid))
				r = mid-1;
			else
				l = mid+1;
		}
		printf("Case #%d: %d\n", cas, l);
	}
	return 0;
}