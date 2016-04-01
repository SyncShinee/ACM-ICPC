#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 10;
int a[maxn], b[maxn];

void solve() {
    for(a[0] = 0; a[0] <= 2; a[0]++) {
	for(a[1] = 0; a[1] <= 2; a[1]++) {
	    for(a[2] = 0; a[2] <= 2; a[2]++) {
		int flag = 1;
		int tag = 0, num, now = b[0];
		for(int i = 0; i <= 2; i++) {
		    if(a[i] == 0) {
			if(tag == 0) {
			    tag = 1;
			    num = now;
			}
			else {
			    if(num != now) {
				flag = 0;
				break;
			    }
			}
			now = b[i + 1];
		    }
		    else if(a[i] == 1) {
			now += b[i + 1];
		    }
		    else if(a[i] == 2) {
			now -= b[i + 1];
		    }
		}
		if(flag == 0)
		    continue;
	        if(tag == 0)
		    continue;
		if(now != num)
		    continue;
		printf("%d", b[0]);
		for(int i = 0; i <= 2; i++) {
		    printf(" ");
		    if(a[i] == 0)
			printf("=");
		    if(a[i] == 1)
			printf("+");
		    if(a[i] == 2)
			printf("-");
		    printf(" %d", b[i + 1]);
		}
		printf("\n");
		return;
	    }
	}
    }
}

int main() {
    freopen("a.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
	printf("Case #%d: ", _);
	for(int i = 0; i <= 3; i++) {
	    scanf("%d", &b[i]);
	}
	solve();
    }
    return 0;
}
