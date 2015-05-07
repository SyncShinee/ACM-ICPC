#include <cstdio>
#include <cstring>
using namespace std;
char s[100010];
int main() {
	int l, m, bl, bm, len;
	while (~scanf("%s", s)) {
		l = m = 0;
		len = strlen(s);
		for(int i = 0; i < len; ++i) {
			if (s[i] >= 'a' && s[i] <= 'z') {
				m++;
				bm = i;
			}
			if (s[i] >= 'A' && s[i] <= 'Z') {
				l++;
				bl = i;
			}
		}
		if (l == 1 && m != 1) {
			printf("%d\n", bl+1);
		}
		else if (l != 1 && m == 1) {
			printf("%d\n", bm+1);
		}
		else
			printf("-1\n");
	}
	return 0;
}