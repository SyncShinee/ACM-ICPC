#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 998244353
using namespace std;

int n, m, x, y, ans;

int gra[20][20], G[20][20], reflect[20], f[1 << 17], dp[1 << 17][20];

struct atom{
    int x,y;
    atom(){}
    atom(int _x, int _y) {
    	x = _x;
    	y = _y;
    }
};

atom operator - (const atom k1,const atom k2){
    return atom((k1.x-k2.x+MOD)%MOD,(k1.y-k2.y+MOD)%MOD);
}

atom operator * (const atom k1,const int k2){
    return atom(1ll*k1.x*k2%MOD,1ll*k1.y*k2%MOD);
}


int gauss(int n) {
	int sign = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			G[i][j] = (G[i][j] + MOD) % MOD;
	for (int i = 1; i <= n; ++i) {
		int r = 0;
		for (int j = i; j <= n; ++j) {
			if (G[i][j]) {
				r = j;
				break;
			}
		}
		if (r != i) {
			sign = -sign;
			for (int j = 1; j <= n; ++j) {
				swap(G[i][j], G[r][j]);
			}
		}
		for (int j = i + 1; j <= n; ++j) {
			int k1 = G[i][i], k2 = G[j][i];
			atom x = atom(1, 0), y = atom(0, 1);
			while (k2) {
				int k4 = k1 / k2;
				atom z = y;
				y = x - y * k4;
				x = z;
				k4 = k2;
				k2 = k1 % k2;
				k1 = k4;
				sign = -sign;
			}
			for (int k = 1; k <= n; ++k) {
				int k3 = G[i][k], k4 = G[j][k];
				G[i][k] = (1ll * x.x * k3 + 1ll * x.y * k4) % MOD;
				G[j][k] = (1ll * y.x * k3 + 1ll * y.y * k4) % MOD;
			}
		}
	} 
	for (int i = 1; i <= n; ++i)
		sign = 1ll * sign * G[i][i] % MOD;
	return (sign + MOD) % MOD;
}

int main() {
	//freopen("e.in", "r", stdin);
	//freopen("1005.out", "w", stdout);
	while (~scanf("%d%d", &n, &m)) {
		memset(gra, 0, sizeof gra);
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &x, &y);
			gra[x][y] = gra[y][x] = 1;
		}
		//预处理dp
		memset(f, 0, sizeof f);
		memset(dp, 0, sizeof dp);
		for (int s = 1; s < n; ++s) {
			
			dp[1 << s - 1][s] = 1;
			for (int sta = 1 << s - 1; sta < (1 << n); sta += 1 << s - 1) {
				for (int u = s; u <= n; ++u) {
					if (!dp[sta][u])
						continue;
					for (int v = s + 1; v <= n; ++v) {
						if (gra[u][v] && ((sta & (1 << v - 1)) == 0)) {
							dp[sta | (1 << v - 1)][v] = (dp[sta | (1 << v - 1)][v] + dp[sta][u]) % MOD;
						}
					}
					if (gra[u][s] && (sta ^ (1 << u - 1) ^ (1 << s - 1)) > 0) {
						f[sta] = (f[sta] + dp[sta][u]) % MOD;
					}
				}
			}
		}
		int inv2 = (MOD + 1) / 2;
		for (int i = 1; i < (1 << n); ++i) {
			f[i] = (1ll * f[i] * inv2) % MOD;
		}

		//枚举子集作为环，缩点求生成树个数
		ans = 0;
		for (int sta = 1; sta < (1 << n); ++sta) {
			if (!f[sta])
				continue;
			int vetex = 1;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					G[i][j] = 0;
			for (int i = 1; i <= n; ++i) {
				if ((sta & (1 << i - 1)) == 0) {
					reflect[i] = vetex++;
				}
			}
			for (int i = 1; i <= n; ++i) {
				if (sta & (1 << i - 1)) {
					reflect[i] = vetex;
				}
			}
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j) {
					if (gra[i][j]) {
						G[reflect[i]][reflect[j]]--;
						G[reflect[i]][reflect[i]]++;
					}
				}
			ans = (ans + 1ll * f[sta] * gauss(vetex - 1)) % MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}