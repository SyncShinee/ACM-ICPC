#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 1000010
using namespace std;
typedef long long ll;
inline bool scan_d(int &ret) {
char c; int sgn;
if(c=getchar(),c==EOF) return 0; //EOF
while(c!='-'&&(c<'0'||c>'9')) c=getchar();
sgn=(c=='-')?-1:1;
ret=(c=='-')?0:(c-'0');
while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
ret*=sgn;
return 1;
}
ll ans, sum[100010];
int n, a[100010];//, R1[100010], R2[100010];

int main() {
    int T;
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    scan_d(T);
    while (T--) {
        scan_d(n);
        for (int i = 1; i <= n; ++i)
            scan_d(a[i]);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + a[i];
            //R1[i] = R2[i] = 1;
        }
        ans = 0;
        int l = 1, r = 1;
        for (int l = 1; l <= n; ++l) {
        	if (a[l] > 0)
        		continue;
        	if (r < l)
        		r = l;
        	while (r <= n && sum[r] - sum[l - 1] == 0) {
        		r++;
        	}
        	r --;
        	ans += ((((ll)(l<<1) + r + l) * (r - l + 1)) >> 1);
        }
        ll now = 0,now1 = 0;
        for (int i = 0; (1ll << i) <= sum[n]; ++i) {
            int r1 = 1, r2 = 1;
            now = (1ll << i);
            now1 = (now << 1);
            for (int l = 1; l <= n; ++ l) {
                //r1 = max(r1, R1[l]), r2 = max(r2, R2[l]);
                if (r1 < l) {
                    r1 = l;
                }
                while (r1 <= n && sum[r1] - sum[l - 1] < now) {
                    r1 ++;
                }
                if (r1 == n + 1) {
                    break;
                }
                if (sum[r1] - sum[l - 1] >= now1) {
                    continue;
                }
                if (r2 < r1 + 1) {
                    r2 = r1 + 1;
                }

                while (r2 <= n && sum[r2] - sum[l - 1] < now1) {
                    r2 ++;
                }
                r2 --;
                //R1[l] = r1, R2[l] = r2;
                ans += ((((ll)(l<<1) + r2 + r1) * (r2 - r1 + 1) * (i + 1)) >> 1);
                //ans += (i + 1) * (l * (r2 - r1 + 1) + (r1 + r2) * (r2 - r1 + 1) / 2);
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}