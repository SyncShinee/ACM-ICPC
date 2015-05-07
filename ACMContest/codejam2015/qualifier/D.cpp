#include <cstdio>
using namespace std;
bool judge(int x, int r, int c) {
	if (x >= 7)
		return false;
	if (x == 1)
		return true;
	if (x == 2 && r * c % 2 == 0) {
		return true;
	}
	if (x == 3 && ((r % 3 == 0 && c >= 2) || (c % 3 == 0 && r >= 2))) {
		return true;
	}
	if (x == 4 && ((r % 4 == 0 && c >= 3) || (c % 4 == 0 && r >= 3))) {
		return true;
	}
	if (x == 4 && (r % 2 == 0 && c % 2 == 0 && r >= 6 && c >= 6)) {
		return true;
	}
	if (x == 5 && ((r % 5 == 0 && c >= 4) || (c % 5 == 0 && r >= 4))) {
		return true;
	}
	if (x == 6 && ((r % 6 == 0 && c >= 4) || (c % 6 == 0 && r >= 4))) {
		return true;
	}
	if (x == 6 && (r % 2 == 0 && c % 3 == 0 && r >= 4 && c >= 9)) {
		return true;
	}
	if (x == 6 && (c % 2 == 0 && r % 3 == 0 && c >= 4 && r >= 9)) {
		return true;
	}
	return false;
}
int main() {
	int x, r, c;
	freopen("D-large-practice.in", "r", stdin);
	freopen("dd.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d%d", &x, &r, &c);
		if (judge(x, r, c)) {
			printf("Case #%d: GABRIEL\n", cas);
		}
		else {
			printf("Case #%d: RICHARD\n", cas);
		}
	}
	return 0;
}