#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll ans, num[100010];
int s[100010], f[100010], n, m, x, y;
int gf(int x) {
    if (x == f[x]) 
    	return x;
    else 
    	return f[x] = gf(f[x]);
}
bool judge(int x, int y) {
	if (gf(x) == gf(y))
		return true;
	return false;
}
void merge(int x, int y) {
	int tmp1 = gf(x), tmp2 = gf(y);
	f[y] = tmp1;
    f[tmp2] = tmp1;
	if (s[tmp1] == 0 && s[tmp2] == 0) 		
        num[tmp1] += num[tmp2];
    else if (s[tmp1] == 0) {
    	s[tmp1] = s[tmp2];
        if (num[tmp2] != 0) {
            if (s[tmp2] == 1)
            	num[tmp1] = 1;
            else
            	num[tmp1] = 2;
        }
        else 
            num[tmp1] = 0;
    }
    else if (s[tmp2] != 0)
        num[tmp1] = 0;
}
int main() {
	int i, cas, tmp;
	cas = 0;
    while (scanf("%d%d", &n, &m), n | m) {
        cas++;
        memset(s, 0, sizeof(s));
        for (i = 0; i < m; ++i) {
            f[i] = i;
            num[i] = 1;
        }
        for (i = 0; i < n; ++i) {
            scanf("%d%d", &x, &y);
            if (x == y) {
                tmp = gf(x);
                if (s[tmp] == 0)
                	num[tmp] = 1;
                else
                	num[tmp] = 0;
                s[tmp] = 1;
            }
            else {
                if (judge(x, y)) {
                	tmp = gf(x);
                    if (s[tmp])
                    	num[tmp] = 0;
                    else {
                        s[tmp] = 2;
                        num[tmp] = 2;
                    }
                }
                else 
                	merge(x, y);
            }
        }
        ans = 1;
        for (i = 0; i < m; ++i)
            if (gf(i) == i) {
                ans = (ans * num[i]) % 1000000007;
                if (ans == 0)
                	break;
            }
        printf("Case %d: %lld\n", cas, ans);
    }
	return 0;
}