#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define N 200010
#define MOD 1000000007
using namespace std;

struct node {
	int x, y;

	friend bool operator < (node a, node b) {
		return a.x > b.x;
	}
}sol[N];

typedef long long ll;
int a[N], l[N], r[N];
int main() {
	int n, tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	a[0] = a[n+1] = 0;
	r[n] = n+1;
	for (int i = n-1; i > 0; --i) {
		tmp = i+1;
		while (a[i] <= a[tmp]) {
			tmp = r[tmp];
		}
		r[i] = tmp;
	}
	l[1] = 0;
	for (int i = 2; i <= n; ++i) {
		tmp = i-1;
		while (a[i] <= a[tmp]) {
			tmp = l[tmp];
		}
		l[i] = tmp;
	}
	for (int i = 1; i <= n; ++i) {
		sol[i].x = a[i];
		sol[i].y = r[i] - l[i] - 1;
	}
	sort(sol + 1, sol + n + 1);
	tmp = 1;
	for (int i = 1; i <= n; ++i) {
		while (i > sol[tmp].y) {

			tmp++;
		}
		//printf("%d %d\n", sol[tmp].x, sol[tmp].y);
		printf("%d%c", sol[tmp].x, i == n ? '\n' : ' ');
	}
	return 0;
}