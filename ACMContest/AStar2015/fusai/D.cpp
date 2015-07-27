#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, r, ans, h[100010], ql[100010], qr[100010], headl, headr, taill, tailr, ansl, ansr;

ll calc(ll x, ll y) {
	ll tmpx, tmpy, tt;
	tmpy = y;
	tmpx = x;
	/*if (x % n == 0)
		tmpx = n;
	else 
		tmpx = x % n;
	if (y % n == 0)
		tmpy = n;
	else
		tmpy = y % n;*/
	if (tmpx > tmpy) {
		tt = tmpx;
		tmpx = tmpy;
		tmpy = tt;
	}
	return h[tmpx] + h[tmpy] + min((tmpy - tmpx) * r, (n - tmpy + tmpx) * r);
}

ll call(ll x, ll y) {
	ll tmpx, tmpy;
	if (x % n == 0)
		tmpx = n;
	else 
		tmpx = x % n;
	if (y % n == 0)
		tmpy = n;
	else
		tmpy = y % n;
	return min(tmpx, tmpy);
}

ll calr(ll x, ll y) {
	ll tmpx, tmpy;
	if (x % n == 0)
		tmpx = n;
	else 
		tmpx = x % n;
	if (y % n == 0)
		tmpy = n;
	else
		tmpy = y % n;
	return max(tmpx, tmpy);
}

int main() {
	ll T;
	scanf("%I64d", &T);
	for (ll cas = 1; cas <= T; ++cas) {
		printf("Case #%I64d:\n", cas);
		scanf("%I64d%I64d", &n, &r);
		for (ll i = 1; i <= n; ++i) {
			scanf("%I64d", &h[i]);
		}
		if (n == 2) {
			printf("1 2\n");
			continue;
		}
		headl = headr = 1;
		taill = tailr = 0;
		ll dui = (n+1)/2;
		for (ll i = 2; i <= dui; ++i) {
			while (headr <= tailr && calc(1, i) > calc(1, qr[tailr])) {
				tailr--;
			}
			qr[++tailr] = i;
		}
		for (ll i = (n+1)/2+1; i <= n; ++i) {
			while (headl <= taill && calc(1, i) > calc(1, ql[taill])) {
				taill--;
			}
			ql[++taill] = i;
		}
		
		ansl = 1; ansr = qr[headr];
		ans = calc(1, qr[headr]);
		if (ans < calc(1, ql[headl])) {
			ans = calc(1, ql[headl]);
			ansl = 1; ansr = ql[headl];
		}
		for (ll i = 2; i <= n; ++i) {
			dui++;
			if(dui > n)
				dui -= n;
			if (headl <= taill && ql[headl] == dui)
				headl++;
			if (headr <= tailr && qr[headr] == i)
				headr++;
			ll tmp1 = calc(i, i-1), tmp2 = calc(i, dui);
			while (headl <= taill && tmp1 > calc(i, ql[taill])) {
				taill--;
			}
			ql[++taill] = i-1;
			while (headr <= tailr && tmp2 > calc(i, qr[tailr])) {
				tailr--;
			}
			qr[++tailr] = dui;
			if (ans < calc(i, qr[headr])) {
				ans = calc(i, qr[headr]);
				ansl = call(i, qr[headr]);
				ansr = calr(i, qr[headr]);
			}
			if (ans < calc(i, ql[headl])) {
				ans = calc(i, ql[headl]);
				ansl = call(i, ql[headl]);
				ansr = calr(i, ql[headl]);
			}
		}
		printf("%I64d %I64d\n", ansl, ansr);
	}
	return 0;
}