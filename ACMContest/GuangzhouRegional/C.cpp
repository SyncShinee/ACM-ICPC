#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const int M = 26;
int ch[N][M], ch2[N][M], tot, root, fail[N];
int f[M],g[M],f2[M];
int n;
ll ans;
char s[41];
int newnode()
{
	tot++;
	memset(ch[tot],-1,sizeof ch[tot]);
	memset(ch2[tot],-1,sizeof ch2[tot]);
	fail[tot] = 0;
	return tot;
}
void init()
{
	tot = -1;
	tot = newnode();
	root = 0;
	memset(f,0,sizeof f);
	memset(f2,0,sizeof f2);
	memset(g,0,sizeof g);
}
void insert(char *s)
{
	int l = strlen(s);
	int now = 0;
	for (int i = 0;i < l;i++)
	{
		int c = s[i] - 'a';
		if (ch[now][c] == -1)
		{
			ch[now][c] = newnode();
			ch2[now][c] = ch[now][c];
		}
		//printf("%d\n",ch[0][0]);
		now = ch[now][c];		
	}

}
void getfail()
{
	queue <int> q;
	for (int i = 0;i < M;i++)
	if (ch[root][i] != -1)
	{
		fail[ch[root][i]] = root;
		q.push(ch[root][i]);		
	}
	else
		ch[root][i] = root;

	while (!q.empty())
	{
		int h = q.front();
		q.pop();
		for (int i = 0;i < M;i++)
		{
			if (ch[h][i] == -1)
			{
				ch[h][i] = ch[fail[h]][i];
			}
			else
			{
				fail[ch[h][i]] = ch[fail[h]][i];
				q.push(ch[h][i]);
			}
		}		
	}
}
void dfs1(int u)
{
	for (int i = 0;i < M;i++)
	{
		if (ch2[u][i] == -1)
		{
			if (u) f[i]++;
			continue;
		}	
		if (u) f2[i]++;
		dfs1(ch2[u][i]);	
	}
}
int dfs2(int u)
{
	if (u == -1) return 0;
	int res = 0;
	for (int i = 0;i < M;i++)
	{
		if (ch2[u][i] == -1) continue;
		res += dfs2(ch2[u][i]);
	}	
	return ++res;
}
void dfs3(int u,int now)
{
	if (now <= 0)
	{
		//printf("%d %d\n",u,now);
		ans--;
	}
	for (int i = 0;i < M;i++)
	{
		if (ch2[u][i] == -1) continue;		
		dfs3(ch2[u][i],ch[now][i]);
	}	
}
void count()
{
	for (int i = 0;i < M;i++)
	if (ch2[0][i] != -1)
	{
		dfs3(ch2[0][i],0);
	}
}
void solve()
{
	if (n == 0) return;
	init();
	for (int i = 1;i <= n;i++)
	{
		scanf("%s",s);
		//puts(s);
		insert(s);		
	}
	getfail();
	//printf("%d %d\n",tot,ch2[0][0]);
	//puts("here");
	dfs1(0);
	for (int i = 0;i < M;i++)
		g[i] = dfs2(ch2[0][i]);
	
	//for (int i = 0;i < M;i++) printf("%c:%d ",i+'a',g[i]);puts("");
	//for (int i = 0;i < M;i++) printf("%c:%d ",i+'a',f2[i]);puts("");
	ans = 0;
	for (int i = 0;i < M;i++)
		ans += (ll)f[i] * g[i];
	for (int i = 0;i < M;i++)
		ans += (ll)f2[i] * g[i];
	printf("%lld\n",ans);
	//for (int i = 0;i < M;i++) ans += g[i];
	//count();
	//printf("%lld\n",ans);
}

int main()
{
	freopen("in.txt","r",stdin);
	while (~scanf("%d",&n))
		solve();
}