#include <cstdio>
#include <cstring>

using namespace std;
int a[1010][1010];
int ans[1010][1010];
int n,m;
int main() {
	//freopen("in","r",stdin);
	int T;
	scanf("%d",&T);
	while (T--) {
		memset(ans,0,sizeof ans);
		scanf("%d %d",&n,&m);
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= m;j++)
				scanf("%d",&a[i][j]);
		int j;
		for (int i = 1;i <= n;i+=2) {
			j = 1;
			while (j <= m) {
				if (a[i][j] >= 4) {
					ans[i][j] = 1;
					a[i+1][j]--;
					a[i+1][j+1]--;
					a[i][j+1]--;
				}else {
					ans[i][j] = 0;
				}
				j++;
				a[i][j] -= (-ans[i][j-1] * 4 + a[i][j-1]);
				if (a[i][j] >= 3) {
					ans[i][j] = 1;
					a[i+1][j]--;
					a[i+1][j+1]--;
					a[i][j+1]--;
				}else {
					ans[i][j] = 0;
				}
				i++,j--;
				a[i][j] -= (-ans[i-1][j] * 4 + a[i-1][j]);
				if (a[i][j] >= 3) {
					ans[i][j] = 1;
					a[i+1][j]--;
					a[i+1][j+1]--;
					a[i][j+1]--;
				}else {
					ans[i][j] = 0;
				}
				int tmp = a[i-1][j] - ans[i-1][j] * 4 - ans[i][j] - ans[i-1][j+1];
				if (tmp == 1) {
					ans[i][j+1] = 1;
					a[i+1][j]--;
					a[i+1][j+1]--;
					a[i][j+1]--;
				}
				else {
					ans[i][j+1] = 0;
				}
				i--;
				j+=2;
			}
		}
		//printf("%d\n",a[2][1]);
		for (int i = 1;i <= n;i++,printf("\n"))
			for (int j = 1;j <= m;j++)
			if (ans[i][j] == 1)
				printf("L");
			else
				printf("-");
	}
}
