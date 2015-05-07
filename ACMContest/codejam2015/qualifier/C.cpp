#include <cstdio>
#include <algorithm>
using namespace std;
long long l, x;
char s[10010];
int len;
bool find(long long length, char ch) {
	int label = 0;
	char tmp = '1';
	while (len < min(length , l*x)) {
		if (tmp == '1') {
			tmp = s[len%l];
		}
		else if (tmp == 'i') {
			if (s[len%l] == 'i') {
				tmp = '1';
				label ^= 1;
			}
			else if (s[len%l] == 'j') {
				tmp = 'k';
			}
			else if (s[len%l] == 'k') {
				tmp = 'j';
				label ^= 1;
			}
		}
		else if (tmp == 'j') {
			if (s[len%l] == 'i') {
				tmp = 'k';
				label ^= 1;
			}
			else if (s[len%l] == 'j') {
				tmp = '1';
				label ^= 1;
			}
			else if (s[len%l] == 'k') {
				tmp = 'i';
			}
		}
		else if (tmp == 'k') {
			if (s[len%l] == 'i') {
				tmp = 'j';
			}
			else if (s[len%l] == 'j') {
				tmp = 'i';
				label ^= 1;
			}
			else if (s[len%l] == 'k') {
				tmp = '1';
				label ^= 1;
			}
		}
		len++;
		if (tmp == ch && label == 0)
			return true;
	}
	return false;
}
int main() {
	freopen("C-large.in", "r", stdin);
	freopen("c.out", "w", stdout);
	int T, label;
	char tmp;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%lld%lld", &l, &x);
		scanf("%s", s);
		len = 0;
		if (!find(4*l, 'i')) {
			printf("Case #%d: NO\n", cas);
			continue;
		}
		//printf("11\n");
		if (!find(8*l, 'j')) {
			printf("Case #%d: NO\n", cas);
			continue;
		}
		//printf("22\n");
		int p = (len+l-1)/l;
		int remain = (x-p)%4;
		len = len%l;
		label = 0;
		tmp = '1';
		//printf("%d\n", len);
		while (len > 0 && len < l) {
			if (tmp == '1') {
				tmp = s[len];
			}
			else if (tmp == 'i') {
				if (s[len] == 'i') {
					tmp = '1';
					label ^= 1;
				}
				else if (s[len] == 'j') {
					tmp = 'k';
				}
				else if (s[len] == 'k') {
					tmp = 'j';
					label ^= 1;
				}
			}
			else if (tmp == 'j') {
				if (s[len] == 'i') {
					tmp = 'k';
					label ^= 1;
				}
				else if (s[len] == 'j') {
					tmp = '1';
					label ^= 1;
				}
				else if (s[len] == 'k') {
					tmp = 'i';
				}
			}
			else if (tmp == 'k') {
				if (s[len] == 'i') {
					tmp = 'j';
				}
				else if (s[len] == 'j') {
					tmp = 'i';
					label ^= 1;
				}
				else if (s[len] == 'k') {
					tmp = '1';
					label ^= 1;
				}
			}
			len++;
		}
		//printf("%d %c", remain,tmp);
		for (len = 0; len < remain*l; ++len) {
			if (tmp == '1') {
				tmp = s[len%l];
			}
			else if (tmp == 'i') {
				if (s[len%l] == 'i') {
					tmp = '1';
					label ^= 1;
				}
				else if (s[len%l] == 'j') {
					tmp = 'k';
				}
				else if (s[len%l] == 'k') {
					tmp = 'j';
					label ^= 1;
				}
			}
			else if (tmp == 'j') {
				if (s[len%l] == 'i') {
					tmp = 'k';
					label ^= 1;
				}
				else if (s[len%l] == 'j') {
					tmp = '1';
					label ^= 1;
				}
				else if (s[len%l] == 'k') {
					tmp = 'i';
				}
			}
			else if (tmp == 'k') {
				if (s[len%l] == 'i') {
					tmp = 'j';
				}
				else if (s[len%l] == 'j') {
					tmp = 'i';
					label ^= 1;
				}
				else if (s[len%l] == 'k') {
					tmp = '1';
					label ^= 1;
				}
			}
		}
		if (tmp == 'k' && label == 0) {
			printf("Case #%d: YES\n", cas);
			continue;
		}
		printf("Case #%d: NO\n", cas);
	}
	return 0;
}