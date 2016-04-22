#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

ll n;
void solve() {
    ll ln = -1;
    ll cnt = 2;
    while(ln != n) {
	ln = n;
	if(n % cnt == 0) {
	    n = -1;
	    break;
	}
	n = n - n / cnt;
	cnt++;
    }
    printf("%lld\n", n);
    //    printf("%lld  %lld\n", cnt, n);
}

int main() {
    //freopen("H.txt", "r", stdin);
    //    n = 1e8 - 100;
    //    solve();
    int t;
    scanf("%d", &t);
    while(t--) {
	scanf("%lld", &n);
	solve();
    }
    return 0;
}
