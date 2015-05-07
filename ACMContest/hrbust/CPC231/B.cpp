#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll p[1001000], t[1001000], cnt;
int i, n, a, b;
void msort(int l,int r) {
    int mid, i, j, tmp;
    if(r > l+1) {
        mid = (l+r) >> 1;
        msort(l, mid);
        msort(mid, r);
        tmp = l;
        for(i = l, j = mid; i < mid && j < r;) {
            if(p[i] > p[j]) {
                t[tmp++] = p[j++];
                cnt += (ll)mid - i;
            }
            else
                t[tmp++] = p[i++];
        }
        while (i < mid) 
        	t[tmp++] = p[i++];
        while (j < r)
        	t[tmp++] = p[j++];
        for(i = l; i < r; ++i)
        	p[i] = t[i];
    }
}
int main() {
	int cas = 0, i;
    while (scanf("%d%d%d", &n, &a, &b), n | a | b) {
        cas++;
        for (i = 0; i < n; ++i)
            p[i] = ((ll)a*i + (ll)b) % n;
        cnt = 0;
        msort(0, n);
        printf("Case %d: %lld\n", cas, cnt);
    }
	return 0;
}