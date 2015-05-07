#include <cstdio>
using namespace std;
int n, a[32768];
bool judge(int x) {
	for (int i = 0; i < n-1; ++i) {
		if (a[i] - x*10 > a[i+1])
			return false;
	}
	return true;
}
int main() {
	freopen("A-large.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	int T, l, r, mid, ans1, ans2, mx;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		ans1 = 0;
		ans2 = 0;
		mx = 0;
		for (int i = 1; i < n; ++i)
			if (a[i] < a[i-1])
				ans1 += a[i-1]-a[i];
		for (int i = 1; i < n; ++i) {
			if (a[i] < a[i-1] && mx < a[i-1]-a[i])
				mx = a[i-1]-a[i];
		}
		//printf("%d\n", mx);
		for (int i = 0; i < n-1; ++i)
			if (a[i] <= mx)
				ans2 += a[i];
			else {
				ans2 += mx;
			}
		printf("Case #%d: %d %d\n", cas, ans1, ans2);
	}
	return 0;
}