#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#define MOD 1000000007
using namespace std;
bool vis[64];
map<int, int> hash;
int dfs(int x) {
	if(x == 0)
		return hash[x] = 0;
	if(hash.find(x) != hash.end())
		return hash[x];
	memset(vis, 0, sizeof(vis));
	int tmp = 0, tt = 29;
	while (tt >= 0) {
		if(x & (1 << tt))
			break;
		tt--;
	}
	for(int i = 1; i <= tt; ++i) {
		if((x & (1 << i)) == 0)
			continue;
		tmp = 0;
		for(int j = 1;j <= tt; ++j) {
			if((x & (1 << j)) == 0)
				continue;
			if(j % i == 0)
				continue;
			tmp |= 1 << j;
		}
		vis[dfs(tmp)] = 1;
	}
	int i = 0;
	while (true) {
		if(vis[i] == 0) {
			hash[x] = i;
			return i;
		}
		++i;
	}
}
int SG[30] = {0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12};
int main()
{

			sg0[0]=0;
			for(int i = 1; i < 30; ++i)
			{
				int tmp = 0;
				for(int j = 1;j <= i; ++j)
					tmp |= 1 << j;
				sg0[i] = dfs(tmp);
				printf("%d ",sg0[i]);

	//system("pause");
	return 0;
}