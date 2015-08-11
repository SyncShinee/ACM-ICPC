#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 998244353
#define N 100005
using namespace std;
int n, a[N], lmgcd[N][20], itv_r, f[N], dp[N], C[N][2], Ci[N][2], len_q, len_v, LOG[N];

int gcd(int x, int y) {
	if (y == 0)
		return x;
	return gcd(y, x % y);
}

int qurey(int l, int r) {
	int len = LOG[r - l + 1];
	return gcd(lmgcd[l][len], lmgcd[r - (1 << len) + 1][len]);
}

struct node {
	int itvgcd, _l, _r, _id;
	node (int _itvgcd = 0, int __l = 0, int __r = 0, int __id = 0) : itvgcd(_itvgcd), _l(__l), _r(__r), _id(__id){}
};

bool operator < (const node &A, const node &B) {
	return A.itvgcd < B.itvgcd || A.itvgcd == B.itvgcd && A._id < B._id;
}

node q[N * 25];

int getSum(int x, int tag) {
	int ret = 0;
	while (x > 0) {
		if (C[x][0] == tag) {
			ret = (ret + C[x][1]) % MOD;
		}
		x -= x & -x;
	}
	return ret;
}

void update(int x, int y, int tag) {
	while (x <= n) {
		if (C[x][0] == tag) {
			C[x][1] = (C[x][1] + y) % MOD;
		}
		else {
			C[x][0] = tag;
			C[x][1] = y;
		}
		x += x & -x;
	}
}

int getSum_i(int x, int tag) {
	int ret = 0;
	while (x > 0) {
		if (Ci[x][0] == tag) {
			ret = (ret + Ci[x][1]) % MOD;
		}
		x -= x & -x;
	}
	return ret;
}

void update_i(int x, int y, int tag) {
	while (x <= n) {
		if (Ci[x][0] == tag) {
			Ci[x][1] = (Ci[x][1] + y) % MOD;
		}
		else {
			Ci[x][0] = tag;
			Ci[x][1] = y;
		}
		x += x & -x;
	}
}

int main() {
	for (int i = 0; 1 << i < N; ++i)
        LOG[1 << i] = i;
    for (int i = 2; i < N; ++i)
        if (!LOG[i]) LOG[i] = LOG[i - 1]; 
	while (~scanf("%d", &n)) {
		memset(C, 0, sizeof C);
		memset(Ci, 0, sizeof Ci);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &a[i]);
		}
		//预处理区间的gcd，与ST算法类似
		for (int i = 1; i <= n; ++ i) {
			lmgcd[i][0] = a[i];
		}
		for (int j = 1; (1 << j) <= n; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				lmgcd[i][j] = gcd(lmgcd[i][j - 1], lmgcd[i + (1 << (j - 1))][j - 1]);
			}
		}
		//通过二分求出所有gcd相同的区间，以(gcd, l, r, i)的形式保存在q 中
		len_q = 0;
		for (int i = 1; i <= n; ++ i) {
			itv_r = i;
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
				q[len_q ++] = node(rct_gcd, l, itv_r, i);
				itv_r = l - 1;
			}
		}
		sort(q, q + len_q);
		//根据gcd值的不同，分开dp，求最大值和方案数
		int nxt = 0, pre;
		int ans = 0, ans2 = 0;
		while (nxt < len_q) {
			pre = nxt;
			while (nxt < len_q && q[nxt].itvgcd == q[pre].itvgcd) {
				nxt++;
			}
			//nxt = lower_bound(q, q + len_q, node(q[pre].itvgcd, 0, 0, n + 1)) - q;
			//求最大值
			int cur = pre, mx = 0;
			for (int i = pre; i < nxt; ++ i) {
				f[q[i]._id] = 0;
				while (q[cur]._id < q[i]._r) {
					mx = max(mx, f[q[cur ++]._id]);
				}
				f[q[i]._id] = mx + 1;
			}
			//求方案数
			if (f[q[nxt - 1]._id] >= ans) {
				for (int i = pre, j = i; i < nxt; ++i) {
					while (j < i && f[q[j]._id] < f[q[i]._id] - 1) {
						update(q[j]._id, MOD - dp[q[j]._id], nxt);
						update_i(q[j]._id, 1ll * (MOD - dp[q[j]._id]) * q[j]._id % MOD, nxt);
						++ j;
					}
					if (f[q[i]._id] == 1) {
						dp[q[i]._id] = q[i]._r - q[i]._l + 1;
						update(q[i]._id, dp[q[i]._id], nxt);
						update_i(q[i]._id, 1ll * dp[q[i]._id] * q[i]._id % MOD, nxt);
						continue;
					}
					int L = q[i]._l, R = q[i]._r;
			        int tmp = 1ll * (R - L + 1) * getSum(L - 1, nxt) % MOD;
			        int res = (1ll * getSum_i(L - 1, nxt) - getSum_i(R, nxt) + MOD) % MOD;
			        res += (1ll * getSum(R, nxt) - getSum(L - 1, nxt)) * R % MOD;
			        if (res < 0) res += MOD;
			        if (res >= MOD) res -= MOD;
			        dp[q[i]._id] = (res + tmp) % MOD;
			        update(q[i]._id, dp[q[i]._id], nxt);
			        update_i(q[i]._id, 1ll * dp[q[i]._id] * q[i]._id % MOD, nxt);
				}
				if (ans < f[q[nxt - 1]._id]) {
					ans = f[q[nxt - 1]._id];
					ans2 = 0;
					int j = nxt - 1;
					while (j >= pre && f[q[j]._id] == ans) {
						ans2 = (ans2 + dp[q[j]._id]) % MOD;
						j --;
					}
				}
				else if (ans == f[q[nxt - 1]._id]){
					int j = nxt - 1;
					while (j >= pre && f[q[j]._id] == ans) {
						ans2 = (ans2 + dp[q[j]._id]) % MOD;
						j --;
					}
				}
			}
		}
		printf("%d %d\n", ans, ans2);
	}
	return 0;
}