#include <cstdio>
#include <map>

using namespace std;
map<int, int> mp;
int num[100010], ans[100010];
bool flag;
int main() {
	int n, a, b;
	flag = true;
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &num[i]);
		mp[num[i]] = i;
	}
	for (int i = 1; i <= n; ++i) {
		if (mp[num[i]] && mp[a-num[i]] && num[i] != a-num[i]) {
			ans[mp[num[i]]] = ans[mp[a-num[i]]] = 0; 
			mp[num[i]] = mp[a-num[i]] = 0;
		}
		else if (mp[num[i]] && mp[b-num[i]] && num[i] != b-num[i]) {
			ans[mp[num[i]]] = ans[mp[b-num[i]]] = 1; 
			mp[num[i]] = mp[b-num[i]] = 0;
		}
		else if (mp[num[i]]) {
			flag = false;
			break;
		}
	}
	if (flag) {
		printf("YES\n");
		for (int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	else
		printf("NO\n");
	scanf("%d", &n);
	return 0;
}