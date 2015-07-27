#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ans, flag[4096], num[16];
char s[16][8];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		ans = 5;
		memset(flag, 0, sizeof(flag));
		memset(num, 0, sizeof(num));
		for (int i = 0; i < 5; ++i) {
			scanf("%s", s[i]);
			num[i] = s[i][0] - 'A';
			num[i] *= 100;
			int kkk = 0;
			for (int j = 1; j < strlen(s[i]); ++j) {

				kkk = kkk * 10 + s[i][j] - '0';
			}
			num[i] += kkk;
			//printf("%d\n", num[i]);
			flag[num[i]] = 1;
		}
		//printf("111\n");
		for (char tmp = 'A'; tmp <= 'D'; ++tmp) {
			for (int i = 1; i <= 10; ++i) {
				int tttt = 0;
				//printf("%d\n", i);
				for (int j = 0; j < 5; ++j) {
					if (i + j == 14) {
						if (flag[(tmp - 'A') * 100 + 1])
							tttt++;
					}
					else {
						if (flag[(tmp - 'A') * 100 + i + j])
							tttt++;
					}
				}
				ans = min(ans, 5 - tttt);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}