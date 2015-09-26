#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

const int maxn = 1e5 + 100;
const int MAXNODE = 4*maxn;

struct info
{
	bool l[11], r[11], res[11];
	int all;
	void getZero()
	{
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
		memset(res, 0, sizeof(res));
		all = 0;
	}
};
info tree[MAXNODE];
int n, a[maxn], rtn, q;

int add(int &a, int &b)
{
	int ans = a+b;
	if(ans > 9)
		ans -= 9;
	return ans;
}
void getMerge(info &a, info &b, info &c)
{
	c.all = add(a.all, b.all);
	for(int i = 0;i<=9;i++)
	{
		c.l[i] = a.l[i];
		c.r[i] = b.r[i];
		c.res[i] = (a.res[i]||b.res[i]);
	}
	for(int i = 0;i<=9;i++)
	{
		if(b.l[i])
		{
			int targe = add(i, a.all);
			c.l[targe] = 1;
		}
		if(a.r[i])
		{
			int targe = add(i, b.all);
			c.r[targe] = 1;
		}
	}
	for(int i = 0;i<=9;i++)
	{
		if(a.r[i])
		{
			for(int j = 0;j<=9;j++)
			{
				if(b.l[j])
				{
					int targe = add(i, j);
					c.res[targe] = 1;
				}
			}
		}
	}
}

void pushUp(int rt)
{
	int lRt = (rt << 1), rRt = ((rt<<1)|1);
	getMerge(tree[lRt], tree[rRt], tree[rt]);
}
void initail()
{
	rtn = 1;
	while(rtn < n)
		rtn <<= 1;
	for(int i = 1;i<=n;i++)
	{
		//memset(tree[rtn + i - 1], 0, sizeof(tree[rtn + i - 1]) ) ;
		tree[rtn + i - 1].getZero();
		tree[rtn + i - 1].all = a[i];
		tree[rtn + i - 1].l[a[i]] = 1;
		tree[rtn + i - 1].r[a[i]] = 1;
		tree[rtn + i - 1].res[a[i]] = 1;
	}
	for(int i = rtn + n;i<2*rtn;i++)
	{
		tree[i].getZero();
		//memset(tree[i], 0, sizeof(tree[i]));
	}
	for(int i = rtn - 1;i>=1;i--)
	{
		pushUp(i);
	}
}

info query(int L, int R, int rt, int l, int r)
{
	if(L <= l && R >= r)
		return tree[rt];
	int lRt = (rt << 1), rRt = ((rt<<1)|1), mid = (l+r)/2;
	info a, b, c;
	a.getZero();
	b.getZero();
	//c.getZero();
	int flagA = 0, flagB = 0;
	if(L <= mid)
	{
		flagA = 1;
		a = query(L, R, lRt, l, mid);
	}
	if(R >= mid+1)
	{
		flagB = 1;
		b = query(L, R, rRt, mid+1, r);
	}
	if(flagA&&flagB)
	{
		getMerge(a, b, c);
		return c;
	}
	if(flagB) return b;
	return a;
}
void solve()
{
	initail();
	scanf("%d", &q);
	//printf("%d ---\n", q);
	while(q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		//printf("%d %d\n",l, r );
		info a = query(l, r, 1, 1, rtn);
		int cnt = 0;
		for(int i = 9;i>=0;i--)
		{
			if(a.res[i])
			{
				cnt++;
				if(cnt != 1)
					printf(" ");
				printf("%d", i);
				if(cnt == 5)
					break;
			}
		}
		for(;cnt < 5;cnt++)
		{
			printf(" ");
			printf("-1");
		}
		printf("\n");
	}
}

int main() {
	freopen("Bin.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) 
	{
		if(cas != 1)
			printf("\n");
		printf("Case #%d:\n", cas);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i) 
		{
			scanf("%d", &a[i]);
			if(a[i]==0)
				a[i] = 0;
			else
			{
				a[i] %= 9;
				if(a[i]==0)
					a[i] = 9;
			}
			//printf("%d\n", a[i]);
		}
		solve();
	}
	return 0;
}