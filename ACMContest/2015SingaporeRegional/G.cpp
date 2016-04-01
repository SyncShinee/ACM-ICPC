#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n;
ll a[4096];
int main() {
    while (~scanf("%d", &n)) {  
	for (int i = 0; i < n; ++ i) {
	    scanf("%lld", &a[i]);
	}
	ll last = -1000, tmp = 0;
	int ans = 0;
	for (int i = 0; i < n; ++ i) {
	    tmp += a[i];
	    if (tmp >= last) {
		last = tmp;
		ans ++;
		tmp = 0;
	    }
	}
	printf("%d\n", ans);
    }
    return 0;
}
