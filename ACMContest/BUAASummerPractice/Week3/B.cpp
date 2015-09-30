#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sr, sb, sg, MOD, x, y;
void exgcd(int a,int b,int &x,int &y)
{
     if(b==0){x=1;y=0;return;}
     exgcd(b,a%b,x,y);
     int t=x;x=y;y=t-a/b*y;
}
int quick_inverse(int x, int p) {
    int ex = p - 2, ret = 1;
    while (ex) {
        if (ex & 1) {
            ret = ret * x % p;
        }
        x = x * x % p;
        ex >>= 1;
    }
    return ret;
}
int f[64][64][64], a[256], b[256];
bool flag[256];
int main() {
    // freopen("in.txt", "r", stdin);
    while (~scanf("%d%d%d%d%d", &sr, &sb, &sg, &m, &MOD)) {
        n = sr + sg + sb;
        int ans = 0;
        for (int ti = 0; ti <= m; ++ ti) {
            if (ti == 0) {
                for (int i = 1; i <= n; ++ i) {
                    b[i] = 0;
                    flag[i] = false;
                    a[i] = i;
                }
            }
            else {
                for (int i = 1; i <= n; ++ i) {
                    b[i] = 0;
                    flag[i] = false;
                    scanf("%d", &a[i]);
                }
            }
            int num = 1;
            for (int i = 1; i <= n; ++ i) {
                int pos = i;
                if (flag[i]) {
                    continue;
                }
                while (!flag[pos]) {
                    b[num] ++;
                    flag[pos] = true;
                    pos = a[pos];
                }
                num++;
            }
            memset(f, 0, sizeof f);
            f[0][0][0] = 1;
            for (int i = 1; i < num; ++ i) {
                for (int j = sr; j >= 0; --j) {
                    for (int t = sb; t >= 0; --t) {
                        for (int k = sg; k >= 0; --k) {
                            if (j >= b[i]) {
                                f[j][t][k] = (f[j][t][k] + f[j - b[i]][t][k]) % MOD;
                            }
                            if (t >= b[i]) {
                                f[j][t][k] = (f[j][t][k] + f[j][t - b[i]][k]) % MOD;
                            }
                            if (k >= b[i]) {
                                f[j][t][k] = (f[j][t][k] + f[j][t][k - b[i]]) % MOD;
                            }
                        }
                    }
                }
            }
            ans = (ans + f[sr][sb][sg]) % MOD;
        }
         printf("%d %d\n", ans);
        ans = ans * quick_inverse(m+1, MOD) % MOD;
        printf("%d\n", ans);
    }
    return 0;
}