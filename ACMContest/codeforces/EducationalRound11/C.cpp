#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 300010;
int a[N];
int main() {
    int n, k, ansl = 0, ansr = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i) {
	scanf("%d", &a[i]);
    }
    int r = 0, nw = 0;
    for (int l = 1; l <= n; ++ l) {
	if (r < l) {
	    r = l;
	}
	while (r <= n) {
	    if (a[r] == 0) {
		if (nw < k)
		    nw ++;
		else break;
	    }
	    r ++;
	}
	//printf("%d %d\n", l, r);
	if (ansr - ansl < r - l) {
	    ansl = l;
	    ansr = r;
	}
	if (r > l && a[l] == 0) nw --;
    }
    printf("%d\n", ansr - ansl);
    for (int i = 1; i <= n; ++ i) {
	if (i >= ansl && i < ansr) a[i] = 1;
	printf("%d%c", a[i], " \n"[i == n]);
    } 
    return 0;
}
