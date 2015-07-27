#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#define N 
#define DEBUG 1
using namespace std;
typedef long long ll;
int n;
void init() {
	scanf("%d", &n);
	gets(s[0]);
	for (int i = 0; i < n; ++i)
		gets(s[i]);
	for (int i = 0 i < (1 << (n-2))-1; ++i) {
		tt = "";
		e.clear();
		f.clear();
		for (int j = 0; j < strlen(s[0]); ++j) {
			if (s[0][j] != ' ' && s[0][j] != '\n') {
				tt += s[0][j];
			}
			else {
				e[tt] = 1;
				tt = "";
			}
		}
		e[tt] = 1;
		tt = "";
		for (int j = 0; j < strlen(s[1]); ++j) {
			if (s[1][j] != ' ' && s[1][j] != '\n') {
				tt += s[1][j];
			}
			else {
				f[tt] = 1;
				tt = "";
			}
		}
		f[tt] = 1;
		for (int k = 2; k < n; ++k) {
			if ((1 << (k-2)) && i) {
				tt = "";
				for (int j = 0; j < strlen(s[k]); ++k) {
					if (s[k][j] != ' ' && s[k][j] != '\n') {
						tt += s[k][j];
					}
					else {
						e[tt] = 1;
						tt = "";
					}
				}
				e[tt] = 1;
			}
			else {
				tt = "";
				for (int j = 0; j < strlen(s[k]); ++k) {
					if (s[k][j] != ' ' && s[k][j] != '\n') {
						tt += s[k][j];
					}
					else {
						f[tt] = 1;
						tt = "";
					}
				}
				f[tt] = 1;
			}
		}
		for (int )
	}
}

void stress() {

}

void solve() {

}

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		init();
		if (DEBUG == 1) {
			stress();
		}
		else {
			solve();
		}
	}
}