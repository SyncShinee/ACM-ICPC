#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[5000010], manacher[10000010];
int f[5000010], p[5000100];
int main() {
	int mx = 0, id, mid, ans = 0;
	scanf("%s", s+1);
	int len = strlen(s+1);
	for (int i = 1; i <= len; ++i) {
		manacher[2*i-1] = '#';
		manacher[2*i] = s[i];
		manacher[0] = '$';
	}
	manacher[2*len+1] = '#';
	manacher[2*len+2] = '\0';
	for (int i = 1; i <= 2*len+1; ++i) {
		if(mx > i) {
			p[i] = min(p[2*id-i], mx-i);
		}
		else {
			p[i] = 1;
		}
		while (manacher[i+p[i]] == manacher[i-p[i]])
			p[i]++;
		if (i+p[i] > mx) {
			mx = i + p[i];
			id = i;
		}
	}
	f[0] = 0;
	for (int i = 1; i <= len; ++i) {
		mid = i+1;
		if (p[mid]-1 >= i) {
			f[i] = f[i >> 1]+1;
		}
		else {
			f[i] = 0;
		}
		ans += f[i];
	}
	printf("%d\n", ans);
	return 0;
}