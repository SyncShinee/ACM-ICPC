#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
char s[2][20];
int len;
ll ans[2];
ll mn;
/*void dfs(int x) {
	if (x == len + len) {
		//printf("sfd\n");
		int t0 = 0, t1 = 0;
		for (int i = 0; i < len; ++ i) {
			t0 *= 10;
			t0 += s[0][i] - '0';
			t1 *= 10;
			t1 += s[1][i] - '0';
		}
		if (abs(t0 - t1) < mn || (abs(t0 - t1) == mn && t0 < ans[0]) || (abs(t0 - t1) == mn && t0 == ans[0] && t1 < ans[1])) {
			mn = abs(t0 - t1);
			ans[0] = t0;
			ans[1] = t1;
		}
		return;
	}
	if (x < len) {
		if (s[0][x] == '?') {
			for (int i = 0; i <= 9; ++ i) {
				s[0][x] = i + '0';
				dfs(x + 1);
			}
			s[0][x] = '?';
		}
		else {
			dfs(x + 1);
		}
	}
	else {
		if (s[1][x - len] == '?') {
			for (int i = 0; i <= 9; ++ i) {
				s[1][x - len] = i + '0';
				dfs(x + 1);
			}
			s[1][x - len] = '?';
		}
		else {
			dfs(x + 1);
		}
	}
}*/
void dfs(int x) {
	if (x == len) {
		ll t0 = 0, t1 = 0;
		for (int i = 0; i < len; ++ i) {
			t0 *= 10;
			t0 += s[0][i] - '0';
			t1 *= 10;
			t1 += s[1][i] - '0';
		}
		if (abs(t0 - t1) < mn || (abs(t0 - t1) == mn && t0 < ans[0]) || (abs(t0 - t1) == mn && t0 == ans[0] && t1 < ans[1])) {
			mn = abs(t0 - t1);
			ans[0] = t0;
			ans[1] = t1;
		}
		return;
	}
	if (s[0][x] == '?' && s[1][x] == '?') {
		for (int i = 0; i <= 9; ++ i) {
			s[0][x] = i + '0';
			if (s[0][x] > '0') {
				s[1][x] = s[0][x] - 1;
			}
			else {
				s[1][x] = '9';
			}
			dfs(x + 1);
			s[1][x] = s[0][x];
			dfs(x + 1);
			if (s[0][x] < '9') {
				s[1][x] = s[0][x] + 1;
			}
			else {
				s[1][x] = '0';
			}
			dfs(x + 1);
			s[1][x] = '?';
		}
		s[0][x] = s[1][x] = '?';
	}
	else if (s[0][x] == '?') {
		if (s[1][x] > '0') {
			s[0][x] = s[1][x] - 1;		
		}
		else {
			s[0][x] = '9';
		}
		dfs(x + 1);
		s[0][x] = s[1][x];
		dfs(x + 1);
		if (s[1][x] < '9') {
			s[0][x] = s[1][x] + 1;
		}
		else {
			s[0][x] = '0';
		}
		dfs(x + 1);
		{
			s[0][x] = '0';
			dfs(x + 1);
			s[0][x] = '9';
			dfs(x + 1);
		}
		s[0][x] = '?';
	}
	else if (s[1][x] == '?'){
		if (s[0][x] > '0') {
			s[1][x] = s[0][x] - 1;
		}
		else {
			s[1][x] = '9';
		}
		dfs(x + 1);
		s[1][x] = s[0][x];
		dfs(x + 1);
		if (s[0][x] < '9') {
			s[1][x] = s[0][x] + 1;
		}
		else {
			s[1][x] = '0';
		}
		dfs(x + 1);
		{
			s[1][x] = '0';
			dfs(x + 1);
			s[1][x] = '9';
			dfs(x + 1);
		}
		s[1][x] = '?';
	}
	else {
		dfs(x + 1);
	}
}
void print(ll x, int b) {
	if (b == len) {
		printf("%lld", x);
	}
	else {
		print(x / 10, b + 1);
		printf("%lld", x % 10);
	}
}
int main() {
	int T;
	freopen("B-large.in", "r", stdin);
	freopen("out1.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		memset(s, 0, sizeof s);
		scanf("%s%s", s[0], s[1]);
		len = strlen(s[0]);
		mn = 100010;
		dfs(0);
		printf("Case #%d: ", cas);
		print(ans[0], 1);printf(" ");
		print(ans[1], 1);puts("");
			//printf("%lld %lld\n", ans[0], ans[1]);
	}
	return 0;
}