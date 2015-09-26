#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6 + 100;
char s[N];
void solve()
{
	scanf("%s",s);
	int l = strlen(s);
	
	int pre = -1,cnt = 0, front = -1,ans = 0;
	bool flag = 1;
	for (int i = 0;i < l;i++)
	{
		//printf("%c\n",s[i]);
		if (s[i] == 'f')
		{
			if (pre != -1) cnt++;			
		}
		else if (s[i] == 'c')
		{
			if (pre != -1 && cnt < 2) flag = 0;
			if (pre == -1) front = i;
			pre = i;
			cnt = 0;
			ans ++;
		}
		else
			flag = 0;
	}
	static int ca = 0;
	if (pre == -1)
	{
		printf("Case #%d: %d\n",++ca,(l + 1)/2);
		return;
	}
	cnt += front;
	if (cnt < 2) flag = 0;
	if (flag == 1)
		printf("Case #%d: %d\n",++ca,ans);
	else
		printf("Case #%d: -1\n",++ca);

}
int main()
{
	freopen("in.txt","r",stdin);
	int t;
	scanf("%d",&t);
	while (t--)
		solve();
}