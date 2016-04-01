#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000 + 100;
const double key = 1e6;
const double INF = 1e30;

double a[maxn];
struct node {
    int id;
    double val;
    node(int _id = 0, double _val = 0) {
	id = _id;
	val = _val;
    }
};
node b[20];
int res[13];
int cmp(node a, node b) {
    return a.val > b.val;
}
double f[maxn][13];
int gi[maxn][13], gj[maxn][13];
int n, k;

void solve() {
    sort(b + 1, b + k + 1, cmp);
    f[0][0] = 0;
    for(int i = 1; i <= n; i++) {
	for(int j = 0; j <= k; j++) {
	    if(j > i)
		break;
	    if(j == 0) {
		f[i][j] = a[i];
		gi[i][j] = -1;
		gj[i][j] = -1;
	    }
	    else if(j == 1) {
		f[i][j] = b[j].val;
		gi[i][j] = -1;
		gj[i][j] = -1;
	    }
	    else {
		f[i][j] = -INF;
	    }
	    if(i - 1 >= 0 && (i - 1 >= j && f[i - 1][j] + a[i] > f[i][j])) {
		f[i][j] = f[i - 1][j] + a[i];
		gi[i][j] = i - 1;
		gj[i][j] = j;
	    }
	    if(j - 1 >= 0 && (f[i - 1][j - 1] + b[j].val > f[i][j])) {
		f[i][j] = f[i - 1][j - 1] + b[j].val;
		gi[i][j] = i - 1;
		gj[i][j] = j - 1;
	    }
	}	    
    }
    double ans = -INF;
    int ansi, ansj;
    for(int i = 1; i <= n; i++) {
	for(int j = 0; j <= k; j++) {
	    if(j > i)
		break;
	    if(f[i][j] > ans) {
		ans = f[i][j];
		ansi = i;
		ansj = j;
	    }
	}
    }
    //printf("%d  %d\n", ansi, ansj);
    int resr = ansi, resl = ansi;
    for(int i = 1; i <= 10; i++)
	res[i] = 0;
    int nowi = ansi, nowj = ansj;
    while(nowi != -1 && nowj != -1) {
	//	printf("111    %d  %d %d\n", nowi, nowj, gj[nowi][nowj]);
	if(gj[nowi][nowj] != nowj) {
	    // printf("****");
	    res[nowj] = nowi;
	}
	int nxti, nxtj;
	nxti = gi[nowi][nowj];
	nxtj = gj[nowi][nowj];
	nowi = nxti;
	nowj = nxtj;
	if(nowi != -1)
	    resl = nowi;
    }
    printf("%d %d\n", resl, resr);
    for(int i = 1; i <= k; i++) {
	for(int j = 1; j <= k; j++) {
	    if(b[j].id == i) {
		printf("%d", res[j]);
	    }
	}
	if(i == k)
	    printf("\n");
	else
	    printf(" ");
    }
}

int main() {
    freopen("k.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
	printf("Case #%d:\n", _);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) {
	    int l, r;
	    scanf("%d/%d", &l, &r);
	    a[i] = log(l) * key - log(r) * key;
	}
	for(int i = 1; i <= k; i++) {
	    int l, r;
	    scanf("%d/%d", &l, &r);
	    b[i].val = log(l) * key - log(r) * key;
	    b[i].id = i;
	}
	solve();
    }
    return 0;
}
