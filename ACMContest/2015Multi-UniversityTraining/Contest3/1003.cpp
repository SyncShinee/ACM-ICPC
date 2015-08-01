#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#define MOD 1000000007
using namespace std;
char s[64][16];
int sum, n;
struct mar {
	int a[128][128];
	friend mar operator * (mar x, mar y) {
		mar k;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				k.a[i][j] = 0;
				for (int t = 0; t < n; ++t) {
					k.a[i][j] = (k.a[i][j] + 1ll * x.a[i][t] * y.a[t][j] % MOD) % MOD;
				}
			}
		}
		return k;
	} 
}ans;
mar power_mod(mar yuan, int k) {
	mar ret;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {			
			if (i == j) {
				ret.a[i][j] = 1;
			}
			else {
				ret.a[i][j] = 0;
			}
		}
	while (k > 0) {
		if (k & 1) {
			ret = ret * yuan;
		}
		yuan = yuan * yuan;
		k >>= 1;
	}
	return ret;
}
map <string, int> mp;
int main() {
	int T, m;
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		mar pre;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				pre.a[i][j] = 0;
		int tttt = 0;
		string x;
		mp.clear();
		int tot = 0;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			if (mp[x]) {
				continue;
			}
			mp[x] = 1;
			for (int j = 0; j < x.size(); ++j)
				s[tot][j] = x[j];
			s[tot++][x.size()] = '\0';
		}
		n = tot;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int la = strlen(s[i]), lb = strlen(s[j]);
				int len = min(la, lb);
				for(int k = 2;k<=len;k++)
				{
					int flag = 1;
					for(int z = 0;z<k;z++)
					{
						if(s[i][la - k + z]!=s[j][z])
							{
								flag = 0;
								break;
							}
					}
					if(flag)
					{
						pre.a[i][j] = 1;
						break;
					}
				}
			}
			//rintf("\n");
		}
		if (m > 1)
			ans = power_mod(pre, m-1);
		sum = 0;
		if (m > 1)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				sum = (sum + ans.a[i][j]) % MOD;
		if (m == 0) {
			sum = 1;
		}
		if (m == 1) {
			sum = n % MOD;
		}
		printf("%d\n", sum);
	}
}