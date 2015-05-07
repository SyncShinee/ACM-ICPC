#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

struct node {
	ll a, b;
	friend bool operator <(node x, node y) {
		return x.b * y.a < y.b * x.a || (x.b * y.a == y.b * x.a && x.a > y.a);
	}
};

node p[100010];
int main() {
	int T, n, ans;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		scanf("%d%d", &p[0].a, &p[0].b);
		ans = 1;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &p[i].a, &p[i].b);
			if (p[0] < p[i]) {
				p[0] = p[i];
				ans = i+1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}