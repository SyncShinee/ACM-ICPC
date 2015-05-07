#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
typedef long long ll;
ll a[300010], sum;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%I64d", &a[i]);
	}
	sort(a+1, a+n+1);
	if (n == 1)
		printf("%I64d\n", a[1]);
	else {
		sum = 0;
		for (int i = 1; i <= n; ++i)
			sum += (ll)(i+1)*a[i];
		sum -= a[n];
		printf("%I64d\n", sum);
	}
	return 0;
}