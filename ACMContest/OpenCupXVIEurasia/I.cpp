#include <bits/stdc++.h>

using namespace std;

const int maxn = 40;

int q;
unsigned int x;
unsigned int p[maxn][maxn];

void pre() {
    for(int i = 0; i <= 31; i++) {
	//printf("22    %d\n", i);
	for(int j = i; j <= 31; j++) {
	    unsigned int tmp = 1;
	    //printf("111    %u\n", tmp);
	    unsigned int res = 0;
	    for(int k = i; k <= j; k++) {
		unsigned int tk = k;
		res += (tmp << tk);
		p[i][j] = res;
	    }
	}
    }
    //printf("333\n");
}
unsigned int calcu(unsigned int x, int i, int j) {
    j = min(31, j);
    i = max(0, i);
    return (x & p[i][j]);
}

void solve() {
    //printf("44  %u\n", x);
    x -= (calcu(x, 0, 15) << 16);
    
    x ^= (calcu(x, 31 - 11 + 1, 31) >> 11);
    x ^= (calcu(x, 10, 20) >> 11);
    x ^= (calcu(x, 0, 9) >> 11);

    for(int now = 0;now <= 31; now += 3) {
	x -= (calcu(x, now, now + 3 - 1) << 3);
    }

    for(int now = 31; now >= 0; now -= 6) {
	x ^= (calcu(x, now - 6 + 1, now) >> 6);
    }

    for(int now  = 0; now <= 31; now += 10) {
	x -= (calcu(x, now, now + 10 - 1) << 10);
    }
    printf("%u\n", x);
}

int main(){
    //freopen("I.txt", "r", stdin);
    pre();
    scanf("%d", &q);
    while(q--) {
	scanf("%u", &x);
	//printf("44  %u\n", x);
	solve();
    }
}
