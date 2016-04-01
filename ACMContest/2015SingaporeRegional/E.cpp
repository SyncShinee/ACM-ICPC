#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m, v[32];
int main() {
    while (~scanf("%d%d", &n, &m)) {
	for (int i = 0; i < n; ++ i) {
	    scanf("%d", &v[i]);
	}
	swap(v[m], v[0]);
	sort(v + 1, v + n);
	int sum = 0;
	int num = 0;
	int ans = 0;
	for (int i = 0; i < n; ++ i) {
	    if (sum + v[i] <= 300) {
		sum += v[i];
		num++;
		ans += sum;
	    }
	    else {
		break;
	    }
	}
	printf("%d %d\n", num, ans);
    }
    return 0;
}
