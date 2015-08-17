#include <cstdio>
#include <algorithm>
#define INF 1000000009
using namespace std;
int a[32], b[32], tmpa[32], n, m;

int solve() {
	int pos = 1, rpos = 0, ans = 0, t = 1;
	while (pos < n) {
		if(a[pos] == a[pos-1]) {
			if (t == b[rpos]) {
				int tmp = pos + 1;
				while (tmp < n && a[tmp] == a[pos])
					tmp++;
				if (tmp == n)
					return INF;
				ans += tmp - pos;
				a[tmp] = a[tmp] ^ 1;
				a[pos] = a[pos] ^ 1;
				t = 1;
				rpos++;
			}
			else {
				t++;
			}
		}
		else {
			if (t < b[rpos]) {
				int tmp = pos+1;
				while (tmp < n && a[tmp] == a[pos])
					tmp++;
				if (tmp == n)
					return INF;
				ans += tmp - pos;
				a[tmp] = a[tmp] ^ 1;
				a[pos] = a[pos] ^ 1;
				t++;
			}
			else {
				t = 1;
				rpos++;
			}
		}
		pos++;
	}
	if (t == b[rpos])
		return ans;
	else 
		return INF;
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			tmpa[i] = a[i];
		}
		for (int i = 0; i < m; ++i) 
			scanf("%d", &b[i]);
		int ans = solve();
		for (int i = 0; i < n; ++i)
			a[i] = tmpa[i];
		int l = 1;
		while (a[l] == a[l-1] && l < n)
			l++;
		if (l < n) {
			a[0] ^= 1;
			a[l] ^= 1;
			ans = min(solve() + l, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}