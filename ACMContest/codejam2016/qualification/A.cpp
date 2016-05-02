#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int T, n;
bool dig[16];
int main() {
	freopen("A-large.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d", &n);
		printf("Case #%d: ", cas);
		if (n == 0) {
			puts("INSOMNIA");
			continue;
		}
		int hehe = n;
		memset(dig, 0, 10);
		int remain = 10;
		while (true) {
			int t = hehe;
			while (t > 0) {
				if (!dig[t % 10]) {
					remain--;
					dig[t % 10] = true;
				}
				t /= 10;
			}
			if (remain == 0) {
				break;
			}
			hehe += n; 
		}
		printf("%d\n", hehe);
	}
	return 0;

}