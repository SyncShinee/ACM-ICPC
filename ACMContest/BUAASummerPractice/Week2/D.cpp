#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 100010
using namespace std;
typedef long long ll;
int n, a[N], num[N], miu[N], p[N], tot;
ll sum[N];
bool flag[N];
vector <int> factor[N];
void mobius() {
	miu[1] = 1;
	tot = 0;
	for (int i = 2; i < N; ++ i) {
		if (!flag[i]) {
			p[tot ++] = i;
			miu[i] = -1;
		}
		for (int j = 0; j < tot && i * p[j] < N; ++ j) {
			flag[i * p[j]] = true;
			if (i % p[j]) {
				miu[i * p[j]] = -miu[i];
			}
			else {
				miu[i * p[j]] = 0;
				break;
			}
		}
	}
}

int main() {
	int T;
	ll tmp, rem, ans;
	scanf("%d", &T);
	mobius();
	for (int i = 1; i < N; ++ i) {
		if (miu[i] != 0) {
			for (int j = i; j < N; j += i) {
				factor[j].push_back(i);
			}
		}
	}
	while (T --) {
		scanf("%d", &n);
		memset(num, 0, sizeof num);
		for (int i = 0; i < n; ++ i) {
			scanf("%d", &a[i]);
			num[a[i]] ++;
		}
		for (int i = 1; i < N; ++ i) {
			sum[i] = 0;
			for (int j = i; j < N; j += i) {
				sum[i] += num[j];
			}
		}
		ans = 0;
		for (int i = 0; i < n; ++i) {
			tmp = 0;
			for (int j = 0; j < factor[a[i]].size(); ++ j) {
				tmp += miu[factor[a[i]][j]] * sum[factor[a[i]][j]];
			}
			if (a[i] == 1) {
				tmp --;
			}
			rem = n - tmp - 1;
			ans += tmp * rem;
		}
		printf("%I64d\n", 1ll * n * (n - 1) * (n - 2) / 6ll - ans / 2ll);
	}
	return 0;
}