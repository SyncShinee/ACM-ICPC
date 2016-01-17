#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n;
vector<int> a[2];

void solve()
{
  a[0].clear();
  a[1].clear();
  int flag = 0, cnt = 0;
  if(n != 2 && n != 4 )
    {
      printf("No\n");
    }
  else
    {
      printf("Yes\n");
      for(int i = 1; i <= n; i += 2)
	{
	  cnt++;
	  a[flag].push_back(cnt);
	  a[flag].push_back(cnt + 3);
	  a[flag^1].push_back(cnt + 1);
	  a[flag^1].push_back(cnt + 2);
	  cnt += 3;
	  flag ^= 1;
	}
      for(int j = 0; j < 2; j++)
	{
	  for(int i = 0; i < a[j].size(); i++)
	    printf("%d ", a[j][i]);
	  printf("\n");
	 }
    }
}
int main()
{
  freopen("analogous.in", "r", stdin);
  freopen("analogous.out", "w", stdout);
  while(scanf("%d", &n) && n)
    {
      solve();
    }
  return 0;
}
