#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long ll;
const int N = 100010;
ll a[N][2], f[N][2];
int n;
using namespace std;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
	scanf("%lld", &a[i][0]);
    }
    for (int i = 1; i <= n; ++ i) {
	scanf("%lld", &a[i][1]);
    }
    memset(f, -1, sizeof f);
    f[1][1] = 0;
    for (int i = 1; i <= n; ++ i) {
	if (i > 1 && a[i][0] >= a[i - 1][0] && a[i][1] < a[i - 1][0]) {
	    f[i][0] = f[i - 1][0];
	}
	if (i > 1 && a[i][1] <= a[i - 1][1] && a[i][0] > a[i - 1][1]) {
	    f[i][1] = f[i - 1][1];
	}
	if (f[i][1] != -1 && (f[i][0] == -1 || f[i][0] > f[i][1] + a[i][0] - a[i][1])) {
	    f[i][0] = f[i][1] + a[i][0] - a[i][1];
	}
	if (f[i][0] != -1 && (f[i][1] == -1 || f[i][1] > f[i][0] + a[i][0] - a[i][1])) {
	    f[i][1] = f[i][0] + a[i][0] - a[i][1];
	}
	//printf("%lld %lld\n", f[i][0], f[i][1]);
    }
    printf("%lld\n", f[n][1]);
    return 0;
}
