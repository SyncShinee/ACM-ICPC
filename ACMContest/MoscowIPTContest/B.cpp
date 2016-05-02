#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cmath>
using namespace std;
int a[16384], n, ans[16384];
char ch;
int main() {
    scanf("%d", &n);
    srand(time(NULL));
    for (int i = 0; i < n; ++ i) {
	a[i] = i;
    }
    for (int j = 0; j < 200; ++ j) {
	random_shuffle(a, a + n);
	int t = rand() % (int)(log(n)/log(2));
	int key = 1 << t;
	for (int i = 0; i < n; ++ i) {
	    ans[i] = 0;
	}
	for (int i = 0; i < key; ++ i) {
	    ans[a[i]] = 1;
	}
	for (int i = 0; i < n; ++ i) {
	    printf("%d", ans[i]);
	}
	puts("");
	fflush(stdout);
	scanf(" %c", &ch);
	if (ch == '+') {
	    break;
	}
    }
    return 0;
}
