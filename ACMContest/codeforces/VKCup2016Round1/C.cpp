#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 200010;
ll fr[N], nr[N];
ll a[N];
ll n, k;
ll INF = 5e16 + 10;
int main() {
    scanf("%lld%lld", &n, &k);
    for (int i = 0; i <= n; ++ i) {
	scanf("%lld", &a[i]);
    }
    int r = n;
    for (int i = 1; i <= n; ++ i) {
	fr[i] = fr[i - 1] + a[i - 1];
	if (fr[i] & 1) {
	    r = i - 1;
	    break;
	}
	else {
	    fr[i] >>= 1;
	}
    }
    int l = 0;
    for (int i = n - 1; i >= 0; -- i) {
	nr[i] = nr[i + 1] + a[i + 1];
	nr[i] *= 2;
	if (abs(nr[i]) > INF) {
	    l = i + 1;
	    break;
	}
    }
    int ans = 0;
    /*printf("%d %d\n", l, r);
    for (int i = 0; i <= 2; ++ i) {
	printf("rrr%d %d\n", fr[i], nr[i]);
	}*/
    for (int i = l; i <= r; ++ i) {
	ll tmp = -fr[i] - nr[i];
	if (tmp == 0 && i == n) continue;
	if (abs(tmp) > k) continue;
	//	printf("%d---%d\n", tmp, i);
	ans++;
    }
    printf("%d\n", ans);
    return 0;
}
