#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int s[100010], manacher[200010];
int p[100010], n;
bool check(int x) {
	int tl = x * 2 + 1;
	for (int i = 1; i < n; ++i) {
		int x2 = i + tl - 1;
		if (p[i] >= tl && p[x2] >= tl) {
			return true;
		}
	}
	return false;
}
int main() {
	int mx = 0, id;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &s[i]);
	for (int i = 1; i <= n; ++i) {
		manacher[2*i-1] = '#';
		manacher[2*i] = s[i];
		manacher[0] = '$';
	}
	manacher[2*n+1] = '#';
	manacher[2*n+2] = 'k';
	for (int i = 1; i <= 2*n+1; ++i) {
		if(mx > i) {
			p[i] = min(p[2*id-i], mx-i);
		}
		else {
			p[i] = 1;
		}
		while (manacher[i+p[i]] == manacher[i-p[i]])
			p[i]++;
		if (i+p[i] > mx) {
			mx = i + p[i];
			id = i;
		}
	}
	for (int i = 1; i <= 2 * n; ++i)
		printf("%d---%d\n",i, p[i]);
	int l = 0, r = n, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	printf("%d\n", r);
	return 0;
}