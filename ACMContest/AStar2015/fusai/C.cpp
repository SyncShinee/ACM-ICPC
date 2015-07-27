#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
struct node {
	int s, t;
	string str;
}e[512];
string dist[64][800];
int n, m, A, B;
int main() {
	int T, len;
	char ch[8];
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		printf("Case #%d:\n", cas);
		scanf("%d%d%d%d", &n, &m, &A, &B);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= 600; ++j) {
				dist[i][j] = "{";
			}
		dist[A][0] = "";
		for (int i = 0; i < m; ++i) {
			scanf("%d%d%s", &e[i].s, &e[i].t, ch);
			e[i].str = "";
			for (int j = 0; j < strlen(ch); ++j) {
				e[i].str += ch[j];
			}
		}
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				for (int t = 0; t <= 600; ++t) {
					len = t + e[j].str.size();
					if (dist[e[j].s][t] + e[j].str < dist[e[j].t][len]) {
						dist[e[j].t][len] = dist[e[j].s][t] + e[j].str;
					}
				}
			}
		}
		
		string ans = "{";
		for (int i = 0; i <= 600; ++i) {
			if (dist[B][i] < ans)
				ans = dist[B][i];
		}
		if (ans.size() > 300 || ans == "{") {
			printf("Tough way!\n");
		}
		else {
			cout << ans << endl;
		}
	}
	return 0;
}
