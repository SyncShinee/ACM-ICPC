#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define MOD 1000000007
using namespace std;
typedef long long ll;
int p[N], tot;
bool flag[N];
void prime() {
	tot = 0;
	for (int i = 2; i < N; ++i) {
		if (!flag[i]) {
			p[tot++] = i;
		}
		for (int j = 0; j < tot && i * p[j] < N; ++j) {
			flag[i * p[j]] = true;
			if (i % p[j] == 0)
				break;
		}
	}
}

int main() {
	int T, n;
	slove();
	for (int i = 1; i <= T; ++i) {
		scanf("%d", &n);
		for ()
		printf("%lld\n",);
	}
	return 0;
}