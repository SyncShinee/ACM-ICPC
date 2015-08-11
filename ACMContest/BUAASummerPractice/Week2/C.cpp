#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define M 200010
using namespace std;
typedef long long ll;
int l, miu[M], tot, p[M];
ll C[50010];
bool flag[M];
vector <int> factor[M];

void mobius() {
	miu[1] = 1;
	tot = 0;
	for (int i = 2; i < M; ++ i) {
		if (! flag[i]) {
			miu[i] = -1;
			p[tot ++] = i;
		}
		for (int j = 0; j < tot && i * p[j] < M; ++ j) {
			flag[i * p[j]] = true;
			if (i % p[j]) {
				miu[i * p[j]] = - miu[i];
			}
			else {
				miu[i * p[j]] = 0;
				break;
			}
		} 
	}
}

void update(int x, int y) {
	while (x <= l) {
		C[x] += y;
		x += x & -x;
	}
}

ll getSum(int x) {
	ll ret = 0;
	while (x > 0) {
		ret += C[x];
		x -= x & -x; 
	}
	return ret;
}

int main() {
	int op, Q, cas = 1, nxt, n, d, v;
	ll ans;
	for (int i = 1; i < M; ++ i) {
		for (int j = i; j < M; j += i)
			factor[j].push_back(i);
	}
	mobius();
	while (scanf("%d%d", &l, &Q), l | Q) {
		memset(C, 0, sizeof C);
		printf("Case #%d:\n", cas ++);
		while (Q--) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d%d", &n, &d, &v);
				if (n % d) {
					continue;
				}
				int t = n / d;
				for (int i = 0; i < factor[t].size(); ++i) {
					update(factor[t][i] * d, miu[factor[t][i]] * v);
				}
			}
			else {
				scanf("%d", &n);
				ans = 0;
				for (int i = 1; i <= n; i = nxt + 1) {
					nxt = n / (n / i);
					ans += (getSum(nxt) - getSum(i - 1)) * (n / i);
				}
				printf("%I64d\n", ans);
			}
		}
	}
	return 0;
}