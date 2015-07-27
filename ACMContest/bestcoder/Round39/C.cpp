#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 10240
#define MOD 10007
using namespace std;
int p[N], miu[N], num[N], sum[N], tot, mx;
bool flag[N];

void mobius() {
	memset(flag, 0, sizeof(flag));
	miu[1] = 1;
	tot = 0;
	for (int i = 2; i < N; ++i) {
		if (!flag[i]) {
			p[tot++] = i;
			miu[i] = -1;
		}
		for (int j = 0; j < tot & i * p[j] < N; ++j){
			flag[i*p[j]] = 1;
			if (i % p[j])
				miu[i*p[j]] = -miu[i];
			else {
				miu[i*p[i]] = 0;
				break;
			}
		}
	}
}

int solve1() {
	int ret = 0, tmp;
	for (int i = 1; i <= mx; ++i) {
		tmp = 0;
		for (int j = i; j <= mx; j += i) {
			tmp = (tmp + miu[j/i] * num[j]) % MOD;
		}
		tmp = ((tmp * i) % MOD * (i - 1)) % MOD;
		
		ret = (ret + tmp) % MOD;
	}
	return ret;
}

int solve2() {
	int ret = 0;
	for (int i = mx; i > 0; --i) {
		for (int j = i + i; j <= mx; j += i)
			num[i] = ((num[i] - num[j]) % MOD + MOD) % MOD;
		ret = (((num[i] * i) % MOD * (i - 1)) % MOD + ret) % MOD;
	}
	return ret;
}

int main() {
	int n, ans, tmp;
	mobius();
	while (~scanf("%d", &n)) {
		memset(sum, 0, sizeof(sum));
		memset(num, 0, sizeof(num));
		mx = ans = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &tmp);
			mx = max(mx, tmp);
			sum[tmp]++;
		}
		for (int i = 1; i <= mx; ++i) {
			for (int j = i; j <= mx; j += i)
				num[i] = (num[i] + sum[j]) % MOD;
		}
		for (int i = 1; i <= mx; ++i)
			num[i] = (num[i] * num[i]) % MOD;

		ans = solve1();

		//ans = solve2();
		
		printf("%d\n", ans);
	}
	return 0;
}