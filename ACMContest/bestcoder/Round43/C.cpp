#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
int label, n, Q, yy, ll, rr, dfn[300010], mn[300010][25], mx[300010][25];
vector <int> gra[300010];
struct node {
	int l, r, idx;
	friend bool operator < (node x, node y) {
		return x.l < y.l || (x.l == y.l && x.r < y.r);
	}
}p[300010], ptmp;

void dfs(int x, int pre) {
	dfn[x] = label++;
	p[x].l = label - 1;
	p[x].idx = x;
	for (int i = 0; i < gra[x].size(); ++i) {
		if (gra[x][i] == pre)
			continue;
		dfs(gra[x][i], x);
	}
	p[x].r = label - 1;
}

int ask(int l,int r,int q){
   int tmp = int(log((r - l + 1)*1.0) / log(2.0));
   int k1,k2;
   
   if (q == 0){
       k1 = mn[l][tmp],k2 = mn[r - (1 << tmp) + 1][tmp];
       if (dfn[k1] < dfn[k2] || (dfn[k1] == dfn[k2] && k1 < k2)) return k1;
       else return k2;
   }
   else{
       k1 = mx[l][tmp],k2 = mx[r - (1 << tmp) + 1][tmp];
       if (dfn[k1] > dfn[k2] || (dfn[k1] == dfn[k2] && k1 < k2)) return k1;
       else return k2;
   }
}

int main() {
	while (~scanf("%d", &n)) {
		int x, y;
		for (int i = 1; i <= n; ++i)
			gra[i].clear();
		memset(p, 0, sizeof(p));
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			gra[x].push_back(y);
			gra[y].push_back(x);
		}
		label= 1;
		dfs(1, 0);
		sort(p + 1, p + n + 1);
		for (int i = 1;i <= n;i ++) 
			mn[i][0] = mx[i][0] = i;
	   
		for (int i = 1; (1 << i) <= n; ++i){
		   for(int j = 1; j + (1 << i) - 1 <= n; ++j){
		       int p = mn[j][i - 1], q = mn[j + (1 << i - 1)][i - 1];
		       if (dfn[p] < dfn[q] || (dfn[p] == dfn[q] && p < q)) 
		       		mn[j][i] = p;
		       else 
		       		mn[j][i] = q;
		       p = mx[j][i - 1],q = mx[j + (1 << i - 1)][i - 1];
		       if (dfn[p] > dfn[q] || (dfn[p] == dfn[q] && p < q)) 
		       		mx[j][i] = p;
		       else 
		       		mx[j][i] = q;
		   }
		}
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d%d", &ll, &rr);
			ptmp.l = dfn[ask(ll, rr, 0)];
			ptmp.r = dfn[ask(ll, rr, 1)];
			yy = lower_bound(p+1, p+n+1, ptmp) - p;
			while (yy > 0 && p[yy].l > ptmp.l) {
				yy--;
			}
			while (yy > 0 && (p[yy].r < ptmp.r))
				yy--;
			printf("%d\n", p[yy].idx);
		}
	}
	return 0;
}