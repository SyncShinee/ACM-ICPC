#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

vector <ll> ans;

bool judge(ll x, ll s) {
	ll tmp = 0;
	while (x > 0) {
		tmp += x % 10;
		x /= 10;
	}
	if (tmp == s)
		return true;
	return false;
}
int main() {
	ll a, b, c, cnt;
	scanf("%I64d%I64d%I64d", &a, &b, &c);
	ans.clear();
	for (ll i = 1; i <= 90; ++i) {
		ll tmp = 1;
		for (ll j = 0; j < a; ++j)
			tmp *= i;
		tmp *= b;
		tmp += c;
		if (tmp < 1000000000 && judge(tmp, i))
			ans.push_back(tmp);
	}
	cnt = ans.size();
	printf("%I64d\n", cnt);
	for (ll i = 0; i < cnt; ++i)
		printf("%I64d%c", ans[i], (i == cnt-1) ? '\n' : ' ');
	return 0;
}