#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
const int N = 10010;
int LOG[N], a[N], lmgcd[N][20], n, Q;
struct node {
	int itgcd, st, ed;
	node(int _itgcd = 0, int _st = 0, int _ed = 0) : itgcd(_itgcd), st(_st), ed(_ed) {} 
};
int gcd(int x, int y) {
	if (y == 0)
		return x;
	return gcd(y, x % y);
}
vector <node> q[N];
int qurey(int l, int r) {
	int len = LOG[r - l + 1];
	return gcd(lmgcd[l][len], lmgcd[r - (1 << len) + 1][len]);
}

int main() {
	int T, x, y;
	for (int i = 0; 1 << i < N; ++i)
        LOG[1 << i] = i;
    for (int i = 2; i < N; ++i)
        if (!LOG[i]) LOG[i] = LOG[i - 1]; 
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &a[i]);
		}
		for (int i = 1; i <= n; ++ i) {
			lmgcd[i][0] = a[i];
		}
		for (int j = 1; (1 << j) <= n; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				lmgcd[i][j] = gcd(lmgcd[i][j - 1], lmgcd[i + (1 << (j - 1))][j - 1]);
			}
		}
		for (int i = 1; i <= n; ++ i) {
			int itv_r = i;
			while (itv_r > 0) {
				int rct_gcd = qurey(itv_r, i);
				int l = 1, r = itv_r, mid;
				while (l <= r) {
					mid = (l + r) >> 1;
					if (qurey(mid, i) < rct_gcd) {
						l = mid + 1;
					}
					else {
						r = mid - 1;
					}
				}
				q[i].push_back(node(rct_gcd, l, itv_r));
				itv_r = l - 1;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < q[i].size(); ++j)
				printf("%d %d %d %d\n",i, q[i][j].itgcd, q[i][j].st, q[i][j].ed);
		}
		scanf("%d", &Q);
		while (Q--) {
			ll ans = 0;
			scanf("%d%d", &x, &y);
			//printf("---%d %d\n", x, y);
			int i;
			for (i = 0; i < q[y].size(); ++i) {
				if (q[y][i].st < x) {
					break;
				}
				ans += 1ll * (q[y][i].ed - q[y][i].st + 1) * q[y][i].itgcd;
				printf("----%I64d\n", ans);
			}
			if (i < q[y].size())
				ans += 1ll * (q[y][i].ed - x + 1) * q[y][i].itgcd;
			printf("%I64d\n", ans);
		}
	}
	return 0;
}