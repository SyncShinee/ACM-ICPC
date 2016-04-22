#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 1e6 + 100;
const double eps = 1e-8;

int dcmp(double x) {
    if(fabs(x) < eps)
	return 0;
    if(x > eps)
	return 1;
    return -1;
}
int x[maxn], y[maxn], n;
double p[maxn];
int pn;

void calcu(int i, int j) {
    if(x[i] == x[j])
	return;
    double xa = x[i], ya = y[i], xb = x[j], yb = y[j];
    if(x[i] > x[j]) {
	swap(xa, xb);
	swap(ya, yb);
    }
    double sum = xb - xa;
    //printf("11  %f\n", sum);
    double sub = (yb * yb - ya * ya) / (xb - xa);
    double ans = (sum + sub) / 2 + min(x[i], x[j]);
    p[pn] = ans;
    pn++;
}

void solve() {
    pn = 0;
    for(int i = 0; i < n; i++) {
	for(int j = i + 1; j < n; j++) {
	    calcu(i, j);
	}
    }
    sort(p, p + pn);
    int cnt = 0;
    for(int i = 0; i < pn; i++) {
	if(i == 0 || dcmp(p[i] - p[i - 1]) != 0) {
	    cnt++;
	}
    }
    printf("%d\n", cnt + 1);
}
ll l = 1e12;

int main() {
    //freopen("A.txt", "r", stdin);
    ll cnt = 2;
    while(l > 1000) {
	l -= l / cnt;
	cnt++;
    }
    printf("%f\n", cnt);
    while(scanf("%d", &n) != EOF) {
	for(int i = 0; i < n; i++) {
	    scanf("%d%d", &x[i], &y[i]);
	}
	solve();
    }
    return 0;
}
