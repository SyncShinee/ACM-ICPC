#include <cstdio>
#define MAXN 100000000
#define MAXM 6000010
#define SHIFT 5
#define RADIX (1 << SHIFT) - 1
using namespace std;
typedef unsigned int u;
u ans;
int flag[(MAXN >> SHIFT) + 1];
u sum[MAXM];
int p[MAXM], tot, n;

inline void setBit(int x) {
	flag[x >> SHIFT] |= (1 << (x & RADIX));
}

inline bool getBit(int x) {
	return flag[x >> SHIFT] & (1 << (x & RADIX));
}

void prime() {
	tot = 0;
	for (int i = 2; i < MAXN; ++i) {
		if (!getBit(i)) {
			p[tot++] = i;
		}
		for (int j = 0; j < tot; ++j) {
			if (i * p[j] > MAXN)
				break;
			setBit(i * p[j]);
			if (i % p[j] == 0)
				break;
		}
	}
}

bool judge(int x, int expo) {
	long long tmp = 1;
	for (int i = 0; i < expo; ++i) {
		tmp *= x;
		if (tmp > n) {
			return false;
		}
	}
	return true;
}

int main() {
	int T, expo;
	scanf("%d", &T);
	prime();
	sum[0] = p[0];
	for (int i = 1; i < tot; ++i)
		sum[i] = sum[i - 1] * p[i];
	for (int cas = 1; cas <= T; ++cas) {
		ans = 1;
		scanf("%d", &n);
		expo = 1;
		while (true) {
			int l = 0, r = tot - 1, mid;
			while (l <= r) {
				mid = (l + r) >> 1;
				if (judge(p[mid], expo)) {
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			if (r == -1)
				break;
			ans *= sum[r];
			expo++;
		}
		printf("Case %d: %u\n", cas, ans);
	}
	return 0;
}