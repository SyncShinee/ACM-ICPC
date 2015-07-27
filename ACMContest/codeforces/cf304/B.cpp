#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#define N 
#define MOD 1000000007
typedef long long ll;



int main() {
	ll k, n, w;
	scanf("%I64d%I64d%I64d", &k, &n, &w);
	ll tmp = (k + w * k) * w / 2;
	if (tmp <= n)
		printf("%d\n", 0);
	else {
		printf("%I64d\n", tmp - n);
	}
	return 0;
}