#include <cstdio>
#include <cstring>
using namespace std;
char s[128], s1[128],s2[128];
int len1, len2, len;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", &s);
		len1 = len2 = 0;
		len = strlen(s);
		for (int i = 0; i < len; ++i) {
			if (i & 1) {
				s1[len1++] = s[i];
			}
			else {
				s2[len2++] = s[i];
			}
		}
		for (int i = 0; i < len2; ++i)
			printf("%c", s2[i]);
		printf("\n");
		for (int i = len1 - 1; i >= 0; --i)
			printf("%c", s1[i]);
		printf("\n");
	}
	return 0;
}