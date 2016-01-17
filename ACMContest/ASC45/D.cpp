#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
int p,q;
vector <int> ans[1010];
int main()
{
  freopen("drunkard.in","r",stdin);
  // freopen("drunkard.out","w",stdout);
  while (~scanf("%d %d",&p,&q)){
    if (p == 0 && q == 0) break;
    printf("%d\n",q + 1);
    int n = q + 1;
    for (int i = 1;i <= n;i++)
      ans[i].clear();
    for (int i = 2;i < p;i++){
      ans[i].push_back(i - 1);
      ans[i].push_back(i + 1);
    }
    ans[1].push_back(2);
    if (p != 1) ans[1].push_back(p + 1);
    else
      ans[1].push_back(n);
    if (p + 1 != n - 1){
      ans[p+1].push_back(1);
      ans[p+1].push_back(p + 2);
    }
    if (p != 1){
      ans[p].push_back(n);
      ans[p].push_back(p - 1);
    }
    for (int i = p + 2;i < n - 2;i++){
      ans[i].push_back(i + 1);
      ans[i].push_back(i - 1);
    }
    if (n - 2 != 1){
      ans[n - 2].push_back(n - 3);
      ans[n - 2].push_back(n - 1);
    }
    for (int i = 1;i < n - 1;i++){
      printf("%d %d\n",ans[i][0],ans[i][1]);
    }
  }
}
