#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
string s[32];
map<>
int main() {
	int n;
	while (~scanf("%d", &n), n) {
		for (int i = 0; i < n; ++ i)
			cin >> s[i];
		for (int i = 0; i < n; ++ i)
			for (int j = i + 1; j < n; ++ j) {
				for (int t = 1; t <= s[i].size(); ++ t) {
					for (int k = 1; t <= s[j].size(); ++ k) {
						string tmp = s[i].substr(0, t) + s[j].substr(0, k);
						mp[tmp] = 1;
					}
				}
			}
		printf("%d\n", mp.count());
	}
	return 0;
}