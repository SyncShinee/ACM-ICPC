#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 6e3 + 100;
const int M = 1e9 + 7.1;
const int key = 6000;

int add(int a, int b) {
    int c = a + b;
    if(c >= M)
	c -= M;
    return c;
}
int pow_mod(int x, int n) {
    int res = 1, tmp = x % M;
    while(n) {
	if(n & 1) {
	    res = (ll)res * (ll)tmp % M;
	}
	tmp = (ll)tmp * (ll)tmp % M;
	n >>= 1;
    }
    return res;
}
int rev(int x) {
    return pow_mod(x, M - 2);
}
int f[maxn][maxn], sg[3][maxn];
int now, last, llast;
int jc[maxn], jcr[maxn];
int n, k;

int numr[maxn];

void pre() {
    for(int i = 1; i <= key; i++) {
	numr[i] = rev(i);
    }
    jc[0] = 1;
    jcr[0] = 1;
    for(int i = 1; i <= key; i++) {
	jc[i] = (ll)jc[i - 1] * (ll)i % M;
	jcr[i] = rev(jc[i]);
    }
    memset(f, 0, sizeof(f));
    //memset(g, 0, sizeof(g));
    memset(sg, 0, sizeof(sg));
    f[0][0] = 1;
    llast = 0;
    last = 1;
    now = 2;
    //g[0][0] = 1;
    sg[0][0] = 1;
    sg[1][0] = 1;
    for(int i = 2; i <= key; i++) {
	sg[now][0] = sg[last][0];
	for(int j = 1; j <= i; j++) {
	    if(j - 1 <= i - 2)
		f[i][j] = (ll)jc[i - 1] * (ll)sg[llast][j - 1] % M;
	    else {
		f[i][j] = 0;
	    }
	    //g[i][j] = (ll)f[i][j] * (ll)jcr[i] % M;
	    sg[now][j] = add(sg[last][j], (ll)f[i][j] * (ll)jcr[i] % M);
	}
	int tmp = last, tt = llast;
	llast = last;
	last = now;
	now = tt;
    }
}
void solve() {
    pre();
    //    printf("%d  %d  %d\n", f[3][1], f[3][2], f[3][3]);
    int ans = 0;
    for(int num = 0; num <= 2 * k; num++) {
	int tmp = 1;
	int a = n;
	for(int b = 1; b <= num; b++) {
	    tmp = (ll)tmp * (ll)(a - b + 1) % M  * (ll)numr[b] % M;
	}
	//printf("%d  %d  %d\n", n, num, tmp);
	for(int j = max(0, num - k); j <= num; j++) {
	    ans = add(ans, (ll)tmp * (ll)f[num][j] % M);
	}
    }
    printf("%d\n", ans);
}

int main() {
    //freopen("E.txt", "r", stdin);
    while(scanf("%d %d", &n, &k) != EOF) {
	solve();
    }
    return 0;
}
