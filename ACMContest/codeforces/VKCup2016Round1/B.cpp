#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int main() {
    int n, d, h;
    scanf("%d%d%d", &n, &d, &h);
    if (h > d || h + h < d || d >= n) {
	puts("-1");
	return 0;
    }
    if (d == 1) {
	if (n != 2) {
	    puts("-1");
	    return 0;
	}
    }
    int nw = 1;
    int tot = 1;
    for (int i = 0; i < h; ++ i) {
	tot ++;
	printf("%d %d\n", nw, tot);
	nw = tot;
    }
    nw = 1;
    for (int i = 0; i < d - h; ++ i) {
	tot ++;
	printf("%d %d\n", nw, tot);
	nw = tot;
    }
    if (h == 1) {
	for (int i = tot + 1; i <= n; ++ i) {
	    printf("%d %d\n", 1, i);
	}
    }
    else {
	for (int i = tot + 1; i <= n; ++ i) {
	    printf("%d %d\n", 2, i);
	}
    }
    return 0;
}
