#include <cstdio>
#include <algorithm>
using namespace std;
int n, a[200010], b[200010], len, m[2000010], l, ans, tmp;
int main() {
	scanf("%d", &n);
	a[0] = b[0] = 0;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	sort(a+1, a+n+1);
	len = 0;
	for (int i = 1; i <= n; ++i)
		if (a[i] != a[i-1])
			b[++len] = a[i];
	b[len+1] = 2000010;
	l = 1;
	ans = 0;
	for (int i = 0; i <= 2000000; ++i)
		if (i <= b[l])
			m[i] = b[l-1];
		else {
			m[i] = b[l];
			l++;
		}
	for (int i = 1; i <= len; ++i) {
		tmp = 2*b[i];
		while (tmp <= 2*b[len]) {
			if (m[tmp] > b[i] && ans < m[tmp] % b[i])
				ans = m[tmp] % b[i];
			tmp += b[i];
		}
	}
	printf("%d\n", ans);
	return 0;
}