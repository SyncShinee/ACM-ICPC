#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 50 + 10;
vector<int> a[maxn];
int n;

int check(ll t) {
    ll now = 0;
    for(int i = 0; i < n; i++) {
	now = (now + a[i][0]) % t;
	ll tmp = a[i][0] % t;
	for(int j = 0; j < a[i].size(); j++) {
	    if(a[i][j] % t != tmp) {
		return 0;
	    }
	}
    }
    if(now != 0)
	return 0;
    return 1;
}

void solve() {
    ll sum = 0, ans = 1;
    for(int i = 0; i < n; i++) {
	//printf("-----   %d\n", a[i][0]);
	sum = sum + a[i][0];
    }
    //printf("sss  %lld\n", sum);
    for(ll i = 1; i * i <= sum; i++) {
	if(sum % i == 0) {
	    ll j = sum / i;
	    //printf("%lld  %lld\n", i, j);   
	    if(check(i))
		ans = max(ans, i);
	    if(check(j))
		ans = max(ans, j);
	}
    }
    printf("%lld\n", ans);
}

int main() {
    freopen("l.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
	printf("Case #%d: ", _);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
	    a[i].clear();
	    int m;
	    scanf("%d", &m);
	    for(int j = 0; j < m; j++) {
		int tmp;
		scanf("%d", &tmp);
		a[i].push_back(tmp);
	    }
	}
	solve();
    }
    return 0;
}
