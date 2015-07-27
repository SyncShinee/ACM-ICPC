#include <cstdio>
#define N 10000000
#define M 100000
using namespace std;

int p[M], miu[N], tot;
bool flag[N];

void mobius() {
	memset(flag, 0, sizeof(flag));
	tot = 0;
	miu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!flag[i]) {
			p[tot++] = i;
			miu[i] = -1;
		}
		for (int j = 0; j < tot && i * p[j] < N; ++j) {
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