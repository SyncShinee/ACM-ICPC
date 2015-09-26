#include <cstdio>
#include <cstring>
using namespace std;
char s[1000010];
int main() {
	int T;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);gets(s);
	for (int cas = 1; cas <= T; ++ cas) {
		gets(s);
		//scanf("%s", s);
		int front = 0, pre = -100, ans = 0;
		bool flag = true;
		int len = strlen(s);
		if (len == 0) {
			printf("Case #%d: 0\n", cas);
			continue;
		}
		for (int i = 0; i < len; ++ i) {
			if (s[i] == 'c') {
				if (s[i] - pre > 2) {
					if (pre == -100) {
						front = i;
					}
					pre = i;
					ans++;
				}
				else {
					flag = false;
					break;
				}
			}
			else if (s[i] != 'f') {
				flag = false;
				break;
			}
		}
		if (len - pre + front < 3) {
			flag = false;
		} 
		if (flag) {
			if (ans == 0) ans = (len + 1) / 2;
			printf("Case #%d: %d\n", cas, ans);
		}
		else {
			printf("Case #%d: -1\n", cas);
		}
	}
	return 0;
}